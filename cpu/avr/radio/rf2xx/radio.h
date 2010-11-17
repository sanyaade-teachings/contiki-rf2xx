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
/**
 *    \addtogroup radiorf2xx
 *   @{
 */
/**\file
 * \brief This file contains radio driver macros, typedefs and function prototypes.
 *
 *   $Id: radio.h,v 1.2 2008/10/14 18:37:28 c_oflynn Exp $
 */

#ifndef RADIO_RF2XX_H
#define RADIO_RF2XX_H
/*============================ INCLUDE =======================================*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
/* #include <avr/pgmspace.h> */

#include "hal.h"
#include "contiki.h"
#include "process.h"
#include "driver-conf.h"

/*----------------------------------------------------------------------------*/
/* #include "sicslowmac.h" */

/* #include "dev/leds.h" */
/* #include "dev/spi.h" */

/*----------------------------------------------------------------------------*/
#include "sys/rtimer.h"

#include "net/packetbuf.h"
#include "net/rime/rimestats.h"
#include "net/netstack.h"
#if RF2XX_TIMETABLE_PROFILING
	#include "sys/timetable.h"
	#define rf2xx_timetable_size 16
#endif

#if RF2XX_CONF_TIMESTAMPS
	#include "net/rime/timesynch.h"
	#define TIMESTAMP_LEN 3
#else
	#define TIMESTAMP_LEN 0
#endif

/*============================ MACROS ========================================*/

#if RF2XX_CONF_AUTORETRIES
	#define RF2XX_CONF_AUTORETRIES 2
#endif

#if RF2XX_CONF_AACK
	#define RF2XX_CONF_AACK 1
#endif

#ifndef RF2XX_CONF_AUTO_CRC
//	#ifdef HAL_CALC_CRC
//	#undef HAL_CALC_CRC
//	#endif
	#define RF2XX_CONF_AUTO_CRC 1
#endif

#if WEBSERVER /* See clock.c and httpd-cgi.c */
	#define RADIOSTATS 1
#else
	#define RADIOSTATS 0
#endif 

/*----------------------------------------------------------------------------*/
#ifndef DEBUG
	#define DEBUG 0
#endif

#if DEBUG
	#define PRINTF(...) printf(__VA_ARGS__)
	#define PRINTSHORT(...) printf(__VA_ARGS__)
#else
	#define PRINTF(...)
	#define PRINTSHORT(...) //printf(__VA_ARGS__)
#endif

/* Track flow through driver,
 * see contiki-raven-main.c for example of use.
 */
//#ifndef DEBUGFLOWSIZE
//	#warning "DEBUGFLOWSIZE is set to 64 by default!"
//	#define DEBUGFLOWSIZE 64
//#endif

#if DEBUGFLOWSIZE
	#define DEBUGFLOW(c) if (debugflowsize<(DEBUGFLOWSIZE-1)) debugflow[debugflowsize++]=c
#else
	#warning "DEBUGFLOW() is disabled!"
	#define DEBUGFLOW(c)
#endif

#define FOOTER_LEN	0 /* or '2' ? */
#define CHECKSUM_LEN	2 /* 16-bit CRC checksum */
#define AUX_LEN (CHECKSUM_LEN + TIMESTAMP_LEN + FOOTER_LEN)

#define FOOTER1_CRC_OK      0x80
#define FOOTER1_CORRELATION 0x7f

/*----------------------------------------------------------------------------*/
/* TODO: this has to be adjusted in accordance to hal.c */
#define SUPPORTED_PART_NUMBER                   ( 2 )
#define SUPPORTED_MANUFACTURER_ID               ( 31 )
#define RF230_SUPPORTED_INTERRUPT_MASK          ( 0x0C )

/* TODO: this will be romoved (most probably). */
#define RF230_REVA                              ( 1 )
#define RF230_REVB                              ( 2 )

/*----------------------------------------------------------------------------*/

#define RF2XX_MIN_CHANNEL                       ( 11 )
#define RF2XX_MAX_CHANNEL                       ( 26 )
#define RF2XX_MIN_ED_THRESHOLD                  ( 0 )
#define RF2XX_MAX_ED_THRESHOLD                  ( 15 )
#define RF2XX_MAX_TX_FRAME_LENGTH               ( 127 ) /**< 127 Byte PSDU. */
/* #define RF230_MAX_PACKET_LEN			( 127 ) */

#define TX_PWR_3DBM                             ( 0 )
#define TX_PWR_17_2DBM                          ( 15 )

#define TX_PWR_MAX		TX_PWR_3DBM
#define TX_PWR_MIN		TX_PWR_17_2DBM
#define TX_PWR_UNDEFINED	( TX_PWR_MIN + 1 )

