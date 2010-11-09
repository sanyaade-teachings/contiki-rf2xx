/*   Copyright (c) 2008, Swedish Institute of Computer Science
 *  All rights reserved. 
 *
 *  Additional fixes for AVR contributed by:
 *
 *	Colin O'Flynn coflynn@newae.com
 *	Eric Gnoske egnoske@gmail.com
 *	Blake Leverett bleverett@gmail.com
 *	Mike Vidales mavida404@gmail.com
 *	Kevin Brown kbrown3@uccs.edu
 *	Nate Bohlmann nate@elfwerks.com
 *
 *  ATMEL RUM v1.0.0 porting by:
 *
 *      Ilya Dmitrichenko errordeveloper@gmail.com
 *
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of the copyright holders nor the names of
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

/* TODO: Doxygenize all comments correctly */
/**
 *    \addtogroup hal
 *    \{
 */

/**
 *  \file
 *  \brief This file contains low-level radio driver code.
 *
 *   $Id: hal.h,v 1.5 2010/02/26 21:15:28 dak664 Exp $
*/

#ifndef HAL_AVR_H
#define HAL_AVR_H
/*============================ INCLUDE =======================================*/
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/crc16.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include "contiki-conf.h"

/* TODO: adjust ATMEL_RADIO and the PLATFORM definitions below to work together */
#ifdef ATMEL_RADIO == RF23x
#define RADIO_BAND B2400
#include "at86rf23x_registermap.h"
#ifdef ATMEL_RADIO == RF212
#define RADIO_BAND B900
#include "at86rf212_registermap.h"
#else
#error "Please define ATMEL_RADIO, use RF23x or RF212"
#endif

/*============================ MACROS ========================================*/

/**\name Macros defined for the radio transceiver's access modes.
 *
 * \brief These functions are implemented as macros since they are used very often.
 * \{
 */
#define HAL_DUMMY_READ         (0x00) /**<  Dummy value for the SPI. */

#define HAL_TRX_CMD_RW         (0xC0) /**<  Register Write (short mode). */
#define HAL_TRX_CMD_RR         (0x80) /**<  Register Read (short mode). */
#define HAL_TRX_CMD_FW         (0x60) /**<  Frame Transmit Mode (long mode). */
#define HAL_TRX_CMD_FR         (0x20) /**<  Frame Receive Mode (long mode). */
#define HAL_TRX_CMD_SW         (0x40) /**<  SRAM Write. */
#define HAL_TRX_CMD_SR         (0x00) /**<  SRAM Read. */
#define HAL_TRX_CMD_RADDRM     (0x7F) /**<  Register Address Mask. */

#define HAL_CALCULATED_CRC_OK   (0) /**<  CRC calculated over the frame including the CRC field should be 0. */
/** \} */

// TEST CODE /* PORTNOTE: this comes from Contiki, what is it? */
#define TRIG1 DDRB |= 0x04, PINB |= 0x04
#define TRIG2 DDRD |= 0x80, PIND |= 0x80

/*============================ PLATFORM SPECIFIC MACROS ======================*/
/**
   \name Platform types.

   Note that the order of these definitions is not arbitrary, and
   there are comparisons of the \ref PLATFORM variable based on
   position within the list.  In other words, re-arranging the list
   can break the code.  Feel free to add new platforms on the end of
   the list.  Note that an RCB230 board can be loaded with an 'RF231
   chip, and vice-versa.  The firmware identifies which radio chip is
   loaded and acts accordingly.  The RCB230/231 distinction is in
   which board is being used, not which chip is loaded.

   \{
*/

#define RCB230     1  /**< Radio control board, designed for use with RF230 */
#define RCB231     2  /**< Radio control board, designed for use with RF231 */
#define RCB212     3  /**< Radio control board, designed for use with RF212 (900MHz only) */
#define RCBSIP     4  /**< Radio control board, designed for use with RF231 */
#define RAVEN      5  /**< Raven demo board (with LCD display) [ATmega1284P] */
#define RAVENUSB   6  /**< Raven demo board (USB version) [AT90USB1287] */
#define SPITFIRE   7  /**< Small sensor demo board (900MHz only) */
#define ZIGBIT09   8  /**< ZigBit module, operating in the 900MHz band */
#define ZIGBIT24   9  /**< ZigBit module, operating in the 2.4GHz band */
#define DSK001    10  /**< TRT Button, model DSK001 */
/** \} */

/**
   \def RADIO_BAND
   \brief The RADIO_BAND macro is set to one particular band based
   on which platform selected for compilation.  Do not manually set
   this macro.

   \name RF Bands supported

   The \ref RADIO_BAND macro is set to one of the following two bands.
   \{
*/
#define BAND900    1
#define BAND2400   2
/** \} */

#if defined DOXYGEN
/**
   \brief Defines the platform for which we are building the firmware.
   See \ref RCB230 under "Platform types" above for possible values.
*/

    #define PLATFORM RCB231
    #define F_CPU 8000000UL
#endif

