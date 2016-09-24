/*
Helios Laser DAC main AS project (for SAM4S2B board)
By Gitle Mikkelsen, Creative Commons Attribution-NonCommercial 4.0 International Public License

Required Atmel Software Framework modules:
	DACC - Digital-to-Analog Converter
	Flash
	Generic Board Support (ATSAM4S2B)
	GPIO
	IOPORT
	SPI - Serial Peripheral Interface
	USB Device Vendor Class
	WDT - Watchdog Timer
*/

#include "main.h"

//ENTRY
int main (void)
{
	//allocate memory to buffers
	frameAddress = malloc(MAXFRAMESIZE * 7 + 5);
	newFrameAddress = malloc(MAXFRAMESIZE * 7 + 5);
	usbInterruptBufferAddress = malloc(2);
	
	//start modules
	sysclk_init();
	pmc_disable_all_periph_clk();
	pmc_disable_pllbck();
	dac_init();
	spi_init();
	iopins_init();
	irq_initialize_vectors();
	cpu_irq_enable();
	sleepmgr_init();
	udc_start();
	wdt_disable(WDT);
	
	//set systick higher priority to avoid pauses in playback when processing USB transfers
	NVIC_SetPriority(SysTick_IRQn, 0); 
	NVIC_SetPriority(UDP_IRQn, 1);
	
	//default output
	shutter_set(LOW);
	statusled_set(LOW);
	ioport_set_pin_level(PIN_POWERLED, HIGH);
	stop();
	
	sleepmgr_lock_mode(SLEEPMGR_WAIT_FAST);
	
	//waiting for interrupts..
	while (true)
		sleepmgr_enter_sleep();
}

void SysTick_Handler(void) //systick timer ISR, called for each point
{
	if (playing)
	{
		if (framePos >= frameSize) //if frame reached the end
		{
			if (newFrameReady)
			{
				//load new frame, switch buffers
				uint8_t* previousFrameAddress = frameAddress;
				frameAddress = newFrameAddress;
				newFrameAddress = previousFrameAddress;
				newFrameReady = false;
				framePos = 0;
				frameSize = newFrameSize;
				notRepeat = newNotRepeat;
				point_output();
				framePos += 7;
				speed_set(outputSpeed);
			}
			else
			{
				if (!notRepeat)
				{
					//loop frame
					framePos = 0;
					point_output();
					framePos += 7;
				}
				else
				{
					stop();
				}
				
			}
		}
		else
		{
			//output current point
			point_output();
			framePos += 7;
		}
	}
}

void usb_bulk_out_callback(udd_ep_status_t status, iram_size_t length, udd_ep_id_t ep)
{
	UNUSED(ep);
	
	//0-n:	frame data, each point is 12-bit X+Y packed into 24-bit big-endian, 8bit R, 8bit G, 8bit B, 8bit I
	//n:	output rate 16bit little endian
	//n+2:	frame size in points 16bit little endian
	//n+4:	flags
	
	if ( (status == UDD_EP_TRANSFER_OK) && (length <= MAXFRAMESIZE * 7 + 5) ) //if not invalid
	{
		uint16_t numOfPointBytes = length - 5; //from length of received data
		uint16_t numOfPointBytes2 = ((newFrameAddress[numOfPointBytes + 3] << 8) | newFrameAddress[numOfPointBytes + 2]) * 7; //from control bytes
		
		if (numOfPointBytes == numOfPointBytes2) //sanity check, skip frame if conflicting frame size information
		{
			cpu_irq_enter_critical();
				uint8_t flags = newFrameAddress[numOfPointBytes + 4];
				newNotRepeat = (flags & (1 << 1));
				outputSpeed = (newFrameAddress[numOfPointBytes + 1] << 8) | newFrameAddress[numOfPointBytes + 0];			
			
				if ( (!playing) || (flags & (1 << 0)) ) //if frame is to start playing immediately
				{
					uint8_t* previousFrameAddress = frameAddress;
					frameAddress = newFrameAddress;
					newFrameAddress = previousFrameAddress;
					framePos = 0;
					frameSize = numOfPointBytes;
					newFrameReady = false;
					playing = true;
					notRepeat = newNotRepeat;
					speed_set(outputSpeed);
				} 
				else
				{
					newFrameSize = numOfPointBytes;
					newFrameReady = true;
				}
			cpu_irq_leave_critical();
		}
	}
}