#ifndef RF_CHANNEL
#define RF_CHANNEL		( 26 )
#endif

#define RADIO_CCA_DONE_MASK (1 << 7) /**<  Mask used to check the CCA_DONE bit. */
#define RADIO_CCA_IDLE_MASK (1 << 6) /**<  Mask used to check the CCA_STATUS bit. */
#define RADIO_START_CCA	(1) /**<  Value in the CCA_REQUEST subregister that initiate a cca. */

#define RADIO_TRANSMISSION_SUCCESS  (0)
#define RADIO_BUSY_CHANNEL          (3)
#define RADIO_MIN_IEEE_FRAME_LENGTH (5)

#if RF2XX_CONF_BATTERY_MONITOR
#define BATTERY_MONITOR_HIGHEST_VOLTAGE         ( 15 )
#define BATTERY_MONITOR_VOLTAGE_UNDER_THRESHOLD ( 0 )
#define BATTERY_MONITOR_HIGH_VOLTAGE            ( 1 )
#define BATTERY_MONITOR_LOW_VOLTAGE             ( 0 )
#endif

#if RF2XX_CONF_CALIBRATION
#define FTN_CALIBRATION_DONE                    ( 0 )
#define PLL_DCU_CALIBRATION_DONE                ( 0 )
#define PLL_CF_CALIBRATION_DONE                 ( 0 )
#define RC_OSC_REFERENCE_COUNT_MAX  (1.005*F_CPU*31250UL/8000000UL)
#define RC_OSC_REFERENCE_COUNT_MIN  (0.995*F_CPU*31250UL/8000000UL)
#endif

#define delay_us( us )   ( _delay_loop_2( ( F_CPU / 4000000UL ) * ( us ) ) )

/** \brief  This macro defines the start value for the RADIO_* status constants.
 *
 *          It was chosen to have this macro so that the user can define where
 *          the status returned from the TAT starts. This can be useful in a
 *          system where numerous drivers are used, and some range of status codes
 *          are occupied.
 *
 *  \see radio_status_t
 */
#define RADIO_STATUS_START_VALUE                  ( 0x40 )

/**
 * \name Transaction status codes
 * \{
 */
#define TRAC_SUCCESS                0
#define TRAC_SUCCESS_DATA_PENDING   1
#define TRAC_SUCCESS_WAIT_FOR_ACK   2
#define TRAC_CHANNEL_ACCESS_FAILURE 3
#define TRAC_NO_ACK                 5
#define TRAC_INVALID                7
/** \} */

/*============================ TYPEDEFS ======================================*/

/** \brief  This enumeration defines the possible return values for the TAT API
 *          functions.
 *
 *          These values are defined so that they should not collide with the
 *          return/status codes defined in the IEEE 802.15.4 standard.
 *
 */
typedef enum{
    RADIO_SUCCESS = RADIO_STATUS_START_VALUE,  /**< The requested service was performed successfully. */
    RADIO_UNSUPPORTED_DEVICE,         /**< The connected device is not an Atmel AT86RF230. */
    RADIO_INVALID_ARGUMENT,           /**< One or more of the supplied function arguments are invalid. */
    RADIO_TIMED_OUT,                  /**< The requested service timed out. */
    RADIO_WRONG_STATE,                /**< The end-user tried to do an invalid state transition. */
    RADIO_BUSY_STATE,                 /**< The radio transceiver is busy receiving or transmitting. */
    RADIO_STATE_TRANSITION_FAILED,    /**< The requested state transition could not be completed. */
    RADIO_CCA_IDLE,                   /**< Channel is clear, available to transmit a new frame. */
    RADIO_CCA_BUSY,                   /**< Channel busy. */
    RADIO_TRX_BUSY,                   /**< Transceiver is busy receiving or transmitting data. */
    RADIO_BAT_LOW,                    /**< Measured battery voltage is lower than voltage threshold. */
    RADIO_BAT_OK,                     /**< Measured battery voltage is above the voltage threshold. */
    RADIO_CRC_FAILED,                 /**< The CRC failed for the actual frame. */
    RADIO_CHANNEL_ACCESS_FAILURE,     /**< The channel access failed during the auto mode. */
    RADIO_NO_ACK,                     /**< No acknowledge frame was received. */
}radio_status_t;

/** \brief  This enumeration defines the possible modes available for the
 *          Clear Channel Assessment algorithm.
 *
 *          These constants are extracted from the datasheet.
 *
 */