#if ( PLATFORM == RCB230 ) /* PORTREF: line 209 */
/* RCB with ATmega1281V and RF230 (RCB rev B) */

	#ifndef __AVR_ATmega1281__
		#error "Incorrect MCU for Platform! Check Makefile"
	#endif

	/* SPI */
	#   define SSPORT     B
	#   define SSPIN      (0x00)
	#   define SPIPORT    B
	#   define MOSIPIN    (0x02)
	#   define MISOPIN    (0x03)
	#   define SCKPIN     (0x01)
	/* RST */
	#   define RSTPORT    B
	#   define RSTPIN     (0x05)
	/* SLP */
	#   define SLPTRPORT  B
	#   define SLPTRPIN   (0x04)
	/* TMR */
	#   define TICKTIMER  3
	#   define HAS_SPARE_TIMER
	/* IRQ */
	#   define IRQPORT    D
	#   define IRQPIN     (0x04)

	#   define ADPORT     F
	#   define ADPIN      (0x00)
	#   define DIDR       DIDR0

	#   define USART      1
	#   define USARTVECT  USART1_RX_vect

	// HAS_CW_MODE?
	// TXCWPORT?
	// TXCWPIN?
	/* TRX */
	#   define RADIO_BAND BAND2400
	#   define RADIO_VECT TIMER1_CAPT_vect
	/* HAL */
	#   define HAL_ENABLE_RADIO_INTERRUPT( ) ( TIMSK1 |= ( 1 << ICIE1 ) ),  \
			TCCR1B = HAL_TCCR1B_CONFIG,   /* Set clock prescaler */ \
			TIFR1 |= (1 << ICF1)        /* Clear Input Capture Flag. */
	#   define HAL_DISABLE_RADIO_INTERRUPT( ) ( TIMSK1 &= ~( 1 << ICIE1 ), TCCR1B = 0 )
	#   define HAL_INIT_ADC() DIDR0 |= (1 << ADPIN), ADMUX = 0xC0 | ADPIN, ADCSRA = 0x80
	#   define HAL_STOP_ADC()  ADCSRA &= ~0x80
	#   define HAL_SAMPLE_ADC() ADCSRA |= (1 << ADSC)
	#   define HAL_WAIT_ADC() while (!(ADCSRA & (1<<ADIF))) {;}; ADCSRA |= (1<<ADIF)
	#   define HAL_READ_ADC() ADC
	/* LED */
	#define LED_INIT() (DDRE |= ((1<<2) | (1<<3) | (1<<4)), PORTE |= ((1<<2) | (1<<3) | (1<<4)))
	#define LED_ON(led) (PORTE &= ~(1 << (led+1))) /* LED_ON(led), where led = 1-3 */
	#define LED_OFF(led) (PORTE |= 1 << (led+1))
	/* BTN */
	#define BUTTON_SETUP() (DDRE &= ~(1 << PE5), PORTE |= (1 << PE5))
	#define BUTTON_PRESSED() (DDRE &= ~0x20, PORTE |= 0x20, !(PINE & 0x20))

#elif ( PLATFORM == RCB231 ) /* PORTREF: line 101 */
/* RCB with ATmega1281 and RF231 */

	#ifndef __AVR_ATmega1281__
		#error "Incorrect MCU for Platform! Check Makefile"
	#endif

/**
   \name Pin configurations for the RCB231 platform.

   Change these values to port to other platforms.
   \{
*/
	/* SPI */
	#   define SSPORT     B          /**< Radio (SPI Slave) Select port */
	#   define SSPIN      (0x00)     /**< Radio (SPI Slave) Select pin */
	#   define SPIPORT    B          /**< Radio SPI port */
	#   define MOSIPIN    (0x02)     /**< Radio SPI MOSI pin */
	#   define MISOPIN    (0x03)     /**< Radio SPI MISO pin */
	#   define SCKPIN     (0x01)     /**< Radio SPI SCK pin */
	/* RST */
	#   define RSTPORT    B          /**< Radio reset port */
	#   define RSTPIN     (0x05)     /**< Radio reset pin */
	/* SLP */
	#   define SLPTRPORT  B          /**< Radio SLP_TR port */
	#   define SLPTRPIN   (0x04)     /**< Radio SLP_TR pin */
	/* TMR */
	#   define TICKTIMER  3          /**< AVR timer used for tick timing */
	// HAS_SPARE_TIMER?

	#   define ADPORT     F          /**< ADC port */
	#   define ADPIN      (0x00)     /**< ADC pin for sensor input */
	#   define DIDR       DIDR0      /**< AVR DIDR register (see \ref HAL_INIT_ADC) */

	#   define USART      1          /**< AVR UART used for debug serial port */

	// HAS_CW_MODE?
	// TXCWPORT?
	// TXCWPIN?
	/* TRX */
	#   define RADIO_BAND BAND2400	 /**< Radio Frequency Band */
	#   define RADIO_VECT INT0_vect  /**< Radio Interrupt Vector */
	/* HAL */
	    /** Macro to enable the radio interrupt. */
	#   define HAL_ENABLE_RADIO_INTERRUPT( ) EICRA |= 3, EIMSK |= 1
	    /** Macro to disable the radio interrupt. */
	#   define HAL_DISABLE_RADIO_INTERRUPT( ) EICRA &= ~3, EIMSK &= ~1
	    /** Macro to initialize the ADC converter.
	     * note that on some platforms, there is no ADC so this macro does nothing. */
	#   define HAL_INIT_ADC() DIDR0 |= (1 << ADPIN), ADMUX = 0xC0 | ADPIN, ADCSRA = 0x84
	    /** Macro to stop the ADC. */
	#   define HAL_STOP_ADC() ADCSRA &= ~0x80
	    /** Macro to sample the ADC. */
	#   define HAL_SAMPLE_ADC() ADCSRA |= (1 << ADSC) | (1<< ADIF)
	    /** Macro to wait for the ADC to finish sampling. */
	#   define HAL_WAIT_ADC() while (!(ADCSRA & (1<<ADIF))) {;}; ADCSRA |= (1<<ADIF);
	    /** Macro to READ the ADC value. */
	#   define HAL_READ_ADC() ADC
	/* LED */
	#define LED_INIT() (DDRE |= ((1<<2) | (1<<3) | (1<<4)), PORTE |= ((1<<2) | (1<<3) | (1<<4)))
	#define LED_ON(led) (PORTE &= ~(1 << (led+1))) /* LED_ON(led), where led = 1-3 */
	#define LED_OFF(led) (PORTE |= 1 << (led+1))
	/* BTN */
	#define BUTTON_SETUP() (DDRE &= ~(1 << PE5), PORTE |= (1 << PE5))
	#define BUTTON_PRESSED() (DDRE &= ~0x20, PORTE |= 0x20, !(PINE & 0x20))

/** \} */