void usb_interrupt_out_callback(udd_ep_status_t status, iram_size_t length, udd_ep_id_t ep)
{
	//LSB: Command
	//MSB: Data
	
	UNUSED(ep);
	if ( (status == UDD_EP_TRANSFER_OK) && (length == 2) )
	{	
		if (usbInterruptBufferAddress[0] == 0x01)		//STOP
		{
			stop();
		}
		else if (usbInterruptBufferAddress[0] == 0x02)	//SHUTTER
		{
			shutter_set( (usbInterruptBufferAddress[1] && true) );
		}
		else if (usbInterruptBufferAddress[0] == 0x03)	//STATUS REQUEST
		{
			uint8_t statusTransfer[2] = {0x83, !newFrameReady};
				
			if (!newFrameReady)
				udi_vendor_bulk_out_run(newFrameAddress, MAXFRAMESIZE * 7 + 5, usb_bulk_out_callback);
				
			udi_vendor_interrupt_in_run(&statusTransfer[0], 2, NULL);
		}
		else if (usbInterruptBufferAddress[0] == 0xDE)	//ERASE GPNVM BIT, BOOT TO FIRMWARE UPDATE BOOTLOADER
		{
			stop();
			flash_clear_gpnvm(1);
			wdt_init(WDT, 0, 1, 0);
			while (1); //MCU will restart into SAM-BA
		}
	}
	
	udi_vendor_interrupt_out_run(usbInterruptBufferAddress, 2, usb_interrupt_out_callback);
}


inline void point_output(void) //sends point data to the DACs, data is point number "framePos" in buffer "frameAddress".
{
	uint8_t* currentPoint = frameAddress + framePos;
	
	if ((dacc_get_interrupt_status(DACC) & DACC_ISR_TXRDY) == DACC_ISR_TXRDY) //if DAC ready
	{
		dacc_set_channel_selection(DACC, 0);
		dacc_write_conversion_data(DACC, (currentPoint[0] << 4) | (currentPoint[1] >> 4) ); //X
	}
	
	spi_write(SPI, (currentPoint[6] << 4) | (0b0001 << 12), 0, 0); //I
	spi_write(SPI, (currentPoint[5] << 4) | (0b0101 << 12), 0, 0); //B
	spi_write(SPI, (currentPoint[4] << 4) | (0b1001 << 12), 0, 0); //G
	spi_write(SPI, (currentPoint[3] << 4) | (0b1101 << 12), 0, 0); //R
	
	if ((dacc_get_interrupt_status(DACC) & DACC_ISR_TXRDY) == DACC_ISR_TXRDY) //if DAC ready
	{
		dacc_set_channel_selection(DACC, 1);
		dacc_write_conversion_data(DACC, ((currentPoint[1] & 0x0F) << 8) | currentPoint[2]); //Y
	}
	
	statusled_set( (currentPoint[6] != 0) ); //turn on status led if not blanked
}

