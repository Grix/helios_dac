/**
 * \file
 *
 * \brief User board configuration template
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef CONF_BOARD_H
#define CONF_BOARD_H

/** Board oscillator settings */
#define BOARD_FREQ_SLCK_XTAL        (32768U)
#define BOARD_FREQ_SLCK_BYPASS      (32768U)
#define BOARD_FREQ_MAINCK_XTAL      (16000000UL)
#define BOARD_FREQ_MAINCK_BYPASS    (16000000UL)

/** Master clock frequency */
#define BOARD_MCK                   (96000000UL) //max for uc: 120 MHz

/** board main clock xtal startup time */
#define BOARD_OSC_STARTUP_US		15625

//GPIO pins
#define PIN_SHUTTER			(IOPORT_CREATE_PIN(PIOA,26))
#define PIN_STATUSLED		(IOPORT_CREATE_PIN(PIOA,24))

/*! SPI MISO pin definition. */
#define SPI_MISO_GPIO       (PIO_PA12_IDX)
#define SPI_MISO_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
/*! SPI MOSI pin definition. */
#define SPI_MOSI_GPIO       (PIO_PA13_IDX)
#define SPI_MOSI_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)

#define SPI_NPCS0_GPIO		(PIO_PA11_IDX)
#define SPI_NPCS0_FLAGS     (PIO_PERIPH_A | PIO_DEFAULT)

/*! SPI SPCK pin definition. */
#define SPI_SPCK_GPIO       (PIO_PA14_IDX)
#define SPI_SPCK_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)

#endif // CONF_BOARD_H