#elif ( PLATFORM == RCBSIP ) /* PORTREF: line 259 */
/* RCB on SIP with ATmega1284P and RF231 */

	#ifndef __AVR_ATmega1284P__
		#error "Incorrect MCU for Platform! Check Makefile"
	#endif

	/* SPI */
	#   define SSPORT     B
	#   define SSPIN      (0x04)
	#   define SPIPORT    B
	#   define MOSIPORT   B
	#   define MOSIPIN    (0x05)
	#   define MISOPIN    (0x06)
	#   define SCKPORT    B
	#   define SCKPIN     (0x07)
	/* RST */
	#   define RSTPORT    B
	#   define RSTPIN     (0x02)
	/* SLP */
	#   define SLPTRPORT  B
	#   define SLPTRPIN   (0x03)
	/* TMR */
	#   define TICKTIMER  3
	// HAS_SPARE_TIMER?

	#   define PB0 0
	#   define PD4 4
	#   define PC0 0
	#   define PC4 4
	#   define PC6 6
	#   define PC7 7

	#   define USART      1

	/* TRX */
	#   define RADIO_BAND BAND2400
	#   define RADIO_VECT TIMER1_CAPT_vect
	/* HAL */
	#   define HAL_ENABLE_RADIO_INTERRUPT( ) ( TIMSK1 |= ( 1 << ICIE1 ) ),  \
			TCCR1B = HAL_TCCR1B_CONFIG,   /* Set clock prescaler */ \
			TIFR1 |= (1 << ICF1)        /* Clear Input Capture Flag. */
	#   define HAL_DISABLE_RADIO_INTERRUPT( ) ( TIMSK1 &= ~( 1 << ICIE1 ), TCCR1B = 0)
	#   define HAL_INIT_ADC()
	#   define HAL_STOP_ADC()
	#   define HAL_SAMPLE_ADC()
	#   define HAL_WAIT_ADC()
	#   define HAL_READ_ADC() 0
	/* LED */
	#define LED_INIT() DDRD |= (1 << PD4), PORTD |= ~(1 << PD4)
	#define LED_ON(led) DDRD |= (1 << PD4), PORTD &= ~(1 << PD4) /* LED_ON(led), where led = 1-3 */
	#define LED_OFF(led) DDRD &= ~(1 << PD4), PORTD |= (1 << PD4)
	/* BTN */
	#define BUTTON_SETUP() (DDRB &= ~(1 << PB0), PORTB |= (1 << PB0))
	#define BUTTON_PRESSED()  (!(PINB & (1 << PB0)))

#elif ( PLATFORM == RCB212 ) /* PORTREF: line 254 */
/* RCB with ATmega1281 and RF212 (900MHz only) */

	#ifndef __AVR_ATmega1281__
		#error "Incorrect MCU for Platform! Check Makefile"
	#endif

	/* SPI */
	#   define SSPORT     B
	#   define SSPIN      (0x00)
	#   define SPIPORT    B
	#   define MOSIPIN    (0x02)
	#   define MISOPIN    (0x03)
	#   define SCKPIN     (0x01)
	/* RST */
	#   define RSTPORT    B
	#   define RSTPIN     (0x05)
	/* SLP */
	#   define SLPTRPORT  B
	#   define SLPTRPIN   (0x04)
	/* TMR */
	#   define TICKTIMER  3
	// HAS_SPARE_TIMER?

	#   define ADPORT     F
	#   define ADPIN      (0x00)
	#   define DIDR       DIDR0

	#   define USART      1

	/* TRX */
	#   define RADIO_BAND BAND900
	#   define RADIO_VECT INT0_vect
	/* HAL */
	#   define HAL_ENABLE_RADIO_INTERRUPT( ) EICRA |= 3, EIMSK |= 1
	#   define HAL_DISABLE_RADIO_INTERRUPT( ) EICRA &= ~3, EIMSK &= ~1
	#   define HAL_INIT_ADC() DIDR0 |= (1 << ADPIN), ADMUX = 0xC0 | ADPIN, ADCSRA = 0x84
	#   define HAL_STOP_ADC() ADCSRA &= ~0x80
	#   define HAL_SAMPLE_ADC() ADCSRA |= (1 << ADSC) | (1<< ADIF)
	#   define HAL_WAIT_ADC() while (!(ADCSRA & (1<<ADIF))) {;}; ADCSRA |= (1<<ADIF)
	#   define HAL_READ_ADC() ADC
	/* LED */
	#define LED_INIT() (DDRE |= ((1<<2) | (1<<3) | (1<<4)), PORTE |= ((1<<2) | (1<<3) | (1<<4)))
	#define LED_ON(led) (PORTE &= ~(1 << (led+1))) /* LED_ON(led), where led = 1-3 */
	#define LED_OFF(led) (PORTE |= 1 << (led+1))
	/* BTN */
	#define BUTTON_SETUP() (DDRE &= ~(1 << PE5), PORTE |= (1 << PE5))
	#define BUTTON_PRESSED() (DDRE &= ~0x20, PORTE |= 0x20, !(PINE & 0x20))

//#elif HARWARE_REVISION == ZIGBIT /* PORTNOTE: Doesn't appear to be in Atmel definitions, comment it out for now. */
/* 1281V Zigbit */
/*
#   define SSPORT     B
#   define SSPIN      (0x00)
#   define SPIPORT    B
#   define MOSIPIN    (0x02)
#   define MISOPIN    (0x03)
#   define SCKPIN     (0x01)
#   define RSTPORT    A
#   define RSTPIN     (0x07)
#   define IRQPORT    E
#   define IRQPIN     (0x05)
#   define SLPTRPORT  B
#   define SLPTRPIN   (0x04)
#   define TXCWPORT   B
#   define TXCWPIN    (0x07)
#   define USART      1
#   define USARTVECT  USART1_RX_vect
*/
//#   define TICKTIMER  3
//#   define HAS_SPARE_TIMER // Not used