typedef enum{
    CCA_ED                    = 0,    /**< Use energy detection above threshold mode. */
    CCA_CARRIER_SENSE         = 1,    /**< Use carrier sense mode. */
    CCA_CARRIER_SENSE_WITH_ED = 2     /**< Use a combination of both energy detection and carrier sense. */
}radio_cca_mode_t;


/** \brief  This enumeration defines the possible CLKM speeds.
 *
 *          These constants are extracted from the RF230 datasheet.
 *
 */
typedef enum{
    CLKM_DISABLED      = 0,
    CLKM_1MHZ          = 1,
    CLKM_2MHZ          = 2,
    CLKM_4MHZ          = 3,
    CLKM_8MHZ          = 4,
    CLKM_16MHZ         = 5
}radio_clkm_speed_t;

/** \brief  This enumeration defines the necessary hardware delay timing
 *          information for the AT86RF230 radio transceiver.
 *          All times are in microseconds.
 *
 *          These constants are extracted from the datasheet.
 *
 */
typedef enum{
    TIME_TO_ENTER_P_ON               = 510, /**<  Transition time from VCC is applied to P_ON. */
    TIME_P_ON_TO_TRX_OFF             = 510, /**<  Transition time from P_ON to TRX_OFF. */
    TIME_SLEEP_TO_TRX_OFF            = 880, /**<  Transition time from SLEEP to TRX_OFF. */
    TIME_RESET                       = 6,   /**<  Time to hold the RST pin low during reset */
    TIME_ED_MEASUREMENT              = 140, /**<  Time it takes to do a ED measurement. */
    TIME_CCA                         = 140, /**<  Time it takes to do a CCA. */
    TIME_PLL_LOCK                    = 150, /**<  Maximum time it should take for the PLL to lock. */
    TIME_FTN_TUNING                  = 25,  /**<  Maximum time it should take to do the filter tuning. */
    TIME_NOCLK_TO_WAKE               = 6,   /**<  Transition time from *_NOCLK to being awake. */
    TIME_CMD_FORCE_TRX_OFF           = 1,   /**<  Time it takes to execute the FORCE_TRX_OFF command. */
    TIME_TRX_OFF_TO_PLL_ACTIVE       = 180, /**<  Transition time from TRX_OFF to: RX_ON, PLL_ON, TX_ARET_ON and RX_AACK_ON. */
    TIME_STATE_TRANSITION_PLL_ACTIVE = 1,   /**<  Transition time from PLL active state to another. */
    TIME_RESET_TRX_OFF               = 37,  /**<  Transition time from RESET to TRX_OFF. */
}radio_trx_timing_t; /* PORTREF: line 79 */

#if HAL_HANDLERS
typedef void (*radio_rx_callback) (uint16_t data);
#endif

/*============================ STRUCTS ========================================*/
#if RF2XX_CONF_TIMESTAMPS
struct timestamp {
  uint16_t time;
  uint8_t authority_level;
};
#endif
/*============================ HOOKS =========================================*/
/*	Hook Documentation 
**	
**	Sniffing Hooks:
**		RF2XX_HOOK_TX_PACKET(buffer,total_len)
**		RF2XX_HOOK_RX_PACKET(buf,len)
**
**	RF2XX_HOOK_IS_SEND_ENABLED()
**	RF2XX_HOOK_RADIO_ON()
**	RF2XX_HOOK_RADIO_OFF()
**	
*/
/*============================ PROTOTYPES ====================================*/

/* == Initialization == */
#if HAL_HANDLERS
radio_status_t rf2xx_init(bool cal_rc_osc,
                          hal_rx_start_isr_event_handler_t rx_event,
                          hal_trx_end_isr_event_handler_t trx_end_event,
                          radio_rx_callback rx_callback);
#else

radio_status_t rf2xx_init( void );

#endif /* HAL_HANDLERS */

radio_status_t rf2xx_cca( void );

#if !CODE_OPT_TEST
void           rf2xx_use_auto_tx_crc( bool auto_crc_on );
#endif

#if RF2XX_CONF_ENABLE_CSMA
radio_status_t rf2xx_configure_csma( uint8_t seed0, uint8_t be_csma_seed1 );
#endif

/* == Store and Read == */
/* #if CODE_OPT_MACROS */
/* extern uint8_t hal_subregister_read(uint8_t address, uint8_t mask, uint8_t position); */
/* #else */
#if !CODE_OPT_MACROS
uint8_t		rf2xx_get_operating_channel( void );
uint8_t		rf2xx_get_device_role( void );
uint8_t		rf2xx_get_cca_mode( void );
uint8_t		rf2xx_get_ed_threshold( void );
#endif /* CODE_OPT_MACROS */