inline void stop(void) //outputs a blanked and centered point and stops playback
{
	playing = false;
	framePos = 0;
	newFrameReady = false;
	statusled_set(LOW);
		
	if ((dacc_get_interrupt_status(DACC) & DACC_ISR_TXRDY) == DACC_ISR_TXRDY) //if DAC ready
	{
		dacc_set_channel_selection(DACC, 0 );
		dacc_write_conversion_data(DACC, 0x800 ); //X
	}
	
	//blank colors
	spi_write(SPI, (0b0001 << 12), 0, 0); //I
	spi_write(SPI, (0b0101 << 12), 0, 0); //B
	spi_write(SPI, (0b1001 << 12), 0, 0); //G
	spi_write(SPI, (0b1101 << 12), 0, 0); //R
	
	if ((dacc_get_interrupt_status(DACC) & DACC_ISR_TXRDY) == DACC_ISR_TXRDY) //if DAC ready
	{
		dacc_set_channel_selection(DACC, 1 );
		dacc_write_conversion_data(DACC, 0x800 ); //Y
	}
	
	//blank colors again to be sure, had some problems with them not being blanked first time
	spi_write(SPI, (0b1101 << 12), 0, 0); //R
	spi_write(SPI, (0b1001 << 12), 0, 0); //G
	spi_write(SPI, (0b0101 << 12), 0, 0); //B
	spi_write(SPI, (0b0001 << 12), 0, 0); //I
	
}

inline void speed_set(uint32_t rate) //set the output speed in points per second
{
	if (rate > MAXSPEED)
		rate = MAXSPEED;
	else if (rate < MINSPEED)
		rate = MINSPEED;
	outputSpeed = rate;
	SysTick_Config( (sysclk_get_cpu_hz() / rate) + 1);
}

int callback_vendor_enable(void) //usb connection opened, preparing for activity
{	
	stop();
	
	sleepmgr_unlock_mode(SLEEPMGR_WAIT_FAST);
	sleepmgr_lock_mode(SLEEPMGR_ACTIVE);
	
	udi_vendor_interrupt_out_run(usbInterruptBufferAddress, 2, usb_interrupt_out_callback);
	
	return 1;
}

void callback_vendor_disable(void) //usb connection closed, sleeping to save power
{
	stop();
	
	sleepmgr_unlock_mode(SLEEPMGR_ACTIVE);
	sleepmgr_lock_mode(SLEEPMGR_WAIT_FAST);
}

inline void shutter_set(bool level)
{
	ioport_set_pin_level(PIN_SHUTTER, level);
}

inline void statusled_set(bool level)
{
	ioport_set_pin_level(PIN_STATUSLED, level);
}

//INIT FUNCTIONS:

void iopins_init(void) //setup io pins config
{
	ioport_set_pin_dir(PIN_SHUTTER, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(PIN_STATUSLED, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(PIN_POWERLED, IOPORT_DIR_OUTPUT);
	
	//ioport_set_pin_dir(PIN_DEBUG1, IOPORT_DIR_OUTPUT);
	//ioport_set_pin_level(PIN_DEBUG1, LOW);
	//ioport_set_pin_dir(PIN_DEBUG2, IOPORT_DIR_OUTPUT);
	//ioport_set_pin_level(PIN_DEBUG2, LOW);
}

void spi_init(void) //setup SPI for DAC084S085
{
	gpio_configure_pin(SPI_MISO_GPIO, SPI_MISO_FLAGS);
	gpio_configure_pin(SPI_MOSI_GPIO, SPI_MOSI_FLAGS);
	gpio_configure_pin(SPI_SPCK_GPIO, SPI_SPCK_FLAGS);
	gpio_configure_pin(SPI_NPCS0_GPIO, SPI_NPCS0_FLAGS);
	spi_enable_clock(SPI);
	spi_disable(SPI);
	spi_reset(SPI);
	spi_set_master_mode(SPI);
	spi_set_fixed_peripheral_select(SPI);
	spi_disable_mode_fault_detect(SPI);
	spi_configure_cs_behavior(SPI, 0, SPI_CS_RISE_FORCED);
	spi_set_delay_between_chip_select(SPI, 6);
	spi_set_peripheral_chip_select_value(SPI, spi_get_pcs(0));
	spi_set_clock_polarity(SPI, 0, 0);
	spi_set_clock_phase(SPI, 0, 0);
	spi_set_bits_per_transfer(SPI, 0, SPI_CSR_BITS_16_BIT);
	spi_set_baudrate_div(SPI, 0, 5 ); //96MHz / 5 = 19.2 MHz
	spi_set_transfer_delay(SPI, 0, 0, 0);
	spi_enable(SPI);
}

void dac_init(void) //setup sam internal DAC controller
{
	sysclk_enable_peripheral_clock(ID_DACC);
	dacc_reset(DACC);
	dacc_enable_channel(DACC, 0);
	dacc_enable_channel(DACC, 1);
	dacc_set_transfer_mode(DACC, 0);
}

// Below is all to make Windows automatically install driver when plugged in
// Credits: https://github.com/cjameshuff/m1k-fw/

static USB_MicrosoftCompatibleDescriptor msft_compatible = {
	.dwLength = sizeof(USB_MicrosoftCompatibleDescriptor) +
	1*sizeof(USB_MicrosoftCompatibleDescriptor_Interface),
	.bcdVersion = 0x0100,
	.wIndex = 0x0004,
	.bCount = 1,
	.reserved = {0, 0, 0, 0, 0, 0, 0},
	.interfaces = {
		{
			.bFirstInterfaceNumber = 0,
			.reserved1 = 0,
			.compatibleID = "WINUSB\0\0",
			.subCompatibleID = {0, 0, 0, 0, 0, 0, 0, 0},
			.reserved2 = {0, 0, 0, 0, 0, 0},
		}
	}
};

// WCID configuration information
// Hooked into UDC via UDC_GET_EXTRA_STRING #define.
bool msft_string_handle(void) {
	uint8_t udi_msft_magic[] = "MSFT1000";

	struct extra_strings_desc_t{
		usb_str_desc_t header;
		le16_t string[sizeof(udi_msft_magic)];
	};

	static UDC_DESC_STORAGE struct extra_strings_desc_t extra_strings_desc = {
		.header.bDescriptorType = USB_DT_STRING
	};

	uint8_t i;
	uint8_t *str;
	uint8_t str_lgt=0;

	if ((udd_g_ctrlreq.req.wValue & 0xff) == 0xEE) {
		str_lgt = sizeof(udi_msft_magic)-1;
		str = udi_msft_magic;
	}
	else {
		return false;
	}

	if (str_lgt!=0) {
		for( i=0; i<str_lgt; i++) {
			extra_strings_desc.string[i] = cpu_to_le16((le16_t)str[i]);
		}
		extra_strings_desc.header.bLength = 2+ (str_lgt)*2;
		udd_g_ctrlreq.payload_size = extra_strings_desc.header.bLength;
		udd_g_ctrlreq.payload = (uint8_t *) &extra_strings_desc;
	}

	// if the string is larger than request length, then cut it
	if (udd_g_ctrlreq.payload_size > udd_g_ctrlreq.req.wLength) {
		udd_g_ctrlreq.payload_size = udd_g_ctrlreq.req.wLength;
	}
	return true;
}

bool usb_device_specific_request(void) {
	uint8_t* ptr = 0;
	uint16_t size = 0;
	
	if (Udd_setup_type() == USB_REQ_TYPE_VENDOR) {//ioport_set_pin_level(PIN_POWERLED, LOW);
		switch (udd_g_ctrlreq.req.bRequest) {
			/// windows compatible ID handling for auto install
			case 0x30: {
				if (udd_g_ctrlreq.req.wIndex == 0x04) {
					ptr = (uint8_t*)&msft_compatible;
					size = (udd_g_ctrlreq.req.wLength);
					if (size > msft_compatible.dwLength) {
						size = msft_compatible.dwLength;
					}
					
				}
				else {
					return false;
				}
				break;
			}
		}
	}
	udd_g_ctrlreq.payload_size = size;
	if ( size == 0 ) {
		udd_g_ctrlreq.callback = 0;
		udd_g_ctrlreq.over_under_run = 0;
	}
	else {
		udd_g_ctrlreq.payload = ptr;
	}
	return true;
}