#elif ( PLATFORM == RAVEN ) /* PORTREF: line 298 */
/* Raven LCD with ATmega1284P */

	#ifndef __AVR_ATmega1284P__
		#error "Incorrect MCU for Platform! Check Makefile"
	#endif

	/* SPI */
	#   define SSPORT     B
	#   define SSPIN      (0x04)
	#   define SPIPORT    B
	#   define MOSIPIN    (0x05)
	#   define MISOPIN    (0x06)
	#   define SCKPIN     (0x07)
	/* RST */
	#   define RSTPORT    B
	#   define RSTPIN     (0x01)
	/* SLP */
	#   define SLPTRPORT  B
	#   define SLPTRPIN   (0x03)
	/* TMR */
	#   define TICKTIMER  3
	#   define HAS_SPARE_TIMER
	/* IRQ */
	#   define IRQPORT    D
	#   define IRQPIN     (0x06)
	
	#   define PC4 4
	#   define PC6 6
	#   define PC7 7

	#   define USART      0 /* PORTNOTE: this was 1 */
	#   define USARTVECT  USART1_RX_vect

	#   define HAS_CW_MODE
	#   define TXCWPORT   B
	#   define TXCWPIN    (0x00)
	/* TRX */
	#   define RADIO_BAND BAND2400
	#   define RADIO_VECT TIMER1_CAPT_vect
	/* HAL */
	#   define HAL_ENABLE_RADIO_INTERRUPT( ) ( TIMSK1 |= ( 1 << ICIE1 ) ),  \
			TCCR1B = HAL_TCCR1B_CONFIG,   /* Set clock prescaler */ \
			TIFR1 |= (1 << ICF1)        /* Clear Input Capture Flag. */
	#   define HAL_DISABLE_RADIO_INTERRUPT( ) ( TIMSK1 &= ~( 1 << ICIE1 ) )
	#   define HAL_INIT_ADC() /* NILL */
	#   define HAL_STOP_ADC() /* NILL */
	#   define HAL_SAMPLE_ADC() /* NILL */
	#   define HAL_WAIT_ADC() /* NILL */
	#   define HAL_READ_ADC() ADC
	/* LED */
	#define LED_INIT()
	/* LED_ON(led), where led = 1-3 */
	/* Needs code programmed into Mega3290 to work!!
	 * RAVEN only has one LED - so we never check which one... should do that probably. */
	#define LED_ON(led)
	#define LED_OFF(led)
	/* BTN */
	/* Needs code programmed into Mega3290 to work!! */
	#define BUTTON_SETUP()
	#define BUTTON_PRESSED() 0

#elif ( PLATFORM == RAVENUSB ) /* || ( RAVEN_REVISION == RAVENUSB_C ) */ /* PORTREF: line 389 */
/* Raven USB with AT90USB1287 */

	#ifndef __AVR_AT90USB1287__
		#error "Incorrect MCU for Platform! Check Makefile"
	#endif

	/* SPI */
	#   define SSPORT     B
	#   define SSPIN      (0x00)
	#   define SPIPORT    B
	#   define MOSIPIN    (0x02)
	#   define MISOPIN    (0x03)
	#   define SCKPIN     (0x01)
	/* RST */
	#   define RSTPORT    B
	#   define RSTPIN     (0x05)
	/* SLP */
	#   define SLPTRPORT  B
	#   define SLPTRPIN   (0x04)
	/* TMR */
	#   define TICKTIMER  3
	#   define HAS_SPARE_TIMER
	/* IRQ */
	#   define IRQPORT    D
	#   define IRQPIN     (0x04)

	#   define USART      1
	#   define USARTVECT  USART1_RX_vect

	#   define HAS_CW_MODE
	#   define TXCWPORT   B
	#   define TXCWPIN    (0x07)
	/* TRX */
	#   define RADIO_BAND BAND2400
	#   define RADIO_VECT TIMER1_CAPT_vect
	/* HAL */
	#   define HAL_ENABLE_RADIO_INTERRUPT( ) ( TIMSK1 |= ( 1 << ICIE1 ) ),  \
			TCCR1B = HAL_TCCR1B_CONFIG,   /* Set clock prescaler */ \
			TIFR1 |= (1 << ICF1)        /* Clear Input Capture Flag. */
	#   define HAL_DISABLE_RADIO_INTERRUPT( ) ( TIMSK1 &= ~( 1 << ICIE1 ), TCCR1B = 0 )
	#   define HAL_INIT_ADC()
	#   define HAL_STOP_ADC()
	#   define HAL_WAIT_ADC()
	#   define HAL_READ_ADC() 0
	#   define HAL_SAMPLE_ADC()
	/* LED */
	#define Leds_init()                 (DDRD  |=  0xA0, DDRE  |=  0xC0)
	#define Leds_on()                   (PORTD |=  0x80, PORTD &= ~0x40, PORTE &=  ~0xC0)
	#define Leds_off()                  (PORTD &= ~0x80, PORTD |=  0x40, PORTE |=   0xC0)
	#define Led0_on()                   (PORTD |=  0x80)
	#define Led1_on()                   (PORTD &= ~0x20)
	#define Led2_on()                   (PORTE &= ~0x80)
	#define Led3_on()                   (PORTE &= ~0x40)
	#define Led0_off()                  (PORTD &= ~0x80)
	#define Led1_off()                  (PORTD |=  0x20)
	#define Led2_off()                  (PORTE |=  0x80)
	#define Led3_off()                  (PORTE |=  0x40)
	#define Led0_toggle()               (PIND |= 0x80)
	#define Led1_toggle()               (PIND |= 0x20)
	#define Led2_toggle()               (PINE |= 0x80)
	#define Led3_toggle()               (PINE |= 0x40)
	#define LED_INIT()                  Leds_init()
	/* LED_ON(led), where led doesn't matter - there is only one LED on the board. */
	#define LED_ON(led)                 Led0_on()
	#define LED_OFF(led)                Led0_off()
	/* BTN */
	/* This platform has no buttons. */
	#define BUTTON_SETUP()
	#define BUTTON_PRESSED()        0

#elif ( PLATFORM == SPITFIRE ) /* PORTREF: line 348 */
/* Spitfire with  ATmega328P and ATmega168P */

	#if (!defined(__AVR_ATmega328P__) && !defined(__AVR_ATmega168P__))
		#error "Incorrect MCU for Platform! Check Makefile"
	#endif

	/* SPI */
	#   define SSPORT     B
	#   define SSPIN      (0x02)
	#   define SPIPORT    B
	#   define MOSIPIN    (0x03)
	#   define MISOPIN    (0x04)
	#   define SCKPIN     (0x05)
	/* RST */
	#   define RSTPORT    B
	#   define RSTPIN     (0x01)
	/* SLP */
	#   define SLPTRPORT  D
	#   define SLPTRPIN   (0x04)
	/* TMR */
	#   define TICKTIMER  1
	// HAS_SPARE_TIMER?
	/* IRQ */
	// IRQ?
	/* TRX */
	#   define RADIO_BAND BAND900
	#   define RADIO_VECT PCINT0_vect

	#   define PD7 7
	
	#   define USART

	// HAS_CW_MODE?
	// TXCWPORT?
	// TXCWPIN?
	/* HAL */
	#   define HAL_ENABLE_RADIO_INTERRUPT( ) PCICR |= (1<<0), PCMSK0 |= (1<<0)
	#   define HAL_DISABLE_RADIO_INTERRUPT( ) PCMSK0 &= ~(1<<0)
	#   define HAL_INIT_ADC()  ADMUX = 0x47, ADCSRA = 0x80
	#   define HAL_STOP_ADC()  ADCSRA &= ~0x80
	#   define HAL_SAMPLE_ADC() ADCSRA |= (1 << ADSC)
	#   define HAL_WAIT_ADC() while (!(ADCSRA & (1<<ADIF))) {;}; ADCSRA |= (1<<ADIF)
	#   define HAL_READ_ADC() ADC
	/* LED */
	#define LED_INIT()             DDRD |= (1 << PD7), PORTD |= (1 << PD7)
	/* LED_ON(led), where led doesn't matter - there is only one LED on the board. */
	#define LED_ON(led)            DDRD |= (1 << PD7), PORTD &= !(1 << PD7)
	#define LED_OFF(led)           DDRD &= ~(1 << PD7), PORTD |= (1 << PD7)
	/* BTN */
	/* This platform has no buttons. */
	#define BUTTON_SETUP()
	#define BUTTON_PRESSED()        0