uint8_t		radio_get_part_number( void );
radio_status_t	rf2xx_set_operating_channel( uint8_t channel );
void		rf2xx_set_device_role( bool i_am_coordinator );

void		rf2xx_set_pan_addr( unsigned pan,
				    unsigned addr,
				    const uint8_t ieee_addr[8] );

uint16_t	radio_get_pan_id( void );
#if !CODE_OPT_TEST
void		radio_set_pan_id( uint16_t new_pan_id );
#endif
uint16_t	radio_get_short_address( void );
#if !CODE_OPT_TEST
void		radio_set_short_address( uint16_t new_short_address );
#endif
void		radio_get_extended_address( uint8_t *extended_address );
#if !CODE_OPT_TEST
void		radio_set_extended_address( uint8_t *extended_address );
#endif
uint8_t		rf2xx_get_tx_power_level( void );
radio_status_t	rf2xx_set_tx_power_level( uint8_t power_level );
radio_status_t	rf2xx_set_cca_mode( uint8_t mode, uint8_t ed_threshold );
uint8_t		rf2xx_get_raw_rssi( void );
#define rf230_rssi	rf2xx_get_raw_rssi
radio_status_t	rf2xx_get_rssi_value( uint8_t *rssi );
uint8_t		rf2xx_get_saved_rssi_value( void );
uint8_t		radio_get_saved_lqi_value ( void );

#if RF2XX_CONF_BATTERY_MONITOR
/* == Battery Monitor ==*/
radio_status_t	rf2xx_batmon_configure( bool range, uint8_t voltage_threshold );
radio_status_t	rf2xx_batmon_get_status( void );
#if !CODE_OPT_MACROS
uint8_t		rf2xx_batmon_get_voltage_threshold( void );
uint8_t		rf2xx_batmon_get_voltage_range( void );
#endif /* CODE_OPT_MACROS */
#endif /* RF2XX_CONF_BATTERY_MONITOR */

/* == Clock Settings == */
uint8_t		rf2xx_get_clock_speed( void );
radio_status_t	rf2xx_set_clock_speed( bool direct, uint8_t clock_speed );

#if RF2XX_CONF_CALIBRATION
/* == Radio Callibration ==*/
radio_status_t	rf2xx_calibrate_filter( void );
radio_status_t	rf2xx_calibrate_pll( void );
bool		calibrate_rc_osc_clkm( void );
void		calibrate_rc_osc_32k( void );
#endif /* RF2XX_CONF_CALIBRATION */

/* == States and Transitions ==*/
#if HAL_HANDLERS
static void radio_rx_start_event( uint32_t const isr_timestamp, uint8_t const frame_length );
static void radio_trx_end_event( uint32_t const isr_timestamp );
#endif

int rf2xx_interrupt( void );
static char rf2xx_is_idle( void );
static void rf2xx_wait_idle( void );
bool rf2xx_is_ready_to_send( void );

static void	on( void );
int	rf2xx_on( void );
static void	off( void );
int	rf2xx_off( void );

#define GET_LOCK() locked = 1
static void RELEASE_LOCK( void );

static void radio_reset_state_machine( void );

void		rf2xx_set_promiscuous_mode(bool m);

#if !CODE_OPT_MACROS
static uint8_t	rf2xx_get_trx_state( void );
#endif
static radio_status_t	rf2xx_set_trx_state( uint8_t new_state );
static bool	radio_is_sleeping( void );
radio_status_t	rf2xx_enter_sleep_mode( void );
radio_status_t	rf2xx_leave_sleep_mode( void );
void		rf2xx_reset_state_machine( void );
#if !CODE_OPT_TEST
void		rf2xx_reset_trx( void );
#endif

/* == Data Transmission ==*/

static int rf2xx_prepare( const void *data, unsigned short len );
static int rf2xx_transmit( unsigned short len );
static int rf2xx_send( const void *data, unsigned short len );
static int rf2xx_read( void *buf, unsigned short bufsize );

static int rf2xx_receiving_packet( void );
/* static int rf2xx_pending_packet( void ); */

static void flushrx( void );

#if HAL_HANDLERS
radio_status_t radio_send_data( uint8_t data_length, uint8_t *data );
#endif
#if !CODE_OPT_TEST
uint8_t      * radio_frame_data( void );
uint8_t        radio_frame_length( void );
#endif

const struct radio_driver rf2xx_driver =
  {
    rf2xx_init,
    rf2xx_prepare,
    rf2xx_transmit,
    rf2xx_send,
    rf2xx_read,
    rf2xx_cca,
    rf2xx_receiving_packet,
    pending_packet,
    rf2xx_on,
    rf2xx_off
  };



#endif /* RADIO_H */
/** @} */
/*EOF*/
