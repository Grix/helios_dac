/* %ATMEL_LICENCE% */

#ifndef _SAM4S16A_
#define _SAM4S16A_

/** \addtogroup SAM4S16A_definitions SAM4S16A definitions
  This file defines all structures and symbols for SAM4S16A:
    - registers and bitfields
    - peripheral base address
    - peripheral ID
    - PIO definitions
*/
/*@{*/

#ifdef __cplusplus
 extern "C" {
#endif 

#ifndef __ASSEMBLY__
#include <stdint.h>
#ifndef __cplusplus
typedef volatile const uint32_t RoReg; /**< Read only 32-bit register (volatile const unsigned int) */
#else
typedef volatile       uint32_t RoReg; /**< Read only 32-bit register (volatile const unsigned int) */
#endif
typedef volatile       uint32_t WoReg; /**< Write only 32-bit register (volatile unsigned int) */
typedef volatile       uint32_t RwReg; /**< Read-Write 32-bit register (volatile unsigned int) */
#endif

/* ************************************************************************** */
/*   CMSIS DEFINITIONS FOR SAM4S16A */
/* ************************************************************************** */
/** \addtogroup SAM4S16A_cmsis CMSIS Definitions */
/*@{*/

/**< Interrupt Number Definition */
typedef enum IRQn
{
/******  Cortex-M4 Processor Exceptions Numbers ******************************/
  NonMaskableInt_IRQn   = -14, /**<  2 Non Maskable Interrupt                */
  MemoryManagement_IRQn = -12, /**<  4 Cortex-M4 Memory Management Interrupt */
  BusFault_IRQn         = -11, /**<  5 Cortex-M4 Bus Fault Interrupt         */
  UsageFault_IRQn       = -10, /**<  6 Cortex-M4 Usage Fault Interrupt       */
  SVCall_IRQn           = -5,  /**< 11 Cortex-M4 SV Call Interrupt           */
  DebugMonitor_IRQn     = -4,  /**< 12 Cortex-M4 Debug Monitor Interrupt     */
  PendSV_IRQn           = -2,  /**< 14 Cortex-M4 Pend SV Interrupt           */
  SysTick_IRQn          = -1,  /**< 15 Cortex-M4 System Tick Interrupt       */
/******  SAM4S16A specific Interrupt Numbers *********************************/
  
  SUPC_IRQn            =  0, /**<  0 SAM4S16A Supply Controller (SUPC) */
  RSTC_IRQn            =  1, /**<  1 SAM4S16A Reset Controller (RSTC) */
  RTC_IRQn             =  2, /**<  2 SAM4S16A Real Time Clock (RTC) */
  RTT_IRQn             =  3, /**<  3 SAM4S16A Real Time Timer (RTT) */
  WDT_IRQn             =  4, /**<  4 SAM4S16A Watchdog Timer (WDT) */
  PMC_IRQn             =  5, /**<  5 SAM4S16A Power Management Controller (PMC) */
  EFC_IRQn             =  6, /**<  6 SAM4S16A Enhanced Embedded Flash Controller (EFC) */
  UART0_IRQn           =  8, /**<  8 SAM4S16A UART 0 (UART0) */
  UART1_IRQn           =  9, /**<  9 SAM4S16A UART 1 (UART1) */
  PIOA_IRQn            = 11, /**< 11 SAM4S16A Parallel I/O Controller A (PIOA) */
  PIOB_IRQn            = 12, /**< 12 SAM4S16A Parallel I/O Controller B (PIOB) */
  USART0_IRQn          = 14, /**< 14 SAM4S16A USART 0 (USART0) */
  TWI0_IRQn            = 19, /**< 19 SAM4S16A Two Wire Interface 0 (TWI0) */
  TWI1_IRQn            = 20, /**< 20 SAM4S16A Two Wire Interface 1 (TWI1) */
  SPI_IRQn             = 21, /**< 21 SAM4S16A Serial Peripheral Interface (SPI) */
  SSC_IRQn             = 22, /**< 22 SAM4S16A Synchronous Serial Controller (SSC) */
  TC0_IRQn             = 23, /**< 23 SAM4S16A Timer/Counter 0 (TC0) */
  TC1_IRQn             = 24, /**< 24 SAM4S16A Timer/Counter 1 (TC1) */
  TC2_IRQn             = 25, /**< 25 SAM4S16A Timer/Counter 2 (TC2) */
  ADC_IRQn             = 29, /**< 29 SAM4S16A Analog To Digital Converter (ADC) */
  DACC_IRQn            = 30, /**< 30 SAM4S16A Digital To Analog Converter (DACC) */
  PWM_IRQn             = 31, /**< 31 SAM4S16A Pulse Width Modulation (PWM) */
  CRCCU_IRQn           = 32, /**< 32 SAM4S16A CRC Calculation Unit (CRCCU) */
  ACC_IRQn             = 33, /**< 33 SAM4S16A Analog Comparator (ACC) */
  UDP_IRQn             = 34  /**< 34 SAM4S16A USB Device Port (UDP) */
} IRQn_Type;

/**
 * \brief Configuration of the Cortex-M4 Processor and Core Peripherals 
 */

#define __CM4_REV              0x0000 /**< SAM4S16A core revision number ([15:8] revision number, [7:0] patch number) */
#define __MPU_PRESENT          1      /**< SAM4S16A does provide a MPU */
#define __FPU_PRESENT          0      /**< SAM4S16A does not provide a FPU */
#define __NVIC_PRIO_BITS       4      /**< SAM4S16A uses 4 Bits for the Priority Levels */
#define __Vendor_SysTickConfig 0      /**< Set to 1 if different SysTick Config is used */

/*
 * \brief CMSIS includes
 */

//#include <core_cm4.h>

/*@}*/

/* ************************************************************************** */
/**  SOFTWARE PERIPHERAL API DEFINITION FOR SAM4S16A */
/* ************************************************************************** */
/** \addtogroup SAM4S16A_api Peripheral Software API */
/*@{*/

#include "component/ACC.h"
#include "component/ADC.h"
#include "component/CHIPID.h"
#include "component/CRCCU.h"
#include "component/DACC.h"
#include "component/EFC.h"
#include "component/GPBR.h"
#include "component/MATRIX.h"
#include "component/PDC.h"
#include "component/PIO.h"
#include "component/PMC.h"
#include "component/PWM.h"
#include "component/RSTC.h"
#include "component/RTC.h"
#include "component/RTT.h"
#include "component/SPI.h"
#include "component/SSC.h"
#include "component/SUPC.h"
#include "component/TC.h"
#include "component/TWI.h"
#include "component/UART.h"
#include "component/UDP.h"
#include "component/USART.h"
#include "component/WDT.h"
/*@}*/

/* ************************************************************************** */
/*   REGISTER ACCESS DEFINITIONS FOR SAM4S16A */
/* ************************************************************************** */
/** \addtogroup SAM4S16A_reg Registers Access Definitions */
/*@{*/

#include "instance/SSC.h"
#include "instance/SPI.h"
#include "instance/TC0.h"
#include "instance/TWI0.h"
#include "instance/TWI1.h"
#include "instance/PWM.h"
#include "instance/USART0.h"
#include "instance/UDP.h"
#include "instance/ADC.h"
#include "instance/DACC.h"
#include "instance/ACC.h"
#include "instance/CRCCU.h"
#include "instance/MATRIX.h"
#include "instance/PMC.h"
#include "instance/UART0.h"
#include "instance/CHIPID.h"
#include "instance/UART1.h"
#include "instance/EFC.h"
#include "instance/PIOA.h"
#include "instance/PIOB.h"
#include "instance/RSTC.h"
#include "instance/SUPC.h"
#include "instance/RTT.h"
#include "instance/WDT.h"
#include "instance/RTC.h"
#include "instance/GPBR.h"
/*@}*/

/* ************************************************************************** */
/*   PERIPHERAL ID DEFINITIONS FOR SAM4S16A */
/* ************************************************************************** */
/** \addtogroup SAM4S16A_id Peripheral Ids Definitions */
/*@{*/

#define ID_SUPC   ( 0) /**< \brief Supply Controller (SUPC) */
#define ID_RSTC   ( 1) /**< \brief Reset Controller (RSTC) */
#define ID_RTC    ( 2) /**< \brief Real Time Clock (RTC) */
#define ID_RTT    ( 3) /**< \brief Real Time Timer (RTT) */
#define ID_WDT    ( 4) /**< \brief Watchdog Timer (WDT) */
#define ID_PMC    ( 5) /**< \brief Power Management Controller (PMC) */
#define ID_EFC    ( 6) /**< \brief Enhanced Embedded Flash Controller (EFC) */
#define ID_UART0  ( 8) /**< \brief UART 0 (UART0) */
#define ID_UART1  ( 9) /**< \brief UART 1 (UART1) */
#define ID_PIOA   (11) /**< \brief Parallel I/O Controller A (PIOA) */
#define ID_PIOB   (12) /**< \brief Parallel I/O Controller B (PIOB) */
#define ID_USART0 (14) /**< \brief USART 0 (USART0) */
#define ID_TWI0   (19) /**< \brief Two Wire Interface 0 (TWI0) */
#define ID_TWI1   (20) /**< \brief Two Wire Interface 1 (TWI1) */
#define ID_SPI    (21) /**< \brief Serial Peripheral Interface (SPI) */
#define ID_SSC    (22) /**< \brief Synchronous Serial Controller (SSC) */
#define ID_TC0    (23) /**< \brief Timer/Counter 0 (TC0) */
#define ID_TC1    (24) /**< \brief Timer/Counter 1 (TC1) */
#define ID_TC2    (25) /**< \brief Timer/Counter 2 (TC2) */
#define ID_ADC    (29) /**< \brief Analog To Digital Converter (ADC) */
#define ID_DACC   (30) /**< \brief Digital To Analog Converter (DACC) */
#define ID_PWM    (31) /**< \brief Pulse Width Modulation (PWM) */
#define ID_CRCCU  (32) /**< \brief CRC Calculation Unit (CRCCU) */
#define ID_ACC    (33) /**< \brief Analog Comparator (ACC) */
#define ID_UDP    (34) /**< \brief USB Device Port (UDP) */
/*@}*/

/* ************************************************************************** */
/*   BASE ADDRESS DEFINITIONS FOR SAM4S16A */
/* ************************************************************************** */
/** \addtogroup SAM4S16A_base Peripheral Base Address Definitions */
/*@{*/

#ifdef __ASSEMBLY__
#define SSC        (0x40004000U) /**< \brief (SSC       ) Base Address */
#define PDC_SSC    (0x40004100U) /**< \brief (PDC_SSC   ) Base Address */
#define SPI        (0x40008000U) /**< \brief (SPI       ) Base Address */
#define PDC_SPI    (0x40008100U) /**< \brief (PDC_SPI   ) Base Address */
#define TC0        (0x40010000U) /**< \brief (TC0       ) Base Address */
#define TWI0       (0x40018000U) /**< \brief (TWI0      ) Base Address */
#define PDC_TWI0   (0x40018100U) /**< \brief (PDC_TWI0  ) Base Address */
#define TWI1       (0x4001C000U) /**< \brief (TWI1      ) Base Address */
#define PDC_TWI1   (0x4001C100U) /**< \brief (PDC_TWI1  ) Base Address */
#define PWM        (0x40020000U) /**< \brief (PWM       ) Base Address */
#define PDC_PWM    (0x40020100U) /**< \brief (PDC_PWM   ) Base Address */
#define USART0     (0x40024000U) /**< \brief (USART0    ) Base Address */
#define PDC_USART0 (0x40024100U) /**< \brief (PDC_USART0) Base Address */
#define UDP        (0x40034000U) /**< \brief (UDP       ) Base Address */
#define ADC        (0x40038000U) /**< \brief (ADC       ) Base Address */
#define PDC_ADC    (0x40038100U) /**< \brief (PDC_ADC   ) Base Address */
#define DACC       (0x4003C000U) /**< \brief (DACC      ) Base Address */
#define PDC_DACC   (0x4003C100U) /**< \brief (PDC_DACC  ) Base Address */
#define ACC        (0x40040000U) /**< \brief (ACC       ) Base Address */
#define CRCCU      (0x40044000U) /**< \brief (CRCCU     ) Base Address */
#define MATRIX     (0x400E0200U) /**< \brief (MATRIX    ) Base Address */
#define PMC        (0x400E0400U) /**< \brief (PMC       ) Base Address */
#define UART0      (0x400E0600U) /**< \brief (UART0     ) Base Address */
#define PDC_UART0  (0x400E0700U) /**< \brief (PDC_UART0 ) Base Address */
#define CHIPID     (0x400E0740U) /**< \brief (CHIPID    ) Base Address */
#define UART1      (0x400E0800U) /**< \brief (UART1     ) Base Address */
#define PDC_UART1  (0x400E0900U) /**< \brief (PDC_UART1 ) Base Address */
#define EFC        (0x400E0A00U) /**< \brief (EFC       ) Base Address */
#define PIOA       (0x400E0E00U) /**< \brief (PIOA      ) Base Address */
#define PDC_PIOA   (0x400E0F68U) /**< \brief (PDC_PIOA  ) Base Address */
#define PIOB       (0x400E1000U) /**< \brief (PIOB      ) Base Address */
#define RSTC       (0x400E1400U) /**< \brief (RSTC      ) Base Address */
#define SUPC       (0x400E1410U) /**< \brief (SUPC      ) Base Address */
#define RTT        (0x400E1430U) /**< \brief (RTT       ) Base Address */
#define WDT        (0x400E1450U) /**< \brief (WDT       ) Base Address */
#define RTC        (0x400E1460U) /**< \brief (RTC       ) Base Address */
#define GPBR       (0x400E1490U) /**< \brief (GPBR      ) Base Address */
#else
#define SSC        ((Ssc    *)0x40004000U) /**< \brief (SSC       ) Base Address */
#define PDC_SSC    ((Pdc    *)0x40004100U) /**< \brief (PDC_SSC   ) Base Address */
#define SPI        ((Spi    *)0x40008000U) /**< \brief (SPI       ) Base Address */
#define PDC_SPI    ((Pdc    *)0x40008100U) /**< \brief (PDC_SPI   ) Base Address */
#define TC0        ((Tc     *)0x40010000U) /**< \brief (TC0       ) Base Address */
#define TWI0       ((Twi    *)0x40018000U) /**< \brief (TWI0      ) Base Address */
#define PDC_TWI0   ((Pdc    *)0x40018100U) /**< \brief (PDC_TWI0  ) Base Address */
#define TWI1       ((Twi    *)0x4001C000U) /**< \brief (TWI1      ) Base Address */
#define PDC_TWI1   ((Pdc    *)0x4001C100U) /**< \brief (PDC_TWI1  ) Base Address */
#define PWM        ((Pwm    *)0x40020000U) /**< \brief (PWM       ) Base Address */
#define PDC_PWM    ((Pdc    *)0x40020100U) /**< \brief (PDC_PWM   ) Base Address */
#define USART0     ((Usart  *)0x40024000U) /**< \brief (USART0    ) Base Address */
#define PDC_USART0 ((Pdc    *)0x40024100U) /**< \brief (PDC_USART0) Base Address */
#define UDP        ((Udp    *)0x40034000U) /**< \brief (UDP       ) Base Address */
#define ADC        ((Adc    *)0x40038000U) /**< \brief (ADC       ) Base Address */
#define PDC_ADC    ((Pdc    *)0x40038100U) /**< \brief (PDC_ADC   ) Base Address */
#define DACC       ((Dacc   *)0x4003C000U) /**< \brief (DACC      ) Base Address */
#define PDC_DACC   ((Pdc    *)0x4003C100U) /**< \brief (PDC_DACC  ) Base Address */
#define ACC        ((Acc    *)0x40040000U) /**< \brief (ACC       ) Base Address */
#define CRCCU      ((Crccu  *)0x40044000U) /**< \brief (CRCCU     ) Base Address */
#define MATRIX     ((Matrix *)0x400E0200U) /**< \brief (MATRIX    ) Base Address */
#define PMC        ((Pmc    *)0x400E0400U) /**< \brief (PMC       ) Base Address */
#define UART0      ((Uart   *)0x400E0600U) /**< \brief (UART0     ) Base Address */
#define PDC_UART0  ((Pdc    *)0x400E0700U) /**< \brief (PDC_UART0 ) Base Address */
#define CHIPID     ((Chipid *)0x400E0740U) /**< \brief (CHIPID    ) Base Address */
#define UART1      ((Uart   *)0x400E0800U) /**< \brief (UART1     ) Base Address */
#define PDC_UART1  ((Pdc    *)0x400E0900U) /**< \brief (PDC_UART1 ) Base Address */
#define EFC        ((Efc    *)0x400E0A00U) /**< \brief (EFC       ) Base Address */
#define PIOA       ((Pio    *)0x400E0E00U) /**< \brief (PIOA      ) Base Address */
#define PDC_PIOA   ((Pdc    *)0x400E0F68U) /**< \brief (PDC_PIOA  ) Base Address */
#define PIOB       ((Pio    *)0x400E1000U) /**< \brief (PIOB      ) Base Address */
#define RSTC       ((Rstc   *)0x400E1400U) /**< \brief (RSTC      ) Base Address */
#define SUPC       ((Supc   *)0x400E1410U) /**< \brief (SUPC      ) Base Address */
#define RTT        ((Rtt    *)0x400E1430U) /**< \brief (RTT       ) Base Address */
#define WDT        ((Wdt    *)0x400E1450U) /**< \brief (WDT       ) Base Address */
#define RTC        ((Rtc    *)0x400E1460U) /**< \brief (RTC       ) Base Address */
#define GPBR       ((Gpbr   *)0x400E1490U) /**< \brief (GPBR      ) Base Address */
#endif /* __ASSEMBLY__ */
/*@}*/

/* ************************************************************************** */
/*   PIO DEFINITIONS FOR SAM4S16A */
/* ************************************************************************** */
/** \addtogroup SAM4S16A_pio Peripheral Pio Definitions */
/*@{*/

#include "pio/SAM4S16A.h"
/*@}*/

/* ************************************************************************** */
/*   MEMORY MAPPING DEFINITIONS FOR SAM4S16A */
/* ************************************************************************** */

#define IFLASH_SIZE 0x100000
#define IRAM_SIZE   0x20000

#define IFLASH_ADDR  (0x00400000u) /**< Internal Flash base address */
#define IROM_ADDR    (0x00800000u) /**< Internal ROM base address */
#define IRAM_ADDR    (0x20000000u) /**< Internal RAM base address */
#define EBI_CS0_ADDR (0x60000000u) /**< EBI Chip Select 0 base address */
#define EBI_CS1_ADDR (0x61000000u) /**< EBI Chip Select 1 base address */
#define EBI_CS2_ADDR (0x62000000u) /**< EBI Chip Select 2 base address */
#define EBI_CS3_ADDR (0x63000000u) /**< EBI Chip Select 3 base address */

#ifdef __cplusplus
}
#endif

/*@}*/

#endif /* _SAM4S16A_ */