#elif PLATFORM==ZIGBIT09 || PLATFORM==ZIGBIT24 /* PORTREF: line 446 */
/* ZIGBIT modules (900MHz and 2400MHZ)*/

	#ifndef __AVR_ATmega1281__
		#error "Incorrect MCU for Platform! Check Makefile"
	#endif

	/* SPI */
	#   define SSPORT     B
	#   define SSPIN      (0x00)
	#   define SPIPORT    B
	#   define MOSIPIN    (0x02)
	#   define MISOPIN    (0x03)
	#   define SCKPIN     (0x01)
	/* RST */
	#   define RSTPORT    A
	#   define RSTPIN     (0x07)
	/* SLP */
	#   define SLPTRPORT  B
	#   define SLPTRPIN   (0x04)
	/* TMR */
	#   define TICKTIMER  3
	// HAS_SPARE_TIMER?

	#   define USART      1

	/* TRX */
	/*
	 * #ifndef RADIO_BAND
	 * 	#warning "Setting Radio Frequency Band to 2.4GHz. Please define RADIO_BAND to use 900MHz."
	 * 	#define RADIO_BAND BAND2400
	 * #endif
	 */
	 /* Define which band we're operating in - 900MHz or 2.4GHz. */
	 #if PLATFORM==ZIGBIT24
	     #define RADIO_BAND BAND2400
	 #else
	     #define RADIO_BAND BAND900
	 #endif

	 #    define RADIO_VECT INT5_vect

	/* HAL */
	#   define HAL_ENABLE_RADIO_INTERRUPT( ) EICRB |= 0x0C, EIMSK |= 0x20
	#   define HAL_DISABLE_RADIO_INTERRUPT( ) EICRB &= ~0x0C, EIMSK &= ~0x20

	#   define HAL_INIT_ADC()
	#   define HAL_STOP_ADC()
	#   define HAL_SAMPLE_ADC()
	#   define HAL_WAIT_ADC()
	#   define HAL_READ_ADC() 0

	/* LED */
	// LED's for MESHBEAN USB
	// LED1 = PB5
	// LED2 = PB6
	// LED3 = PB7
	#define Leds_init()      (DDRB  |=  0xE0)
	#define Leds_on()        (PORTB |=  0x80)
	#define Leds_off()       (PORTB &= ~0xE0)
	#define Led0_on()
	#define Led1_on()        (PORTB |=  0x80)
	#define Led2_on()        (PORTB |=  0x40)
	#define Led3_on()        (PORTB |=  0x20)
	#define Led0_off()
	#define Led1_off()       (PORTB &= ~0x80)
	#define Led2_off()       (PORTB &= ~0x40)
	#define Led3_off()       (PORTB &= ~0x20)
	#define Led0_toggle()
	#define Led1_toggle()    (PINB  |= 0x80)
	#define Led2_toggle()    (PINB  |= 0x40)
	#define Led3_toggle()    (PINB  |= 0x20)
	#define LED_INIT()                  Leds_init()
	/* LED_ON(led), where led doesn't matter - there is only one LED on the board. */
	#define LED_ON(led)                 Led1_on()
	#define LED_OFF(led)                Led1_off()
	/* BTN */
	/* PE6, needs pullup, short to gnd when pressed. */
	#define BUTTON_SETUP()     (DDRE &= ~(1 << 6), PINE |= (1 << 6))
	#define BUTTON_PRESSED()   (!(PINE & (1 << 6)))

#elif ( PLATFORM==DSK001 ) /* PORTREF: line 512 */
/* TRT "button" board DSK001 with ATmega328P */

	#ifndef __AVR_ATmega328P__
		#error "Incorrect MCU for Platform! Check Makefile"
	#endif

	/* SPI */
	#   define SSPORT     B
	#   define SSPIN      (0x02)
	#   define SPIPORT    B
	#   define MOSIPIN    (0x03)
	#   define MISOPIN    (0x04)
	#   define SCKPIN     (0x05)
	/* RST */
	#   define RSTPORT    C
	#   define RSTPIN     (0x05)
	/* SLP */
	#   define SLPTRPORT  C
	#   define SLPTRPIN   (0x04)
	/* TMR */
	#   define TICKTIMER  1
	// HAS_SPARE_TIMER?

	#   define USART      0

	/* TRX */
	#   define RADIO_BAND BAND2400
	#   define RADIO_VECT PCINT0_vect
	/* HAL */
	#   define HAL_ENABLE_RADIO_INTERRUPT( ) PCICR |= (1 << PCIE0), PCMSK0 |= (1 << PCINT1)
	#   define HAL_DISABLE_RADIO_INTERRUPT( ) PCMSK0 &= ~(1 << PCINT1)

	#   define HAL_INIT_ADC()    ADMUX = 0xc8, ADCSRA = (1 << ADEN) | (1<<ADPS1) | (1<<ADPS2)
	#   define HAL_STOP_ADC()    ADMUX = 0x0F, ADCSRA = 1<<ADIF
	#   define HAL_SAMPLE_ADC()  ADCSRA |= (1 << ADSC) | (1 << ADIF)
	#   define HAL_WAIT_ADC()    while (!(ADCSRA & (1<<ADIF))) {;}; ADCSRA |= (1<<ADIF)
	#   define HAL_READ_ADC()    ADC

	#   define HAL_SELECT_ACCELZ()   ADMUX = (ADMUX & 0xF0) | 0x02
	#   define HAL_SELECT_ACCELY()   ADMUX = (ADMUX & 0xF0) | 0x01
	#   define HAL_SELECT_ACCELX()   ADMUX = (ADMUX & 0xF0) | 0x00

	#   define HAL_ACCEL_INIT()      DDRC = (DDRC & 0xf0) | (1<<3), PORTC &= 0xf0;
	#   define HAL_ACCEL_ON()        PORTC |= 1<<3
	#   define HAL_ACCEL_OFF()       PORTC &= ~(1<<3)
	/* LED */
	/* LED is on Port D Pin 7 */
	#define Leds_init()   //   (DDRD  |=  0x80, PORTD &= ~0x80)
	#define Leds_on()   (DDRD  |=  0x80, PORTD &= ~0x80)
	#define Leds_off()  (DDRD  &=  ~0x80)
	#define Led0_on()   (DDRD  |=  0x80, PORTD &= ~0x80)
	#define Led1_on()   (DDRD  |=  0x80, PORTD &= ~0x80)
	#define Led2_on()   (DDRD  |=  0x80, PORTD &= ~0x80)
	#define Led3_on()   (DDRD  |=  0x80, PORTD &= ~0x80)
	#define Led0_off()  (DDRD  &=  ~0x80)
	#define Led1_off()  (DDRD  &=  ~0x80)
	#define Led2_off()  (DDRD  &=  ~0x80)
	#define Led3_off()  (DDRD  &=  ~0x80)
	#define Led0_toggle() DDRD = DDRD ^ 0x80)
	#define Led1_toggle()  DDRD = DDRD ^ 0x80
	#define Led2_toggle()  DDRD = DDRD ^ 0x80
	#define Led3_toggle()  DDRD = DDRD ^ 0x80
	#define LED_INIT()                  Leds_init()
	/* LED_ON(led), where led doesn't matter - there is only one LED on the board. */
	#define LED_ON(led)                 Led1_on()
	#define LED_OFF(led)                Led1_off()
	/* BTN */
	/* This platform has no buttons. */
	#define BUTTON_SETUP()
	#define BUTTON_PRESSED()  0

#else

 #ifdef ATMEL_BOARD_SPEC
	#warning "Using Atmel boars specs in hal.h"
	#error "Platform undefined in hal.h"
 #else
	#warning "Using board.h"
	#include "board.h"
 #endif

#endif
/** \} */

/*============================ GENERAL MACROS ================================*/
/**
 * \name Macros used to generate read register names
 * 		from platform-specific definitions of ports.
 *
 * \brief The various CAT macros (DDR, PORT, and PIN)
 * are used to assign port/pin/DDR names to various macro variables.
 * The variables are assigned based on the specific connections
 * made in the hardware.
 * For example TCCR(TICKTIMER,A) can be used in place of TCCR0A
 * if TICKTIMER is defined as 0. This setup allows changing which
 * resources are used on a PCB with minimum of modifications.
 * \{
 */
#define CAT(x, y)      x##y		/**< Concatenate two strings. */
#define CAT2(x, y, z)  x##y##z		/**< Concatenate three strings. */
#define DDR(x)         CAT(DDR,  x)	/**< Data direction register macro. */
#define PORT(x)        CAT(PORT, x)
#define PIN(x)         CAT(PIN,  x)
#define UCSR(num, let) CAT2(UCSR,num,let)
#define RXEN(x)        CAT(RXEN,x)
#define TXEN(x)        CAT(TXEN,x)
#define TXC(x)         CAT(TXC,x)
#define RXC(x)         CAT(RXC,x)
#define RXCIE(x)       CAT(RXCIE,x)
#define UCSZ(x,y)      CAT2(UCSZ,x,y)
#define UBRR(x,y)      CAT2(UBRR,x,y)
#define UDRE(x)        CAT(UDRE,x)
#define UDRIE(x)       CAT(UDRIE,x)
#define UDR(x)         CAT(UDR,x)
#define TCNT(x)        CAT(TCNT,x)
#define TIMSK(x)       CAT(TIMSK,x)
#define TCCR(x,y)      CAT2(TCCR,x,y)
#define COM(x,y)       CAT2(COM,x,y)
#define OCR(x,y)       CAT2(OCR,x,y)
#define CS(x,y)        CAT2(CS,x,y)
#define WGM(x,y)       CAT2(WGM,x,y)
#define OCIE(x,y)      CAT2(OCIE,x,y)
#define COMPVECT(x)    CAT2(TIMER,x,_COMPA_vect)
#define UDREVECT(x)    CAT2(USART,x,_UDRE_vect)
#define RXVECT(x)      CAT2(USART,x,_RX_vect)
/** \} */

/**
 * \name Pin macros
 * \brief These macros convert the platform-specific pin defines into names and functions
 *       that the source code can directly use.
 * \{
 */
#define SLP_TR		SLPTRPIN          /**< Pin number that corresponds to the SLP_TR pin. */
#define DDR_SLP_TR	DDR( SLPTRPORT )  /**< Data Direction Register that corresponds to the port where SLP_TR is connected. */
#define PORT_SLP_TR	PORT( SLPTRPORT ) /**< Port (Write Access) where SLP_TR is connected. */
#define PIN_SLP_TR	PIN( SLPTRPORT )  /**< Pin (Read Access) where SLP_TR is connected. */

#define hal_set_slptr_high( ) ( PORT_SLP_TR |= ( 1 << SLP_TR ) ) /**< This macro pulls the SLP_TR pin high. */
#define hal_set_slptr_low( )  ( PORT_SLP_TR &= ~( 1 << SLP_TR ) ) /**< This macro pulls the SLP_TR pin low. */
#define hal_get_slptr( ) (    ( PIN_SLP_TR & ( 1 << SLP_TR ) ) >> SLP_TR ) /**< Read current state of the SLP_TR pin (High/Low). */

#define RST		RSTPIN		/**< Pin number that corresponds to the RST pin. */
#define DDR_RST		DDR( RSTPORT )	/**< Data Direction Register that corresponds to the port where RST is */
#define PORT_RST	PORT( RSTPORT )	/**< Port (Write Access) where RST is connected. */
#define PIN_RST		PIN( RSTPORT )	/**< Pin (Read Access) where RST is connected. */

#define hal_set_rst_high( )   ( PORT_RST |= ( 1 << RST ) ) /**< This macro pulls the RST pin high. */
#define hal_set_rst_low( )    ( PORT_RST &= ~( 1 << RST ) ) /**< This macro pulls the RST pin low. */
#define hal_get_rst( )        ( ( PIN_RST & ( 1 << RST )  ) >> RST ) /**< Read current state of the RST pin (High/Low). */

#if 0 /* TODO: this can be removed. */
#define HAL_SS_PIN            SSPIN 		/**< The slave select pin. */
#endif

#define HAL_PORT_SPI          PORT( SPIPORT )	/**< The SPI module is located on PORTB. */
#define HAL_DDR_SPI           DDR( SPIPORT )	/**< Data Direction Register for PORTB. */
#define HAL_DD_SS             SSPIN		/**< Data Direction bit for SS. */
#define HAL_DD_SCK            SCKPIN		/**< Data Direction bit for SCK. */
#define HAL_DD_MOSI           MOSIPIN		/**< Data Direction bit for MOSI. */
#define HAL_DD_MISO           MISOPIN		/**< Data Direction bit for MISO. */
#define HAL_PORT_SS           PORT( SSPORT )	/**< The SPI module PORT. */	/* PORTLABLE: COMPAT */
#define HAL_DDR_SS            DDR( SSPORT )	/**< Data Direction register for the SPI port. */ /* PORTLABLE: COMPAT */

#define HAL_SS_HIGH( ) (HAL_PORT_SS |= ( 1 << HAL_DD_SS )) /**< MACRO for pulling SS high. */
#define HAL_SS_LOW( )  (HAL_PORT_SS &= ~( 1 << HAL_DD_SS )) /**< MACRO for pulling SS low. */

/** \} */

/** \name Macros defined for the radio received packet timer (HAL_TIMER1).
 *
 *  \brief These macros are used to define the correct setupt of the AVR's Timer1,
 *  and to ensure that the hal_get_system_time function returns the system time in
 *  symbols (16 us ticks).
 * \{
 */
#if ( F_CPU == 16000000UL )
    #define HAL_TCCR1B_CONFIG ( ( 1 << ICES1 ) | ( 1 << CS12 ) )
    #define HAL_US_PER_SYMBOL ( 1 )
    #define HAL_SYMBOL_MASK   ( 0xFFFFffff )
#elif ( F_CPU == 8000000UL )
    #define HAL_TCCR1B_CONFIG ( ( 1 << ICES1 ) | ( 1 << CS11 ) | ( 1 << CS10 ) )
    #define HAL_US_PER_SYMBOL ( 2 )
    #define HAL_SYMBOL_MASK   ( 0x7FFFffff )
#elif ( F_CPU == 4000000UL )
    #define HAL_TCCR1B_CONFIG ( ( 1 << ICES1 ) | ( 1 << CS11 ) | ( 1 << CS10 ) )
    #define HAL_US_PER_SYMBOL ( 1 )
    #define HAL_SYMBOL_MASK   ( 0xFFFFffff )
#elif ( F_CPU == 2000000UL )
    #define HAL_TCCR1B_CONFIG ( ( 1 << ICES1 ) | ( 1 << CS11 ) )
    #define HAL_US_PER_SYMBOL ( 2 )
    #define HAL_SYMBOL_MASK   ( 0x7FFFffff )
#elif ( F_CPU == 1000000UL )
    #define HAL_TCCR1B_CONFIG ( ( 1 << ICES1 ) | ( 1 << CS11 ) )
    #define HAL_US_PER_SYMBOL ( 2 )
    #define HAL_SYMBOL_MASK   ( 0x7FFFffff )
#else
    #error "Clock speed not supported."
#endif
/** \} */

/**
 * \name Macros for radio operation.
 * \{ 
 */
#define HAL_BAT_LOW_MASK       ( 0x80 ) /**< Mask for the BAT_LOW interrupt. */
#define HAL_TRX_UR_MASK        ( 0x40 ) /**< Mask for the TRX_UR interrupt. */
#define HAL_TRX_END_MASK       ( 0x08 ) /**< Mask for the TRX_END interrupt. */
#define HAL_RX_START_MASK      ( 0x04 ) /**< Mask for the RX_START interrupt. */
#define HAL_PLL_UNLOCK_MASK    ( 0x02 ) /**< Mask for the PLL_UNLOCK interrupt. */
#define HAL_PLL_LOCK_MASK      ( 0x01 ) /**< Mask for the PLL_LOCK interrupt. */
#define HAL_MIN_FRAME_LENGTH   ( 0x03 ) /**< A frame should be at least 3 bytes. */
#define HAL_MAX_FRAME_LENGTH   ( 0x7F ) /**< A frame should no more than 127 bytes. */
/** \} */

/*============================ INTERRUPTION MACROS ===========================*/
#if 0

/* #if HARWARE_REVISION == ZIGBIT */
/* IRQ E5 for Zigbit example */
#define RADIO_VECT INT5_vect
#define HAL_ENABLE_RADIO_INTERRUPT( ) { ( EIMSK |= ( 1 << INT5 ) ) ; EICRB |= 0x0C ; PORTE &= ~(1<<PE5);  DDRE &= ~(1<<DDE5); }
#define HAL_DISABLE_RADIO_INTERRUPT( ) ( EIMSK &= ~( 1 << INT5 ) )

/* #else */

#define RADIO_VECT TIMER1_CAPT_vect
#define HAL_ENABLE_RADIO_INTERRUPT( ) ( TIMSK1 |= ( 1 << ICIE1 ) )
#define HAL_DISABLE_RADIO_INTERRUPT( ) ( TIMSK1 &= ~( 1 << ICIE1 ) )
#endif

#ifndef HAL_ENABLE_RADIO_INTERRUPT
	#warning "HAL_ENABLE_RADIO_INTERRUPT(): is a PLATFORM specific macro, it has to be defined!"
	#error "HAL_ENABLE_RADIO_INTERRUPT(): macro not defined"
#endif

#ifndef HAL_DISABLE_RADIO_INTERRUPT
	#warning "HAL_DISABLE_RADIO_INTERRUPT(): is a PLATFORM specific macro, it has to be defined!"
	#error "HAL_DISABLE_RADIO_INTERRUPT(): macro not defined"
#endif

#define HAL_ENABLE_OVERFLOW_INTERRUPT( ) ( TIMSK1 |= ( 1 << TOIE1 ) ) /* PORTNOTE: Atmel code doesn't have this. */
#define HAL_DISABLE_OVERFLOW_INTERRUPT( ) ( TIMSK1 &= ~( 1 << TOIE1 ) ) /* PORTNOTE: Atmel code doesn't have this. */

/** This macro will protect the following code from interrupts.*/
#define AVR_ENTER_CRITICAL_REGION( ) {uint8_t volatile saved_sreg = SREG; cli( )  /* PORTREF: line 723 */

/** This macro must always be used in conjunction with \ref AVR_ENTER_CRITICAL_REGION
    so that interrupts are enabled again.*/
#define AVR_LEAVE_CRITICAL_REGION( ) SREG = saved_sreg;}  /* PORTREF: line 727 */


/** \brief  Enable the interrupt from the radio transceiver.
 */
#define hal_enable_trx_interrupt( ) HAL_ENABLE_RADIO_INTERRUPT( )  /* PORTREF: line 768 */

/** \brief  Disable the interrupt from the radio transceiver.
 *
 *  \retval 0 if the pin is low, 1 if the pin is high.
 */
#define hal_disable_trx_interrupt( ) HAL_DISABLE_RADIO_INTERRUPT( ) /* PORTREF: line 771 */

/*============================ TYPDEFS =======================================*/
/**
 * \struct hal_rx_frame_t
 * \brief  This struct defines the rx data container.
 *
 * \see hal_frame_read
 */
typedef struct{
	uint8_t length; /**< Length of frame. */
	uint8_t data[ HAL_MAX_FRAME_LENGTH ]; /**< Actual frame data. */
	uint8_t lqi;	/**< LQI value for received frame. */
	bool crc;	/**< Flag - did CRC pass for received frame? */
} hal_rx_frame_t; /* PORTNOTE: Atmel doesn't have the hal_rx_frame_t here. */

/** RX_START event handler callback type.
 *		Is called with timestamp in IEEE 802.15.4 symbols and frame length.
 *		See hal_set_rx_start_event_handler().
 **/
typedef void (*hal_rx_start_isr_event_handler_t) /* PORTREF: line 790 */
		(uint32_t const isr_timestamp, uint8_t const frame_length);

/** RRX_END event handler callback type.
 *		Is called with timestamp in IEEE 802.15.4 symbols and frame length.
 *		See hal_set_trx_end_event_handler().
 **/
typedef void (*hal_trx_end_isr_event_handler_t) /* PORTREF: line 793 */
		(uint32_t const isr_timestamp);

/** TODOC */
typedef void (*rx_callback_t) /* PORTREF: line 795 */
		(uint16_t data);

#if 0 /* TODO */

typedef struct {
	double m;	/**< The slope of the reading versus ADC input */
	double b;	/**< The offset of the reading */
} __attribute__((packed)) eeprom_cal_factors_t; /* TODO: look into mac.c and mac.h */

typedef struct {
	uint8_t eeprom_mac_addr[8];	/**< The node's unique IEEE MAC address */
	eeprom_cal_factors_t cal_fact;	/**< The node's calibration data (see sensor.h) */
	uint16_t data_seconds;		/**< The number of tenth seconds between data readings (see sensor.h) */
} eeprom_contents_t; /* TODO: look into mac.c and mac.h */

#endif

/*============================ PROTOTYPES ====================================*/

/* == Initialization == */
void hal_init( void );
void hal_spi_init( void );

/* == Flags == */
void	hal_reset_flags( void );
uint8_t	hal_get_bat_low_flag( void );
void	hal_clear_bat_low_flag( void );
uint8_t	hal_get_pll_lock_flag( void );
void	hal_clear_pll_lock_flag( void );

/* == Handlers for States and Transitions == */

hal_trx_end_isr_event_handler_t hal_get_trx_end_event_handler( void );
void hal_set_trx_end_event_handler( hal_trx_end_isr_event_handler_t trx_end_callback_handle );
void hal_clear_trx_end_event_handler( void );

hal_rx_start_isr_event_handler_t hal_get_rx_start_event_handler( void );
void hal_set_rx_start_event_handler( hal_rx_start_isr_event_handler_t rx_start_callback_handle );
void hal_clear_rx_start_event_handler( void );

/* == Register Access == */

uint8_t	hal_register_read( uint8_t address );
void hal_register_write( uint8_t address, uint8_t value );

uint8_t hal_subregister_read( uint8_t address,
			      uint8_t mask,
			      uint8_t position );

void hal_subregister_write( uint8_t address,
			    uint8_t mask,
			    uint8_t position,
                            uint8_t value );

void hal_sram_read( uint8_t address, uint8_t length, uint8_t *data );
void hal_sram_write( uint8_t address, uint8_t length, uint8_t *data );

void hal_eeprom_read_block(uint8_t *addr, uint8_t length, uint8_t *dest);
void hal_eeprom_write_block(uint8_t *addr, uint8_t length, uint8_t *src);

void hal_frame_read( hal_rx_frame_t *rx_frame, rx_callback_t rx_callback);
void hal_frame_write( uint8_t *write_buffer, uint8_t length );

#if 0 /* TODO */

/** Macro to retrieve MAC address stored in EEPROM. */
#define hal_get_mac_addr(p) hal_eeprom_read_block( offsetof( eeprom_contents_t, eeprom_mac_addr ), \
				sizeof( typeof( ((eeprom_contents_t*)0)->eeprom_mac_addr ) ), p)

/** Macro to retrieve MAC address stored in EEPROM. */
#define hal_set_mac_addr(p) hal_eeprom_write_block( offsetof( eeprom_contents_t, eeprom_mac_addr ), \
				sizeof( typeof( ((eeprom_contents_t*)0)->eeprom_mac_addr ) ), p)

#endif

#endif /* HAL_AVR_H */
/** \} */
/*EOF*/
