/*   Copyright (c) 2008, Swedish Institute of Computer Science
 *  All rights reserved.
 *
 *  Additional fixes for AVR contributed by:
 *      Colin O'Flynn coflynn@newae.com
 *      Eric Gnoske egnoske@gmail.com
 *      Blake Leverett bleverett@gmail.com
 *      Mike Vidales mavida404@gmail.com
 *      Kevin Brown kbrown3@uccs.edu
 *      Nate Bohlmann nate@elfwerks.com
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
 *
 * $Id: radio.c,v 1.5 2010/02/12 18:00:30 dak664 Exp $
*/

/**
 *  \brief This module contains the radio driver code for the Atmel
 *  AT86RF230, '231, and '212 chips.
 *
 *  \author Blake Leverett <bleverett@gmail.com>
 *          Mike Vidales <mavida404@gmail.com>
 *          Eric Gnoske <egnoske@gmail.com>
 *
*/

/**  \addtogroup wireless
 * @{
 *
 * The radio interface is a driver for the Atmel 802.15.4 radio chips.
 * This code works with the AT86RF230, 'RF231, and 'RF212 chips.
 *
 * This driver code is fairly modular, and can be modified to be used
 * without the RUM MAC layer that lies on top.
 *
 * The radio interface involves an SPI port and several digital I/O
 * lines.  See the radio chip datasheet for details.
 */

/**
 *  \defgroup radiorf2xx RF2xx interface
 * @{
 */
/**
 *  \file
 *  This file contains radio driver code.
 *
 */



/*============================ INCLUDE =======================================*/
#include <stdlib.h>
#include <util/delay.h>
#include "radio.h"
#include "hal.h"
#include "process.h"
#include "sicslowmac.h"

/*
 * #ifdef HAL_HANDLERS
 * #include "frame.h"
 * #endif
 */

/*============================ VARIABLES =====================================*/
#ifdef HAL_HANDLERS
static hal_rx_start_isr_event_handler_t user_rx_event;
static hal_trx_end_isr_event_handler_t user_trx_end_event;
static radio_rx_callback rx_frame_callback;
static uint8_t rx_mode;
#endif

static uint8_t rssi_val;

/* TODO: this needs to be checked if it's needed */
/* uint8_t rxMode = RX_AACK_ON; */

/* See clock.c and httpd-cgi.c for RADIOSTATS code */
#if WEBSERVER
#define RADIOSTATS 1
#else
#define RADIOSTATS 0
#endif 

#if RADIOSTATS
	uint8_t RF2xx_rsigsi;

	uint16_t RF2xx_sendpackets,
		 RF2xx_receivepackets,
		 RF2xx_sendfail,
		 RF2xx_receivefail;
#endif

/* HACK: these will be made as Chameleon packet attributes */
rtimer_clock_t rf2xx_time_of_arrival, rf2xx_time_of_departure;


/* == Physical Layer == */

/* == Packes and Frames == */

static uint8_t buffer[RF230_MAX_TX_FRAME_LENGTH+AUX_LEN];

#if RF2XX_CONF_TIMESTAMPS
static rtimer_clock_t setup_time_for_transmission;
static unsigned long total_time_for_transmission, total_transmission_len;
static int num_transmissions;
static volatile rtimer_clock_t interrupt_time;
static volatile int interrupt_time_set;
#endif /* RF2XX_CONF_TIMESTAMPS */

#if RF2XX_TIMETABLE_PROFILING
#define rf2xx_timetable_size 16
TIMETABLE(rf2xx_timetable);
TIMETABLE_AGGREGATE(aggregate_time, 10);
#endif /* RF2XX_TIMETABLE_PROFILING */

/* Received frames are buffered to rx_frame in the interrupt routine in hal.c */
static hal_rx_frame_t rx_frame;
/* static parsed_frame_t parsed_frame; */

int rf2xx_packets_seen, rf2xx_packets_read;

int rf2xx_authority_level_of_sender;

static uint8_t volatile pending;

/* == State Variables == */
uint8_t RF2xx_receive_on, RF2xx_sleeping;
static uint8_t locked, lock_on, lock_off;

#if RF2XX_CONF_AACK
static bool is_promiscuous;
#endif

#if DEBUG
char rf2xx_process_flag; /** For debugging process call problems. */
#endif

/*============================ IMPLEMENTATION ================================*/

/*---------------------------------------------------------------------------*/
PROCESS(rf2xx_process, "RF2XX driver");
/*---------------------------------------------------------------------------*/
const struct radio_driver rf2xx_driver =
  {				/* SECTION: */
    rf2xx_init,			/** Initialization */
//    rf2xx_prepare,		/** Data Transmission */
//    rf2xx_transmit,		/** Data Transmission */
//    rf2xx_send,		/** Data Transmission */
    rf2xx_read,			/** Data Transmission */
//    rf2xx_cca,		/** Initialization */
//    rf2xx_receiving_packet,	/** Data Transmission */
//    rf2xx_pending_packet,	/** Data Transmission */
//    rf2xx_on,			/** States and Transitions */
//    rf2xx_off			/** States and Transitions */
  };

/*============================================================================*/
/*= Section: Initialization ==================================================*/
/*----------------------------------------------------------------------------*/
/** \brief  Initialize the Transceiver Access Toolbox and lower layers.
 *
 *          If the initialization is successful the radio transceiver will be in
 *          TRX_OFF state.
 *
 *  \note  This function must be called prior to any of the other functions in
 *         this file! Can be called from any transceiver state.
 * 
 *  \note There is a parameter (SR_CCA_ED_THRES) that sets the energy
 * 	   threshold for determining if a channel is clear before the radio
 *	   can send a packet.  If the threshold is set too low, then in the
 *  	   presence of interference the radio may never get a chance to send a
 *  	   packet, and will be cut off from the network.  If the threshold is
 *  	   set too high, then each node may "yell over" the other nodes and
 *  	   disrupt other network connections.  The default value is 7, and a
 *  	   value of 2 was useful for testing the initial 2.4GHz version of the
 *  	   network.  Interference caused problems in the 900MHz band, and the
 *  	   threshold was raised back up to 7.  This parameter may be
 *  	   auto-tuned by application software in the future.
 *
 *  \param cal_rc_osc If true, the radio's accurate clock is used to calibrate the
 *                    CPU's internal RC oscillator.
 *
 *  \param rx_event Optional pointer to a user-defined function to be called on an
 *                  RX_START interrupt.  Use NULL for no handler.
 *
 *  \param trx_end_event Optional pointer to a user-defined function to be called on an
 *                  TRX_END interrupt.  Use NULL for no handler.
 *
 *  \param rx_callback Optional pointer to a user-defined function that receives
 *         a frame from the radio one byte at a time.  If the index parameter to
 *         this callback is 0xff, then the function should reset its state and prepare
 *         for a frame from the radio, with one call per byte.
 *
 *  \retval RADIO_SUCCESS     The radio transceiver was successfully initialized
 *                          and put into the TRX_OFF state.
 *  \retval RADIO_UNSUPPORTED_DEVICE  The connected device is not an Atmel
 *                          AT86RF230 radio transceiver.
 *  \retval RADIO_TIMED_OUT   The radio transceiver was not able to initialize and
 *                          enter TRX_OFF state within the specified time.
 */
radio_status_t		/* PORTNOTE: in RF230BB driver it's 'int'. */
#ifdef HAL_HANDLERS
rf2xx_init(bool cal_rc_osc,
           hal_rx_start_isr_event_handler_t rx_event,
           hal_trx_end_isr_event_handler_t trx_end_event,
           radio_rx_callback rx_callback) /* PORTREF: line 124 */
#else /* !HAL_HANDLERS */
rf2xx_init(void)
#endif
{
    DEBUGFLOW('I');

    radio_status_t init_status = RADIO_SUCCESS;

    /* Wait in case VCC just applied. */
    delay_us(TIME_TO_ENTER_P_ON);

    #ifdef RF2XX_CONF_CALIBRATION
    /*  Calibrate RC oscillator. */
    if (cal_rc_osc){
        calibrate_rc_osc_32k();
    }
    #endif

    /* Initialize Hardware Abstraction Layer. */
    hal_init();

    /* Do HW reset of radio transeiver. */
    #ifdef CODE_OPT_TEST

	hal_set_rst_low();
	hal_set_slptr_low();
	delay_us(TIME_RESET);
	hal_set_rst_high();

    #else /* Use functions. */
    rf2xx_reset_trx();
    #endif

    /* Force transition to TRX_OFF. */
    hal_subregister_write(SR_TRX_CMD, CMD_FORCE_TRX_OFF);
    /* Wait for the transition to be complete. */
    delay_us(TIME_P_ON_TO_TRX_OFF);

    if (rf2xx_get_trx_state() != TRX_OFF){
        init_status = RADIO_TIMED_OUT;
    } else {
	/* TODO: adjust this and hal.c accordingly! */
        /* Read Version Number */
        uint8_t version_number = hal_register_read(RG_VERSION_NUM);

        if ((version_number != RF230_REVA) && (version_number != RF230_REVB))
            init_status = RADIO_UNSUPPORTED_DEVICE;
        else {
            if (hal_register_read(RG_MAN_ID_0) != SUPPORTED_MANUFACTURER_ID)
                init_status = RADIO_UNSUPPORTED_DEVICE;
            else
                hal_register_write(RG_IRQ_MASK, RF230_SUPPORTED_INTERRUPT_MASK);
        }

#if RADIOSTATS
        RF2xx_radio_on = 1;
#endif
    }

#ifdef HAL_HANDLERS
    /*  Set callbacks for events.  Save user's rx_event, which we will */
    /*  call from radio_rx_start_event() and radio_trx_end_event(). */
    user_rx_event = rx_event;
    user_trx_end_event = trx_end_event;
    hal_set_rx_start_event_handler(radio_rx_start_event);
    hal_set_trx_end_event_handler(radio_trx_end_event);
    rx_frame_callback = rx_callback;

#else /* !HAL_HANDLERS */

   /* Set up number of automatic retries */
   hal_subregister_write(SR_MAX_FRAME_RETRIES, RF2XX_CONF_AUTORETRIES);

/* If RF2XX_CONF_AUTO_CRC defined, then automatic CRC is enabled;
 * otherwise it is disabled and then HAL_CALC_CRC can be used. */
#ifdef CODE_OPT_TEST /* Disable rearly called functions. */

	#if RF2XX_CONF_AUTO_CRC /* Enable automatic CRC. */
	hal_subregister_write(SR_TX_AUTO_CRC_ON, 1);
	#else
	hal_subregister_write(SR_TX_AUTO_CRC_ON, 0);
	#endif /* RF2XX_CONF_AUTO_CRC */

#endif /* CODE_OPT_TEST */

#else /* Use functions. */
	rf2xx_use_auto_tx_crc(RF2XX_CONF_AUTO_CRC);
#endif

    /* Start the packet receive process.*/
    process_start(&rf2xx_process, NULL);
    
    /* Leave radio in on state (?)*/
    on();

#endif

    return init_status; /* PORTNOTE: in RF230BB it returns '1'. */
}

/* TODO: This has to be checked. */
radio_status_t
rf2xx_cca(void)
{			/* PORTNOTE: taken from RF230BB as is
			 * there is defined as rf230_cca on line 1199.
			 ****************************************************/
	
    int cca;
    int radio_was_off = 0;

    /* If the radio is locked by an underlying thread (because we are
     * being invoked through an interrupt), we preted that the coast is
     * clear (i.e., no packet is currently being transmitted by a neighbor).
     ************************************************************************/

    if(locked) {
      return 1;
    }
    
    if(!RF2xx_receive_on) {
      radio_was_off = 1;
      radio_on();
    }

    /* cca = CCA_IS_1; */
    DEBUGFLOW('c');
    cca=1;

    if(radio_was_off) {
      radio_off();
    }
    return cca;

}

/*----------------------------------------------------------------------------*/
/** \brief  This function will enable or disable automatic CRC during frame
 *          transmission. If CODE_OPT_TEST is defined, this is not defined.
 *
 *  \param  auto_crc_on If this parameter equals true auto CRC will be used for
 *                      all frames to be transmitted. The framelength must be
 *                      increased by two bytes (16 bit CRC). If the parameter equals
 *                      false, the automatic CRC will be disabled.
 */
#ifndef CODE_OPT_TEST
void
rf2xx_use_auto_tx_crc(bool auto_crc_on) /* PORTREF: line 928 */
{					/* PORTNOTE: SR_TX_AUTO_CRC_ON has to be defined correctly in the header! */
					/* IF WE WERE TO USE IT WITH DIFFERENT RADIOS, THEN - YES, DO LIKE ATMEL. */
					/* (that way we wouldn't need to recompile it every time for every radio) */
    if (auto_crc_on == true){
	hal_subregister_write(SR_TX_AUTO_CRC_ON, 1);
    } else {
	hal_subregister_write(SR_TX_AUTO_CRC_ON, 0);
    }
}
#endif

/*----------------------------------------------------------------------------*/
/** \brief  This function will configure the CSMA algorithm used by the radio
 *          transceiver when transmitting data from TX_ARET_ON state.
 *
 *  \param  seed0 Lower 8 bits of the seed used for the random number generator
 *                in the CSMA algorithm. Value range: 0 to 255.
 *  \param  be_csma_seed1 Is a combined argument of the MIN_BE, MAX_CSMA_RETRIES
 *                        and SEED1 variables:
 *                        -# MIN_BE: Bit[7:6] Minimum back-off exponent in the
 *                           CSMA/CA algorithm.
 *                        -# MAX_CSMA_RETRIES: Bit[5:3] Number of retries in
 *                          TX_ARET_ON mode to repeat the CSMA/CA procedures
 *                          before the ARET procedure gives up.
 *                        -# SEED1: Bits[2:0] Higher 3 bits of CSMA_SEED, bits[10:8]
 *                           Seed for the random number generator in the
 *                           CSMA/CA algorithm.
 *  \retval RADIO_SUCCESS The CSMA algorithm was configured successfully.
 *  \retval RADIO_WRONG_STATE This function should not be called in the
 *                          SLEEP state.
 */
#ifdef RF2XX_CONF_ENABLE_CSMA
radio_status_t
rf2xx_configure_csma(uint8_t seed0, uint8_t be_csma_seed1)
{

    /*Check state.*/
    if (radio_is_sleeping() == true){
	return RADIO_WRONG_STATE;
    }

    /*Extract parameters, and configure the CSMA-CA algorithm.*/
    uint8_t back_off_exponent = (be_csma_seed1 & 0xC0) >> 6;
    uint8_t csma_retries      = (be_csma_seed1 & 0x38) >> 3;
    uint8_t seed1             = (be_csma_seed1 & 0x07);

    hal_subregister_write(SR_MAX_FRAME_RETRIES, 0); /* AT86RF230 rev A errata. */
    hal_subregister_write(SR_MAX_CSMA_RETRIES, csma_retries);
    hal_subregister_write(SR_MIN_BE, back_off_exponent);
    hal_register_write(RG_CSMA_SEED_0, seed0);
    hal_subregister_write(SR_CSMA_SEED_1, seed1);

    return RADIO_SUCCESS;
}
#endif

/*============================================================================*/
/*= Section: Store and Read ==================================================*/
/*---------------------------------------------------------------------------*/
/** \brief Returns the radio part number.
 * The value returned is shown in the radio datasheet.
 * This value is valid any time after rf2xx_init() is called.
 *
 *  \return \ref RF230
 *  \return \ref RF231
 *  \return \ref RF212
*/
u8 radio_get_part_number(void) /* PORTREF: line 161 */
{
    static u8 radio_part_number;

    if (!radio_part_number)
	radio_part_number = hal_register_read(RG_PART_NUM);
    return radio_part_number;
}

/*----------------------------------------------------------------------------*/
/** \brief  This function will return the channel used by the radio transceiver.
 *
 *  \return Current channel, 11 to 26.
 */
uint8_t
rf2xx_get_operating_channel(void) /* PORTREF: line 349 */
{
    return hal_subregister_read(SR_CHANNEL);
}

/*----------------------------------------------------------------------------*/
/** \brief This function will change the operating channel.
 *
 *  \param  channel New channel to operate on. Must be between 11 and 26.
 *
 *  \retval RADIO_SUCCESS New channel set.
 *  \retval RADIO_WRONG_STATE Transceiver is in a state where the channel cannot
 *                          be changed (SLEEP).
 *  \retval RADIO_INVALID_ARGUMENT Channel argument is out of bounds.
 *  \retval RADIO_TIMED_OUT The PLL did not lock within the specified time.
 */
radio_status_t
rf2xx_set_operating_channel(uint8_t channel) /* PORTREF: line 366 */
{
    /* Do function parameter and state check. */
    if ((channel < MIN_CHANNEL) ||
        (channel > MAX_CHANNEL)){
        return RADIO_INVALID_ARGUMENT;
    }

    if (radio_is_sleeping() == true){
        return RADIO_WRONG_STATE;
    }

    if (rf2xx_get_operating_channel() == channel){
        return RADIO_SUCCESS;
    }

    /* Set new operating channel. */
    hal_subregister_write(SR_CHANNEL, channel);

    /* Read current state and wait for the PLL_LOCK interrupt if the */
    /* radio transceiver is in either RX_ON or PLL_ON. */
    uint8_t trx_state = rf2xx_get_trx_state();

    if ((trx_state == RX_ON) ||
        (trx_state == PLL_ON)){
        delay_us(TIME_PLL_LOCK);
    }

    radio_status_t channel_set_status = RADIO_TIMED_OUT;

    /* Check that the channel was set properly. */
    if (rf2xx_get_operating_channel() == channel){
        channel_set_status = RADIO_SUCCESS;
    }

    return channel_set_status;
}

/*----------------------------------------------------------------------------*/
/** \brief  This function will read the I_AM_COORD sub register.
 *
 *  \retval 0 Not coordinator.
 *  \retval 1 Coordinator role enabled.
 */
uint8_t
rf2xx_get_device_role(void)
{
    return hal_subregister_read(SR_I_AM_COORD);
}

/*----------------------------------------------------------------------------*/
/** \brief  This function will set the I_AM_COORD sub register.
 *
 *  \param[in] i_am_coordinator If this parameter is true, the associated
 *                              coordinator role will be enabled in the radio
 *                              transceiver's address filter.
 *                              False disables the same feature.
 */
void
rf2xx_set_device_role(bool i_am_coordinator) /* PORTREF: line 1017 */
{
    hal_subregister_write(SR_I_AM_COORD, i_am_coordinator);
}

/*---------------------------------------------------------------------------*/
/** \breif This function set the address for the RF2XX device.
 */
void
rf2xx_set_pan_addr(unsigned pan, unsigned addr, const uint8_t ieee_addr[8])
//rf230_set_pan_addr(uint16_t pan,uint16_t addr,uint8_t *ieee_addr)
{
  PRINTF("rf2xx: PAN=%x ShortAddress=%x\n", pan, addr);
  
  uint8_t b;
  abyte = pan & 0xFF;
  hal_register_write(RG_PAN_ID_0, b);
  abyte = (pan >> 8*1) & 0xFF;
  hal_register_write(RG_PAN_ID_1, b);

  abyte = addr & 0xFF;
  hal_register_write(RG_SHORT_ADDR_0, b);
  abyte = (addr >> 8*1) & 0xFF;
  hal_register_write(RG_SHORT_ADDR_1, b);  

  if (ieee_addr != NULL) {
    PRINTF("rf2xx: MAC=%x",*ieee_addr);
    hal_register_write(RG_IEEE_ADDR_7, *ieee_addr++);
    PRINTF(":%x",*ieee_addr);
    hal_register_write(RG_IEEE_ADDR_6, *ieee_addr++);
    PRINTF(":%x",*ieee_addr);
    hal_register_write(RG_IEEE_ADDR_5, *ieee_addr++);
    PRINTF(":%x",*ieee_addr);
    hal_register_write(RG_IEEE_ADDR_4, *ieee_addr++);
    PRINTF(":%x",*ieee_addr);
    hal_register_write(RG_IEEE_ADDR_3, *ieee_addr++);
    PRINTF(":%x",*ieee_addr);
    hal_register_write(RG_IEEE_ADDR_2, *ieee_addr++);
    PRINTF(":%x",*ieee_addr);
    hal_register_write(RG_IEEE_ADDR_1, *ieee_addr++);
    PRINTF(":%x",*ieee_addr);
    hal_register_write(RG_IEEE_ADDR_0, *ieee_addr);
    PRINTF("\n");
  }
}

/*----------------------------------------------------------------------------*/
/** \brief  This function will return the PANID used by the address filter.
 *
 *  \retval Any value from 0 to 0xFFFF.
 */
uint16_t
radio_get_pan_id(void)
{

    uint8_t pan_id_15_8 = hal_register_read(RG_PAN_ID_1); /*  Read pan_id_15_8. */
    uint8_t pan_id_7_0 = hal_register_read(RG_PAN_ID_0); /*  Read pan_id_7_0. */

    uint16_t pan_id = ((uint16_t)(pan_id_15_8 << 8)) | pan_id_7_0;

    return pan_id;
}

/*----------------------------------------------------------------------------*/
/** \brief  This function will set the PANID used by the address filter.
 *
 *  \param  new_pan_id Desired PANID. Can be any value from 0x0000 to 0xFFFF
 */
#ifndef CODE_OPT_TEST
void
radio_set_pan_id(uint16_t new_pan_id) /* PORTREF: line 1028 */
{

    uint8_t pan_byte = new_pan_id & 0xFF; /*  Extract new_pan_id_7_0. */
    hal_register_write(RG_PAN_ID_0, pan_byte);

    pan_byte = (new_pan_id >> 8*1) & 0xFF;  /*  Extract new_pan_id_15_8. */
    hal_register_write(RG_PAN_ID_1, pan_byte);
}
#endif

/*----------------------------------------------------------------------------*/
/** \brief  This function will return the current short address used by the
 *          address filter.
 *
 *  \retval Any value from 0x0000 to 0xFFFF
 */
uint16_t
radio_get_short_address(void)
{

    uint8_t short_address_15_8 = hal_register_read(RG_SHORT_ADDR_1); /*  Read short_address_15_8. */
    uint8_t short_address_7_0  = hal_register_read(RG_SHORT_ADDR_1); /*  Read short_address_7_0. */

    uint16_t short_address = ((uint16_t)(short_address_15_8 << 8)) | short_address_7_0;

    return short_address;
}

/*----------------------------------------------------------------------------*/
/** \brief  This function will set the short address used by the address filter.
 *
 *  \param  new_short_address Short address to be used by the address filter.
 */
#ifndef CODE_OPT_TEST
void
radio_set_short_address(uint16_t new_short_address) /* PORTREF: line 1044 */
{

    uint8_t short_address_byte = new_short_address & 0xFF; /*  Extract short_address_7_0. */
    hal_register_write(RG_SHORT_ADDR_0, short_address_byte);

    short_address_byte = (new_short_address >> 8*1) & 0xFF; /*  Extract short_address_15_8. */
    hal_register_write(RG_SHORT_ADDR_1, short_address_byte);
}
#endif

/*----------------------------------------------------------------------------*/
/** \brief  This function will read the extended address used by the address
 *          filter.
 *
 *  \note In this function a pointer is used to convey the 64-bit result, since
 *        it is very inefficient to use the stack for this.
 *
 *  \return Extended Address, any 64-bit value.
 */
void
radio_get_extended_address(uint8_t *extended_address)
{
    *extended_address++ = hal_register_read(RG_IEEE_ADDR_0);
    *extended_address++ = hal_register_read(RG_IEEE_ADDR_1);
    *extended_address++ = hal_register_read(RG_IEEE_ADDR_2);
    *extended_address++ = hal_register_read(RG_IEEE_ADDR_3);
    *extended_address++ = hal_register_read(RG_IEEE_ADDR_4);
    *extended_address++ = hal_register_read(RG_IEEE_ADDR_5);
    *extended_address++ = hal_register_read(RG_IEEE_ADDR_6);
    *extended_address   = hal_register_read(RG_IEEE_ADDR_7);
}

/*----------------------------------------------------------------------------*/
/** \brief  This function will set a new extended address to be used by the
 *          address filter.
 *
 *  \param  extended_address Extended address to be used by the address filter.
 */
#ifndef CODE_OPT_TEST
void
radio_set_extended_address(uint8_t *extended_address) /* PORTREF: line 1061 */
{								/* PORTNOTE: Atmel uses a loop here. */
    hal_register_write(RG_IEEE_ADDR_0, *extended_address++);
    hal_register_write(RG_IEEE_ADDR_1, *extended_address++);
    hal_register_write(RG_IEEE_ADDR_2, *extended_address++);
    hal_register_write(RG_IEEE_ADDR_3, *extended_address++);
    hal_register_write(RG_IEEE_ADDR_4, *extended_address++);
    hal_register_write(RG_IEEE_ADDR_5, *extended_address++);
    hal_register_write(RG_IEEE_ADDR_6, *extended_address++);
    hal_register_write(RG_IEEE_ADDR_7, *extended_address++);
}
#endif

/*----------------------------------------------------------------------------*/
/** \brief This function will read and return the output power level.
 *
 *  \returns 0 to 15 Current output power in "TX power settings" as defined in
 *          the radio transceiver's datasheet
 */
uint8_t
rf2xx_get_tx_power_level(void) /* PORTREF: line 457 */
{
    #ifndef CODE_OPT_MINIMAL
    uint8_t powe = TX_PWD_UNDEFINED;
    if (radio_is_sleeping()){
    	PRINTF("rf2xx_get_txpower(): The radio is sleeping.");
    } else {
    		tx_power = hal_subregister_read(SR_TX_PWD);
    }
    return tx_power;
    #else
    return hal_subregister_read(SR_TX_PWR);
    #endif
}

/*----------------------------------------------------------------------------*/
/** \brief This function will change the output power level.
 *
 *  \param  power_level New output power level in the "TX power settings"
 *                      as defined in the radio transceiver's datasheet.
 *
 *  \retval RADIO_SUCCESS New output power set successfully.
 *  \retval RADIO_INVALID_ARGUMENT The supplied function argument is out of bounds.
 *  \retval RADIO_WRONG_STATE It is not possible to change the TX power when the
 *                          device is sleeping.
 */
radio_status_t
rf2xx_set_tx_power_level(uint8_t power_level) /* PORTREF: line 433 */
{
    GET_LOCK();				/* PORTNOTE: in RF230BB there two functions
    					 * rf230_set_txpower() and set_txpower()
					 * first calls the second with locking.
					 * This is an attempt to merge both.
					 ******************************************/
    /* Check function parameter. */
    if (power_level > TX_PWR_17_2DBM){	/* PORTNOTE: or just ignore & set 17.2dBm */
    	PRINTF("rf2xx_set_tx_power_level(): Invalid agument.\n");
	RELEASE_LOCK();
        return RADIO_INVALID_ARGUMENT;
    }

    /* Check radio state. */
    if (radio_is_sleeping() == true){
	PRINTF("rf2xx_set_tx_power_level(): The radio is sleeping.\n");
	RELEASE_LOCK();
        return RADIO_WRONG_STATE;
    }

    /* Set new power level. */
    hal_subregister_write(SR_TX_PWR, power_level);
    PRINTF("rf2xx_set_tx_power_level(): Set TX power level to %d.\n", power_level);
    RELEASE_LOCK();
    return RADIO_SUCCESS;
}
/* void set_txpower(uint8_t p) { rf2xx_set_tx_power_level(p); } */

/*----------------------------------------------------------------------------*/
/** \brief This function returns the current CCA mode used.
 *
 *  \return CCA mode currently used, 0 to 3.
 */
uint8_t
rf2xx_get_cca_mode(void) /* PORTREF: line 468 */
{
    return hal_subregister_read(SR_CCA_MODE);
}

/*----------------------------------------------------------------------------*/
/** \brief This function will configure the Clear Channel Assessment algorithm.
 *
 *  \param  mode Three modes are available: Energy above threshold, carrier
 *               sense only and carrier sense with energy above threshold.
 *  \param  ed_threshold Above this energy threshold the channel is assumed to be
 *                      busy. The threshold is given in positive dBm values.
 *                      Ex. -91 dBm gives a csThreshold of 91. Value range for
 *                      the variable is [61 to 91]. Only valid for the CCA_ED
 *                      and CCA_CARRIER_SENSE_ED modes.
 *
 *  \retval RADIO_SUCCESS Mode and its parameters successfully changed.
 *  \retval RADIO_WRONG_STATE This function cannot be called in the SLEEP state.
 *  \retval RADIO_INVALID_ARGUMENT If one of the three function arguments are out
 *                               of bounds.
 */
radio_status_t
rf2xx_set_cca_mode(uint8_t mode, uint8_t ed_threshold)
{
    /*Check function parameters and state.*/
    if ((mode != CCA_ED) &&
        (mode != CCA_CARRIER_SENSE) &&
        (mode != CCA_CARRIER_SENSE_WITH_ED)){
        return RADIO_INVALID_ARGUMENT;
    }

    /* Ensure that the ED threshold is within bounds. */
    if (ed_threshold > RF230_MAX_ED_THRESHOLD){
        return RADIO_INVALID_ARGUMENT;
    }

    /* Ensure that the radio transceiver is not sleeping. */
    if (radio_is_sleeping() == true){
        return RADIO_WRONG_STATE;
    }

    /*Change cca mode and ed threshold.*/
    hal_subregister_write(SR_CCA_MODE, mode);
    hal_subregister_write(SR_CCA_ED_THRES, ed_threshold);

    return RADIO_SUCCESS;
}

/*----------------------------------------------------------------------------*/
/** \brief This function returns the RSSI (Received Signal Strength Indication) value.
 *
 *  \note This function should only be called from the: RX_ON and BUSY_RX. This
 *        can be ensured by reading the current state of the radio transceiver
 *        before executing this function!
 *  \param rssi Pointer to memory location where RSSI value should be written.
 *  \retval RADIO_SUCCESS The RSSI measurement was successful.
 *  \retval RADIO_WRONG_STATE The radio transceiver is not in RX_ON or BUSY_RX.
 */
radio_status_t
radio_get_rssi_value(uint8_t *rssi) /* PORTREF: line 597 */
{

    uint8_t current_state = rf2xx_get_trx_state();
    radio_status_t retval = RADIO_WRONG_STATE;

    /* The RSSI measurement should only be done in RX_ON or BUSY_RX. */
    if ((current_state == RX_ON) ||
        (current_state == BUSY_RX))
    {
        *rssi = hal_subregister_read(SR_RSSI);
        retval = RADIO_SUCCESS;
    }

    return retval;
}
/*----------------------------------------------------------------------------*/
/** \brief This function returns the RSSI value as a raw 8-bit integer.
 */
uint8_t
rf2xx_get_raw_rssi(void)
{ 					/* PORTNOTE: taken from RF230BB as is.
					 * TODO: find out which is more usefull,
					 * rf2xx_get_raw_rssi() or
					 * radio_get_rssi_value().
					 * Neither of these are used yet.
					 **************************************/
    uint8_t retval;
    bool radio_was_off = 0;

    /* The RSSI measurement should only be done in RX_ON or BUSY_RX. */
    if (!RF2xx_receive_on) { /* PORTNOTE: this can be defined as a macro. */ 
       radio_was_off = 1;
       radio_on();
    }

    retval = (int)((signed char)hal_subregister_read(SR_RSSI));

    if(radio_was_off) { /* Together with this. */
      radio_off();
    }

    return retval;
}

/*----------------------------------------------------------------------------*/
/**\brief Retrieves the saved RSSI (Received Signal Strength Indication) value.
 * 	The value returned is the RSSI at the time of the RX_START interrupt.
 *
 * \return The RSSI value, which ranges from 0 to 28,
 *		and can be used to calculate the RSSI in dBm:
 *
 *	Input Signal Strength (in dBm) = -90dBm + (3 * RSSI - 1)
 *
 */
uint8_t
radio_get_saved_rssi_value(void) /* PORTREF: line 198 */
{
    return rssi_val;
}

/*----------------------------------------------------------------------------*/
/**\brief Retrieves the saved LQI (Link Quality Indication) value.
   The value returned is the LQI for the last packet received.

   \return The LQI value, which ranges from 0 to 255.
*/
u8 radio_get_saved_lqi_value(void) /* PORTREF: line 209 */
{
    return ((rx_frame_t*)mac_buffer_rx)->lqi; /* TODO: check if this works with the DS */
}

/*----------------------------------------------------------------------------*/
/** \brief This function returns the current ED threshold used by the CCA algorithm.
 *
 *  \return Current ED threshold, 0 to 15.
 */
uint8_t
rf2xx_get_ed_threshold(void) /* PORTREF: line 480 */
{
    return hal_subregister_read(SR_CCA_ED_THRES);
}

/*============================================================================*/
/*= Section: Battery Monitor =================================================*/
#ifdef RF2XX_CONF_BATTERY_MONITOR
/*----------------------------------------------------------------------------*/
/** \brief This function is used to configure the battery monitor module
 *
 *  \param range True means high voltage range and false low voltage range.
 *  \param voltage_threshold The datasheet defines 16 voltage levels for both
 *                          low and high range.
 *  \retval RADIO_SUCCESS Battery monitor configured
 *  \retval RADIO_WRONG_STATE The device is sleeping.
 *  \retval RADIO_INVALID_ARGUMENT The voltage_threshold parameter is out of
 *                               bounds (Not within [0 - 15]).
 */
radio_status_t
rf2xx_batmon_configure(bool range, uint8_t voltage_threshold) /* PORTREF: line 526 */
{

    /* Check function parameters and state. */
    if (voltage_threshold > BATTERY_MONITOR_HIGHEST_VOLTAGE){
	return RADIO_INVALID_ARGUMENT;
    }

    if (radio_is_sleeping() == true){
	return RADIO_WRONG_STATE;
    }

    /* Write new voltage range and voltage level. */
    if (range == true){
	hal_subregister_write(SR_BATMON_HR, BATTERY_MONITOR_HIGH_VOLTAGE);
    } else {
	hal_subregister_write(SR_BATMON_HR, BATTERY_MONITOR_LOW_VOLTAGE);
    }

    hal_subregister_write(SR_BATMON_VTH, voltage_threshold);

    return RADIO_SUCCESS;
}

/*----------------------------------------------------------------------------*/
/** \brief This function returns the status of the Battery Monitor module.
 *
 *  \note This function can not be called from P_ON or SLEEP. This is ensured
 *        by reading the device state before calling this function.
 *
 *  \retval RADIO_BAT_LOW Battery voltage is below the programmed threshold.
 *  \retval RADIO_BAT_OK Battery voltage is above the programmed threshold.
 */
radio_status_t
rf2xx_batmon_get_status(void) /* PORTREF: line 557 */
{

    radio_status_t batmon_status = RADIO_BAT_LOW;

    if (hal_subregister_read(SR_BATMON_OK) !=
	BATTERY_MONITOR_VOLTAGE_UNDER_THRESHOLD){
	batmon_status = RADIO_BAT_OK;
    }

    return batmon_status;
}

/*----------------------------------------------------------------------------*/
/** \brief This function returns the current threshold volatge used by the
 *         battery monitor (BATMON_VTH).
 *
 *  \note This function can not be called from P_ON or SLEEP. This is ensured
 *        by reading the device state before calling this function.
 *
 *  \return Current threshold voltage, 0 to 15.
 */
uint8_t
rf2xx_batmon_get_voltage_threshold(void) /* PORTREF: line 495 */
{
    return hal_subregister_read(SR_BATMON_VTH);
}

/*----------------------------------------------------------------------------*/
/** \brief This function returns if high or low voltage range is used.
 *
 *  \note This function can not be called from P_ON or SLEEP. This is ensured
 *        by reading the device state before calling this function.
 *
 *  \retval 0 Low voltage range selected.
 *  \retval 1 High voltage range selected.
 */
uint8_t
rf2xx_batmon_get_voltage_range(void) /* PORTREF: line 510 */
{
    return hal_subregister_read(SR_BATMON_HR);
}
#endif /* RF2XX_CONF_BATTERY_MONITOR */

/*============================================================================*/
/*= Section: Clock Settings ==================================================*/
/*----------------------------------------------------------------------------*/
/** \brief This function returns the current clock setting for the CLKM pin.
 *
 *  \retval CLKM_DISABLED CLKM pin is disabled.
 *  \retval CLKM_1MHZ CLKM pin is prescaled to 1 MHz.
 *  \retval CLKM_2MHZ CLKM pin is prescaled to 2 MHz.
 *  \retval CLKM_4MHZ CLKM pin is prescaled to 4 MHz.
 *  \retval CLKM_8MHZ CLKM pin is prescaled to 8 MHz.
 *  \retval CLKM_16MHZ CLKM pin is not prescaled. Output is 16 MHz.
 */
uint8_t
rf2xx_get_clock_speed(void) /* PORTREF: line 580 */
{
    return hal_subregister_read(SR_CLKM_CTRL);
}

/*----------------------------------------------------------------------------*/
/** \brief This function changes the prescaler on the CLKM pin.
 *
 *  \param direct   This boolean variable is used to determine if the frequency
 *                  of the CLKM pin shall be changed directly or not. If direct
 *                  equals true, the frequency will be changed directly. This is
 *                  fine if the CLKM signal is used to drive a timer etc. on the
 *                  connected microcontroller. However, the CLKM signal can also
 *                  be used to clock the microcontroller itself. In this situation
 *                  it is possible to change the CLKM frequency indirectly
 *                  (direct == false). When the direct argument equlas false, the
 *                  CLKM frequency will be changed first after the radio transceiver
 *                  has been taken to SLEEP and awaken again.
 *  \param clock_speed This parameter can be one of the following constants:
 *                     CLKM_DISABLED, CLKM_1MHZ, CLKM_2MHZ, CLKM_4MHZ, CLKM_8MHZ
 *                     or CLKM_16MHZ.
 *
 *  \retval RADIO_SUCCESS Clock speed updated. New state is TRX_OFF.
 *  \retval RADIO_INVALID_ARGUMENT Requested clock speed is out of bounds.
 */
radio_status_t
rf2xx_set_clock_speed(bool direct, uint8_t clock_speed) /* PORTREF: line 635 */
{
    /* Check function parameter and current clock speed. */
    if (clock_speed > CLKM_16MHZ){
            return RADIO_INVALID_ARGUMENT;
    }

    if (rf2xx_get_clock_speed() == clock_speed){ /* PORTNOTE: That's a good thing to do here! */
        return RADIO_SUCCESS;
    }

    /* Select to change the CLKM frequency directly or after returning from SLEEP. */
    if (direct == false){
            hal_subregister_write(SR_CLKM_SHA_SEL, 1);
    } else {
            hal_subregister_write(SR_CLKM_SHA_SEL, 0);
    }
        
    hal_subregister_write(SR_CLKM_CTRL, clock_speed);

    return RADIO_SUCCESS;
}

/*============================================================================*/
/*= Section: Radio Callibration ==============================================*/
#ifdef RF2XX_CONF_CALIBRATION
/*----------------------------------------------------------------------------*/
/** \brief  This function calibrates the Single Side Band Filter.
 *
 *  \retval     RADIO_SUCCESS    Filter is calibrated.
 *  \retval     RADIO_TIMED_OUT  The calibration could not be completed within time.
 *  \retval     RADIO_WRONG_STATE This function can only be called from TRX_OFF or
 *              PLL_ON.
 */
radio_status_t
rf2xx_calibrate_filter(void)
{
    /*Check current state. Only possible to do filter calibration from TRX_OFF or PLL_ON.*/
    uint8_t trx_state = rf2xx_get_trx_state();

    if ((trx_state != TRX_OFF) &&
        (trx_state != PLL_ON)){
        return RADIO_WRONG_STATE;
    }

    /* Start the tuning algorithm by writing one to the FTN_START subregister. */
    hal_subregister_write(SR_FTN_START, 1);
    delay_us(TIME_FTN_TUNING); /* Wait for the calibration to finish. */

    radio_status_t filter_calibration_status = RADIO_TIMED_OUT;

    /* Verify the calibration result. */
    if (hal_subregister_read(SR_FTN_START) == FTN_CALIBRATION_DONE){
        filter_calibration_status = RADIO_SUCCESS;
    }

    return filter_calibration_status;
}

/*----------------------------------------------------------------------------*/
/** \brief  This function calibrates the PLL.
 *
 *  \retval     RADIO_SUCCESS    PLL Center Frequency and Delay Cell is calibrated.
 *  \retval     RADIO_TIMED_OUT  The calibration could not be completed within time.
 *  \retval     RADIO_WRONG_STATE This function can only be called from PLL_ON.
 */
radio_status_t
rf2xx_calibrate_pll(void)
{

    /*Check current state. Only possible to calibrate PLL from PLL_ON state*/
    if (rf2xx_get_trx_state() != PLL_ON){
        return RADIO_WRONG_STATE;
    }

    /* Initiate the DCU and CF calibration loops. */
    hal_subregister_write(SR_PLL_DCU_START, 1);
    hal_subregister_write(SR_PLL_CF_START, 1);

    /* Wait maximum 150 us for the PLL to lock. */
    hal_clear_pll_lock_flag();
    delay_us(TIME_PLL_LOCK);

    radio_status_t pll_calibration_status = RADIO_TIMED_OUT;

    if (hal_get_pll_lock_flag() > 0){
        if (hal_subregister_read(SR_PLL_DCU_START) == PLL_DCU_CALIBRATION_DONE){
            if (hal_subregister_read(SR_PLL_CF_START) == PLL_CF_CALIBRATION_DONE){
                pll_calibration_status = RADIO_SUCCESS;
            }
        }
    }

    return pll_calibration_status;
}

/*----------------------------------------------------------------------------*/
/** \brief Calibrate the internal RC oscillator
 *
 *  This function calibrates the internal RC oscillator, based
 *  on the 1 MHz clock supplied by the AT86RF2xx. In order to
 *  verify the calibration result you can program the CKOUT fuse
 *  and monitor the CPU clock on an I/O pin.
 *
 *  \return TRUE if calibrate passed; FALSE if calibrate failed.
*/
bool
calibrate_rc_osc_clkm(void)
{
	bool success = false;

    /*  Use the 1 MHz CLK_M from the AT86RF230. */
    uint16_t temp, counter;
    uint8_t osccal_saved;
    uint8_t tccr2b, tccr1b, tccr1a;

    /*  in the following line, 1000000ULL represents the 1MHz input signal */
    /*  from the radio.  265 is the number of counts to overflow 8-bit */
    /*  timer 2.  32 is the divide by 32 prescaler for timer 1.  F_CPU is */
    /*  the main clock frequency. */
#define TARGETVAL ((1000000ULL * 256 * 32) / F_CPU)


	osccal_saved = OSCCAL;
	cli();

	rf2xx_set_clock_speed(true, CLKM_1MHz);

    /*  Save current values of timer status. */
	tccr2b = TCCR2B;
	tccr1b = TCCR1B;
	tccr1a = TCCR1A;

    /*  Stop timers 1 and 2. */
    /*  Set timer 1 to normal mode (no CTC, no PWM, just count). */
	TCCR2B = 0;
	TCCR1B = 0;
	TCCR1A = 0;

    for (counter = 0; counter < 1000;  counter++){
	/*  Delete pending timer 1 and 2 interrupts, and clear the */
	/*  counters. */
	    TIFR1 = 0xFF;
	    TIFR2 = 0xFF;
	    TCNT2 = 0;
	    TCNT1 = 0;
	/*  Timer 2 driven from clock divided by 32 */
	    TCCR2B = (1 << CS21) | (1 << CS20);
	/*  Timer 1 driven with external clock */
	    TCCR1B = (1 << CS12) | (1 << CS11);

	/*  Wait for timer 2 to overflow. */
	while (!(TIFR2 & (1 << TOV2))){
		;
	}

	/*  Stop timer 1.  Now, TCNT1 contains the number of CPU cycles */
	/*  counted while timer 2 was counting */
	    TCCR1B = 0;
	    TCCR2B = 0;

	    temp = TCNT1;

	if (temp < (uint16_t)(0.995 * TARGETVAL)){
	    /*  Too fast, slow down */
		OSCCAL--;
	} else if (temp > (uint16_t)(1.005 * TARGETVAL)){
	    /*  Too slow, speed up */
		OSCCAL++;
	} else {
	    /*  We are within +/- 0.5 % of our target frequency, so we're */
	    /*  done. */
		success = true;
		break;
	    }
	}

	rf2xx_set_clock_speed(true, CLKM_DISABLED);

    /*  restore timer status regs */
	TCCR2B = tccr2b;
	TCCR1B = tccr1b;
	TCCR1A = tccr1a;
    if (!success){
	/*  We failed, therefore restore previous OSCCAL value. */
	    OSCCAL = osccal_saved;
	}

	return success;
}

/*----------------------------------------------------------------------------*/
/** \brief Calibrate the internal RC oscillator
 *
 * This function calibrates the internal RC oscillator, based
 * on an external 32KHz crystal connected to TIMER2. In order to
 * verify the calibration result you can program the CKOUT fuse
 * and monitor the CPU clock on an I/O pin.
 */
void
calibrate_rc_osc_32k(void)
{
    /* Calibrate RC Oscillator: The calibration routine is done by clocking TIMER2
     * from the external 32kHz crystal while running an internal timer simultaneously.
     * The internal timer will be clocked at the same speed as the internal RC
     * oscillator, while TIMER2 is running at 32768 Hz. This way it is not necessary
     * to use a timed loop, and keep track cycles in timed loop vs. optimization
     * and compiler.
     */
    uint8_t osccal_original = OSCCAL;
    volatile uint16_t temp;
	
    /* This is bad practice, but seems to work. */
    OSCCAL = 0x80;


  //    PRR0 &= ~((1 << PRTIM2)|(1 << PRTIM1)); /*  Enable Timer 1 and 2 */

    TIMSK2 = 0x00; /*  Disable Timer/Counter 2 interrupts. */
    TIMSK1 = 0x00; /*  Disable Timer/Counter 1 interrupts. */

    /* Enable TIMER/COUNTER 2 to be clocked from the external 32kHz clock crystal.
     * Then wait for the timer to become stable before doing any calibration.
     */
    ASSR |= (1 << AS2);
    while (ASSR & ((1 << TCN2UB)|(1 << OCR2AUB)|(1 << TCR2AUB)|(1 << TCR2BUB))) { ; }
    TCCR2B = 1 << CS20;   /* run timer 2 at divide by 1 (32KHz) */

    AVR_ENTER_CRITICAL_REGION();

    uint8_t counter = 128;
    bool cal_ok = false;
    do{
	/* wait for timer to be ready for updated config */
	TCCR1B = 1 << CS10;

	while (ASSR & ((1 << TCN2UB)|(1 << OCR2AUB)|(1 << TCR2AUB)|(1 << TCR2BUB))) { ; }

	TCNT2 = 0x80;
	TCNT1 = 0;

	TIFR2 = 0xFF;

	/* Wait for TIMER/COUNTER 2 to overflow. Stop TIMER/COUNTER 1 and 2, and
	 * read the counter value of TIMER/COUNTER 1. It will now contain the
	 * number of cpu cycles elapsed within the period.
	 */
	while (!(TIFR2 & (1 << TOV2))){
	    ;
	    }
	temp = TCNT1;

	TCCR1B = 0;

#define cal_upper (31250*1.05) // 32812 = 0x802c
#define cal_lower (31250*0.95) // 29687 = 0x73f7
	/* Iteratively reduce the error to be within limits */
	if (temp < cal_lower) {
	    /* Too slow. Put the hammer down. */
	    OSCCAL++;
	} else if (temp > cal_upper) {
	    /* Too fast, retard. */
	    OSCCAL--;
	} else {
	    /* The CPU clock frequency is now within +/- 0.5% of the target value. */
	    cal_ok = true;
	}

	counter--;
    } while ((counter != 0) && (false == cal_ok));

    if (true != cal_ok) {
	/* We failed, therefore restore previous OSCCAL value. */
	OSCCAL = osccal_original;
    }

    TCCR2B = 0;

    ASSR &= ~(1 << AS2);

    /* Disable both timers again to save power. */
    //    PRR0 |= (1 << PRTIM2);/* |(1 << PRTIM1); */

    AVR_LEAVE_CRITICAL_REGION();
}
#endif

/*============================================================================*/
/*= Section: States and Transitions ==========================================*/
/*----------------------------------------------------------------------------*/
/** \brief Process to handle input packets.
 *         Receive interrupts cause this process to be polled.
 *         It calls the core MAC layer which calls rf230_read to get the packet.
 */
PROCESS_THREAD(rf2xx_process, ev, data)
{
  int len;
  PROCESS_BEGIN();

  #if DEBUG
  rf2xx_process_flag=99;
  #endif

  while(1) {
    PROCESS_YIELD_UNTIL(ev == PROCESS_EVENT_POLL);

    #if DEBUG
    rf2xx_process_flag=42;
    #endif

    #if RF2XX_TIMETABLE_PROFILING
    TIMETABLE_TIMESTAMP(rf2xx_timetable, "poll");
    #endif /* RF2XX_TIMETABLE_PROFILING */

    pending = 0;

    packetbuf_clear();
    len = rf2xx_read(packetbuf_dataptr(), PACKETBUF_SIZE);

    #if DEBUG
    rf2xx_process_flag=1;
    #endif

    if(len > 0) {
      packetbuf_set_datalen(len);

      #if DEBUG
      rf2xx_process_flag=2;
      #endif

      NETSTACK_RDC.input();

      #if RF2XX_TIMETABLE_PROFILING
      TIMETABLE_TIMESTAMP(rf2xx_timetable, "end");
      timetable_aggregate_compute_detailed(&aggregate_time,
					   &rf2xx_timetable);
      timetable_clear(&rf2xx_timetable);
      #endif /* RF2XX_TIMETABLE_PROFILING */

    }
  }

  PROCESS_END();
}

/*---------------------------------------------------------------------------*/
int
rf2xx_interrupt(void)
{
   /* Poll the receive process, unless the stack thinks the radio is off. */
   #if RF2XX_CONF_ALWAYS_ON
   if (RF2xx_receive_on) {
       DEBUGFLOW('+');
   #endif /* RF2XX_CONF_ALWAYS_ON */

   #if RF2XX_CONF_TIMESTAMPS
   interrupt_time = timesynch_time();
   interrupt_time_set = 1;
   #endif /* RF2XX_CONF_TIMESTAMPS */

   process_poll(&rf2xx_process);
  
   #if RF2XX_TIMETABLE_PROFILING
   timetable_clear(&rf2xx_timetable);
   TIMETABLE_TIMESTAMP(rf2xx_timetable, "interrupt");
   #endif /* RF2XX_TIMETABLE_PROFILING */

   pending = 1;
  
#if RADIOSTATS
   RF2xx_receivepackets++;
#endif

   rf2xx_packets_seen++;

   #if RF2XX_CONF_ALWAYS_ON
   } else {
       DEBUGFLOW('-');
       rxframe.length = 0; /* flushrx() */
   }
   #endif

   return 1;
}

/*---------------------------------------------------------------------------*/
/* TODOC */
int /* This could be 'bool'. */
rf2xx_off(void)
{
  /* Don't do anything if we are already turned off. */
  if(RF2xx_receive_on == 0) {
    return 1;
  }

  /* If we are called when the driver is locked, we indicate that the
   * radio should be turned off when the lock is unlocked. */
  if(locked) {
    lock_off = 1;
    return 1;
  }

  /* If we are currently receiving a packet.
   * We don't actually switch the radio off now, but signal that the
   * driver should switch off the radio once the packet has been
   * received and processed, by setting the 'lock_off' variable. */
  if(!rf2xx_is_idle()) {
    lock_off = 1;
    return 1;
  }

  off();
  return 1;
}
/*---------------------------------------------------------------------------*/
static void
off(void)
{
/*  rtimer_set(&rt, RTIMER_NOW()+ RTIMER_ARCH_SECOND*1UL, 1,(void *) rtimercycle, NULL); */
  RF230_receive_on = 0;

#ifdef RF2XX_HOOK_RADIO_OFF
  RF2XX_HOOK_RADIO_OFF();
#endif

  DEBUGFLOW('F');

#if !RF2XX_CONF_ALWAYS_ON
  
  /* Wait any transmission to end. */
  rf2xx_wait_idle(); 

  /* Force the device into TRX_OFF. */   
  radio_reset_state_machine();

#if 0            //optionally sleep
  /* Sleep Radio */
  hal_set_slptr_high();
  RF230_sleeping = 1;
#endif

#endif /* !RF2XX_CONF_ALWAYS_ON */

  ENERGEST_OFF(ENERGEST_TYPE_LISTEN);
}

/*----------------------------------------------------------------------------*/
/** \brief This function calles on() if reciever is off and not locked.
 */
int /* This could be 'bool'. */
rf2xx_on(void)
{
  if(RF2xx_receive_on) {
    return 1;
  }
  if(locked) {
    DEBUGFLOW('L');
    lock_on = 1;
    return 1;
  }

  on();
  return 1;
}
/*----------------------------------------------------------------------------*/
/* TODOC */
static void
on(void)
{
  ENERGEST_ON(ENERGEST_TYPE_LISTEN);
  
#ifdef RF2XX_HOOK_RADIO_ON
  RF2XX_HOOK_RADIO_ON();
#endif

  /* Wake up if radio is sleeping. */
  if (RF2xx_sleeping) {
    hal_set_slptr_low();
    delay_us(TIME_SLEEP_TO_TRX_OFF);
    /* Wake time depends on board capacitance. */
    #ifdef RF2XX_CONF_WAKEUP_DOUBLE_DELAY
    delay_us(TIME_SLEEP_TO_TRX_OFF);
    #endif
    RF2xx_sleeping=0;
  }

  /* Wait any transmission to end. */
  rf2xx_wait_idle();

#if RF2XX_CONF_AACK
  radio_set_trx_state(is_promiscuous ? RX_ON : RX_AACK_ON);
#else
  radio_set_trx_state(RX_ON);
#endif
/*  flushrx(); */
  DEBUGFLOW('O');
  RF2xx_receive_on = 1;
}

/*----------------------------------------------------------------------------*/
/* TODOC */
static char /* This counld be 'bool'. */
rf2xx_is_idle(void)
{
  uint8_t radio_state;
  #ifndef CODE_OPT_MACROS
  radio_state = hal_subregister_read(SR_TRX_STATUS);
  #else
  radio_state = rf2xx_get_trx_state();
  #endif
  if (radio_state != BUSY_TX_ARET &&
      radio_state != BUSY_RX_AACK &&
      radio_state != STATE_TRANSITION &&
      radio_state != BUSY_RX && 
      radio_state != BUSY_TX) {
    return(1);
  } else {
/*    PRINTF(".%u",radio_state); */
    return(0);
  }
}
  
/*----------------------------------------------------------------------------*/
/* TODOC */
static void
rf2xx_wait_idle(void)
{
  while (1) {
    if (rf2xx_is_idle()) break;
  }
}

/*----------------------------------------------------------------------------*/
/** \brief This function checks if the radio is in BUSY_TX or BUSY_TX_ARET.
 *
 *  \retval TRUE or FALSE depending on the state.
 *  
 *  \note If CODE_OPT_TEST is defined this is not defined.
 */
#ifdef CODE_OPT_TEST
bool
rf230_is_ready_to_send() {

  switch(radio_get_trx_state()) {
    case BUSY_TX:
    case BUSY_TX_ARET:
	return false;
  }
	return true;
}
#endif

/*----------------------------------------------------------------------------*/
/** \brief This functions sets is_promiscuous global variable to TRUE or FALSE.
 *         If RF2XX_CONF_AACK is enabled, it sets appropriate states.
 */
/* #ifdef CODE_OPT_TEST */
void
rf230_set_promiscuous_mode(bool mode) {
  if(mode) {
    is_promiscuous = true;
#if RF2XX_CONF_AACK
    rf2xx_set_trx_state(RX_ON);
#endif
  } else {
   is_promiscuous = false;
#if RF2XX_CONF_AACK
   rf2xx_set_trx_state(RX_AACK_ON);
#endif
  }
}
/* #endif */

/*----------------------------------------------------------------------------*/
/** \brief  This function return the Radio Transceivers current state.
 *
 *  \retval     P_ON               When the external supply voltage (VDD) is
 *                                 first supplied to the transceiver IC, the
 *                                 system is in the P_ON (Poweron) mode.
 *  \retval     BUSY_RX            The radio transceiver is busy receiving a
 *                                 frame.
 *  \retval     BUSY_TX            The radio transceiver is busy transmitting a
 *                                 frame.
 *  \retval     RX_ON              The RX_ON mode enables the analog and digital
 *                                 receiver blocks and the PLL frequency
 *                                 synthesizer.
 *  \retval     TRX_OFF            In this mode, the SPI module and crystal
 *                                 oscillator are active.
 *  \retval     PLL_ON             Entering the PLL_ON mode from TRX_OFF will
 *                                 first enable the analog voltage regulator. The
 *                                 transceiver is ready to transmit a frame.
 *  \retval     BUSY_RX_AACK       The radio was in RX_AACK_ON mode and received
 *                                 the Start of Frame Delimiter (SFD). State
 *                                 transition to BUSY_RX_AACK is done if the SFD
 *                                 is valid.
 *  \retval     BUSY_TX_ARET       The radio transceiver is busy handling the
 *                                 auto retry mechanism.
 *  \retval     RX_AACK_ON         The auto acknowledge mode of the radio is
 *                                 enabled and it is waiting for an incomming
 *                                 frame.
 *  \retval     TX_ARET_ON         The auto retry mechanism is enabled and the
 *                                 radio transceiver is waiting for the user to
 *                                 send the TX_START command.
 *  \retval     RX_ON_NOCLK        The radio transceiver is listening for
 *                                 incomming frames, but the CLKM is disabled so
 *                                 that the controller could be sleeping.
 *                                 However, this is only true if the controller
 *                                 is run from the clock output of the radio.
 *  \retval     RX_AACK_ON_NOCLK   Same as the RX_ON_NOCLK state, but with the
 *                                 auto acknowledge module turned on.
 *  \retval     BUSY_RX_AACK_NOCLK Same as BUSY_RX_AACK, but the controller
 *                                 could be sleeping since the CLKM pin is
 *                                 disabled.
 *  \retval     STATE_TRANSITION   The radio transceiver's state machine is in
 *                                 transition between two states.
 */
#ifndef CODE_OPT_MACROS
static uint8_t
rf2xx_get_trx_state(void) /* PORTREF: line 695 */
{
    return hal_subregister_read(SR_TRX_STATUS);
}
#else /* TODO: check if this macro works okay. */
extern uint8_t hal_subregister_read(uint8_t address, uint8_t mask, uint8_t position);
#define rf2xx_get_trx_state() hal_subregister_read(SR_TRX_STATUS);
#endif

/*----------------------------------------------------------------------------*/
/** \brief  This function will change the current state of the radio
 *          transceiver's internal state machine.
 *
 *  \param     new_state        Here is a list of possible states:
 *             - RX_ON        Requested transition to RX_ON state.
 *             - TRX_OFF      Requested transition to TRX_OFF state.
 *             - PLL_ON       Requested transition to PLL_ON state.
 *             - RX_AACK_ON   Requested transition to RX_AACK_ON state.
 *             - TX_ARET_ON   Requested transition to TX_ARET_ON state.
 *
 *  \retval    RADIO_SUCCESS          Requested state transition completed
 *                                  successfully.
 *  \retval    RADIO_INVALID_ARGUMENT Supplied function parameter out of bounds.
 *  \retval    RADIO_WRONG_STATE      Illegal state to do transition from.
 *  \retval    RADIO_BUSY_STATE       The radio transceiver is busy.
 *  \retval    RADIO_TIMED_OUT        The state transition could not be completed
 *                                  within resonable time.
 */
static radio_status_t
rf2xx_set_trx_state(uint8_t new_state) /* PORTREF: line 740 */
{
    uint8_t original_state;

    /* Check function paramter. */
    if (!((new_state == TRX_OFF)    ||
	  (new_state == RX_ON)      ||
	  (new_state == PLL_ON)     ||
	  (new_state == RX_AACK_ON) ||
	  (new_state == TX_ARET_ON))){
	PRINTF("rf2xx_set_trx_state(): Invalid argument.");
	return RADIO_INVALID_ARGUMENT;
    }

    /* Check current state of the radio transceiver. */
    if (radio_is_sleeping() == true){
	PRINTF("rf2xx_set_trx_state(): The radio is sleeping.");
	return RADIO_WRONG_STATE;
    }

    /* Wait for radio to finish previous operation. */
    rf2xx_wait_idle();

    original_state = rf2xx_get_trx_state();
    if (new_state == original_state){
	return RADIO_SUCCESS;
    }

    /* At this point it is clear that the requested new_state is: */
    /* TRX_OFF, RX_ON, PLL_ON, RX_AACK_ON or TX_ARET_ON. */

    /* The radio transceiver can be in one of the following states: */
    /* TRX_OFF, RX_ON, PLL_ON, RX_AACK_ON, TX_ARET_ON. */

    if(new_state == TRX_OFF){
	radio_reset_state_machine(); /* Go to TRX_OFF from any state. */
    } else {
	/* It is not allowed to go from RX_AACK_ON or TX_AACK_ON and directly to */
	/* TX_AACK_ON or RX_AACK_ON respectively. Need to go via RX_ON or PLL_ON. */
	if ((new_state == TX_ARET_ON) &&
	    (original_state == RX_AACK_ON)){
	    /* First do intermediate state transition to PLL_ON, then to TX_ARET_ON. */
	    /* The final state transition to TX_ARET_ON is handled after the if-else if. */
	    hal_subregister_write(SR_TRX_CMD, PLL_ON);
	    delay_us(TIME_STATE_TRANSITION_PLL_ACTIVE);
	} else if ((new_state == RX_AACK_ON) &&
		 (original_state == TX_ARET_ON)){
	    /* First do intermediate state transition to RX_ON, then to RX_AACK_ON. */
	    /* The final state transition to RX_AACK_ON is handled after the if-else if. */
	    hal_subregister_write(SR_TRX_CMD, RX_ON);
	    delay_us(TIME_STATE_TRANSITION_PLL_ACTIVE);
	}

	/* Any other state transition can be done directly. */
	hal_subregister_write(SR_TRX_CMD, new_state);

	/* When the PLL is active most states can be reached in 1us. However, from */
	/* TRX_OFF the PLL needs time to activate. */
	if (original_state == TRX_OFF){
	    delay_us(TIME_TRX_OFF_TO_PLL_ACTIVE);
	} else {
	    delay_us(TIME_STATE_TRANSITION_PLL_ACTIVE);
	}
    } /*  end: if(new_state == TRX_OFF) ... */

    /*Verify state transition.*/
    radio_status_t set_state_status = RADIO_TIMED_OUT;

    if (rf2xx_get_trx_state() == new_state){
	set_state_status = RADIO_SUCCESS;
	#ifdef HAL_HANDLERS
	/* set rx_mode flag based on mode we're changing to */
	/* TODO: This has to be looked at ... */
	if (new_state == RX_ON ||
	    new_state == RX_AACK_ON){
	    rx_mode = true;
	} else {
	    rx_mode = false;
        }
	#endif
    }

    return set_state_status;
}

#ifdef HAL_HANDLERS
/*---------------------------------------------------------------------------*/
/**\brief Callback function, called when the radio receives an RX_START interrupt.
 *        This function reads the radio's RSSI reading for the frame that is being received.
 *
 * \note This function is called from an interrupt - beware of re-entrancy problems.
 *
 * \param isr_timestamp ISR timestamp.
 *
 * \param frame_length The length of the frame that is being received.
 *
 */
static void
radio_rx_start_event(uint32_t const isr_timestamp, uint8_t const frame_length) /* PORTREF: line 180 */
{
    /*  save away RSSI */
    rssi_val =  hal_subregister_read( SR_RSSI );

    /*  call user's rx_start event handler */
    if (user_rx_event)
	user_rx_event(isr_timestamp, frame_length);
}

/*---------------------------------------------------------------------------*/
static void
radio_trx_end_event(uint32_t const isr_timestamp)
{
    volatile uint8_t status;

    /*  call user's trx_end event handler */
    if (user_trx_end_event){
	user_trx_end_event(isr_timestamp);
	return;
    }
    if (rx_mode){
	/* radio has received frame, store it away */
#if RADIOSTATS
	RF2xx_rsigsi=rssi_val;
	RF2xx_receivepackets++;
#endif
	parsed_frame.time = isr_timestamp;
	parsed_frame.rssi = rssi_val;
	
	hal_frame_read(&rx_frame, NULL);
	rx_frame_parse(&rx_frame, &parsed_frame);
	}

    if (!rx_mode){
	/*  Put radio back into receive mode. */
	rf2xx_set_trx_state(TRX_OFF);
	rf2xx_set_trx_state(RX_AACK_ON); /* radio_set_trx_state(rxMode); */

	/*  transmit mode, put end-of-transmit event in queue */
	event_object_t event;
	event.event = 0;
	event.data = 0;
	status = hal_subregister_read(SR_TRAC_STATUS);
	switch(status){
	case TRAC_SUCCESS:
	case TRAC_SUCCESS_DATA_PENDING:
	    event.event = MAC_EVENT_ACK;
	    break;
	case TRAC_NO_ACK:
	case TRAC_CHANNEL_ACCESS_FAILURE:
	    event.event = MAC_EVENT_NACK;
#if RADIOSTATS
	RF2xx_sendfail++;
#endif
	    break;
	case TRAC_SUCCESS_WAIT_FOR_ACK:
	    /*  should only happen in RX mode */
	case TRAC_INVALID:
	    /*  should never happen here */
	default:
#if RADIOSTATS
	    RF2xx_sendfail++;
#endif
	    break;
	}
	if (event.event)
	    mac_put_event(&event);
	process_post(&mac_process, event.event, event.data);
    }
}
#endif /* HAL_HANDLERS */

/*----------------------------------------------------------------------------*/
/** \brief  This function checks if the radio transceiver is sleeping.
 *
 *  \retval     true    The radio transceiver is in SLEEP or one of the *_NOCLK
 *                      states.
 *  \retval     false   The radio transceiver is not sleeping.
 */
static bool
radio_is_sleeping(void) /* PORTREF: line 708 */
{
    bool sleeping = false;

    /* The radio transceiver will be at SLEEP or one of the *_NOCLK states only if */
    /* the SLP_TR pin is high. */
    if (hal_get_slptr() != 0){
	sleeping = true;
    }

    return sleeping;
}

/*----------------------------------------------------------------------------*/
/** \brief  This function will put the radio transceiver to sleep.
 *
 *  \retval    RADIO_SUCCESS          Sleep mode entered successfully.
 *  \retval    RADIO_TIMED_OUT        The transition to TRX_OFF took too long.
 */
radio_status_t
radio_enter_sleep_mode(void) /* PORTREF: line 842 */
{
    if (radio_is_sleeping() == true){
        return RADIO_SUCCESS;
    }

    radio_reset_state_machine(); /* Force the device into TRX_OFF. */

    delay_us(TIME_RESET_TRX_OFF);

    radio_status_t enter_sleep_status = RADIO_TIMED_OUT;

    if (rf2xx_get_trx_state() == TRX_OFF){
        /* Enter Sleep. */
        hal_set_slptr_high();
        enter_sleep_status = RADIO_SUCCESS;
#if RADIOSTATS
        RF2xx_radio_on = 0;
#endif
    }

    return enter_sleep_status;
}

/*----------------------------------------------------------------------------*/
/** \brief  This function will take the radio transceiver from sleep mode and
 *          put it into the TRX_OFF state.
 *
 *  \retval    RADIO_SUCCESS          Left sleep mode and entered TRX_OFF state.
 *  \retval    RADIO_TIMED_OUT        Transition to TRX_OFF state timed out.
 */
radio_status_t
radio_leave_sleep_mode(void) /* PORTREF: line 871 */
{
    /* Check if the radio transceiver is actually sleeping. */
    if (radio_is_sleeping() == false){
        return RADIO_SUCCESS;
    }

    hal_set_slptr_low();
    delay_us(TIME_SLEEP_TO_TRX_OFF);

    radio_status_t leave_sleep_status = RADIO_TIMED_OUT;

    /* Ensure CLKM is OFF. */
    rf2xx_set_clock_speed(true, CLKM_DISABLED);

    /* Ensure that the radio transceiver is in the TRX_OFF state. */
    if (rf2xx_get_trx_state() == TRX_OFF){
        leave_sleep_status = RADIO_SUCCESS;
#if RADIOSTATS
        RF2xx_radio_on = 1;
#endif
    }

    return leave_sleep_status;
}

/*----------------------------------------------------------------------------*/
/** \brief  This function will reset the state machine (to TRX_OFF) from any of
 *          its states, except for the SLEEP state.
 */
static void
radio_reset_state_machine(void) /* PORTREF: line 897 */
{
    hal_set_slptr_low();
    delay_us(TIME_NOCLK_TO_WAKE);
    hal_subregister_write(SR_TRX_CMD, CMD_FORCE_TRX_OFF);
    delay_us(TIME_CMD_FORCE_TRX_OFF);
}

/*----------------------------------------------------------------------------*/
/** \brief  This function will reset all the registers and the state machine of
 *          the radio transceiver. If CODE_OPT_TEST is defined it is not defined.
 */
#ifndef CODE_OPT_TEST
void
rf2xx_reset_trx(void) /* PORTREF: line 910 */
{
    hal_set_rst_low();
    hal_set_slptr_low();
    delay_us(TIME_RESET);
    hal_set_rst_high();
}
#endif

/*============================================================================*/
/*= Section: Data Transmission ===============================================*/

/*----------------------------------------------------------------------------*/
/* TODOC */
static int
rf2xx_prepare(const void *payload, unsigned short payload_len)
{
  int ret = 0;
  uint8_t total_len,*pbuf;

#ifdef RF2XX_CONF_TIMESTAMPS
  struct timestamp timestamp;
#endif /* RF2XX_CONF_TIMESTAMPS */

#ifdef HAL_CALC_CRC
  uint16_t checksum;
#endif /* HAL_CALC_CRC */

  GET_LOCK();

  DEBUGFLOW('P'); /* PORTNOTE: It was commented in RF230BB. */

//  PRINTF("rf230: sending %d bytes\n", payload_len);
//  PRINTSHORT("s%d ",payload_len);

  RIMESTATS_ADD(lltx);

#ifdef HAL_CALC_CRC
  checksum = crc16_data(payload, payload_len, 0);
#endif /* HAL_CALC_CRC */
 
  /* Copy payload to RAM buffer */
  total_len = payload_len + AUX_LEN;
  if (total_len > RF230_MAX_TX_FRAME_LENGTH){
#if RADIOSTATS
    RF2xx_sendfail++;
#endif
#if DEBUG
    printf_P(PSTR("rf2xx_prepare(): Packet is too large (%d, max: %d)\n"),
                                    total_len, RF230_MAX_TX_FRAME_LENGTH);
#endif
    ret = -1;
	goto bail;
  }

  pbuf = &buffer[0];
  memcpy(pbuf, payload, payload_len);
  pbuf += payload_len;

#ifdef HAL_CALC_CRC
  memcpy(pbuf, &checksum, CHECKSUM_LEN);
  pbuf += CHECKSUM_LEN;
#endif /* HAL_CALC_CRC */

#if RF2XX_CONF_TIMESTAMPS
  timestamp.authority_level = timesynch_authority_level();
  timestamp.time = timesynch_time();
  memcpy(pbuf, &timestamp, TIMESTAMP_LEN);
  pbuf += TIMESTAMP_LEN;
#endif /* RF2XX_CONF_TIMESTAMPS */

#ifdef RF2XX_HOOK_TX_PACKET
#ifndef HAL_CALC_CRC
  {
    /* Add a checksum before we log the packet out. */
    uint16_t checksum;
    checksum = crc16_data(payload, payload_len, 0);
    memcpy((buffer + total_len - CHECKSUM_LEN), &checksum, CHECKSUM_LEN);
  }
#endif /* HAL_CALC_CRC */
  RF2XX_HOOK_TX_PACKET(buffer, total_len);
#endif /* RF2XX_HOOK_TX_PACKET */
  

bail:
  RELEASE_LOCK();
  return ret;
}

/*----------------------------------------------------------------------------*/
/* TODOC */
static int
rf2xx_transmit(unsigned short payload_len)
{
  uint8_t tx_power, radio_was_on;
  uint8_t total_len;

#if RF2XX_CONF_TIMESTAMPS
  struct timestamp timestamp;
#endif /* RF2XX_CONF_TIMESTAMPS */

#if HAL_CALC_CRC
  uint16_t checksum;
#endif /* HAL_CALC_CRC */

  GET_LOCK();

  DEBUGFLOW('T'); /* PORTNOTE: It was commented in RF230BB. */

  /* Save receiver state */
  radio_was_on = RF230_receive_on;

  /* If radio is sleeping we have to turn it on first. */
  if (RF2xx_sleeping) { /* PORTNOTE: Could use functions instead. */
    hal_set_slptr_low();
//   delay_us(TIME_SLEEP_TO_TRX_OFF);
    RF2xx_sleeping = 0;
  }
 
  /* Wait for any previous operation or state transition to finish. */
  rf2xx_wait_idle();

  /* Prepare to transmit. */
  #if RF2XX_CONF_AUTORETRIES
  rf2xx_set_trx_state(TX_ARET_ON);
  #else
  rf2xx_set_trx_state(PLL_ON);
  #endif

  tx_power = 0;
  
  if(packetbuf_attr(PACKETBUF_ATTR_RADIO_TXPOWER) > 0) {
    /* Remember the current transmission power. */
    tx_power = rf2xx_get_tx_power_level();
    /* Set the specified transmission power. */
    rf2xx_set_tx_power_level(packetbuf_attr(PACKETBUF_ATTR_RADIO_TXPOWER) - 1);
  }

  total_len = payload_len + AUX_LEN;

#if RF2XX_CONF_TIMESTAMPS
  rtimer_clock_t tx_time = timesynch_time();
#endif /* RF2XX_CONF_TIMESTAMPS */

  #ifndef ATMEL_HAL_MISC
  /* Toggle the SLP_TR pin to initiate the frame transmission. */
  hal_set_slptr_high();
  hal_set_slptr_low();
  #endif /* !ATMEL_HAL_MISC */

  hal_frame_write(buffer, total_len);

  if(RF2xx_receive_on) { ENERGEST_OFF(ENERGEST_TYPE_LISTEN); }

  ENERGEST_ON(ENERGEST_TYPE_TRANSMIT);

#if RADIOSTATS
  RF2xx_sendpackets++;
#endif
 
 /* We wait until transmission has ended so that we get
  * an accurate measurement of the transmission time. */
  rf2xx_wait_idle();


#ifdef ENERGEST_CONF_LEVELDEVICE_LEVELS
  ENERGEST_OFF_LEVEL(ENERGEST_TYPE_TRANSMIT, rf2xx_get_tx_power_level());
#endif

  /* Restore the transmission power */
  if(packetbuf_attr(PACKETBUF_ATTR_RADIO_TXPOWER) > 0) {
    rf2xx_set_tx_power_level(tx_power & 0xff);
  }
 
  /* Restore receive mode. */
  if(radio_was_on) {
 //       DEBUGFLOW('m');
    on();
  }

#if RF230_CONF_TIMESTAMPS
  setup_time_for_transmission = tx_time - timestamp.time;

  if(num_transmissions < 10000) {
    total_time_for_transmission += timesynch_time() - tx_time;
    total_transmission_len += total_len;
    num_transmissions++;
  }
#endif /* RF230_CONF_TIMESTAMPS */

  ENERGEST_OFF(ENERGEST_TYPE_TRANSMIT);

  if(RF2xx_receive_on) {
    ENERGEST_ON(ENERGEST_TYPE_LISTEN);
  } else {
#if RF2XX_CONF_ALWAYS_ON
    /* Enable reception. */
    on();
#else
    /* Go to lower power TRX_OFF state (turn off PLL). */
    hal_subregister_write(SR_TRX_CMD, CMD_FORCE_TRX_OFF);
#endif
  }

  RELEASE_LOCK();
  return 0;

#if TODO
  /* If we are using WITH_SEND_CCA, we get here if the packet
   * wasn't transmitted because of other channel activity. */
 // RIMESTATS_ADD(contentiondrop);
 // PRINTF("rf230: do_send() transmission never started\n");

  //if(packetbuf_attr(PACKETBUF_ATTR_RADIO_TXPOWER) > 0) {
    /* Restore the transmission power */
  //  set_txpower(txpower & 0xff);
 // }

 // RELEASE_LOCK();
 // return -3;			/* Transmission never started! */
#endif /* TODO */
}

/*---------------------------------------------------------------------------*/
static int
rf2xx_send(const void *payload, unsigned short payload_len)
{
  int retval = 0;

#ifdef RF2XX_HOOK_IS_SEND_ENABLED
  if(!RF2XX_HOOK_IS_SEND_ENABLED()) { goto bail; }
#endif
	
  if((retval = rf2xx_prepare(payload, payload_len))) {

#if DEBUG
    printf_P(PSTR("rf2xx_send(): Unable to send, rf2xx_prepare() failed (%d).\n"), retval);
#endif

    goto bail;
  }

  retval = rf2xx_transmit(payload_len);
	
bail:
  return retval;
}

/*---------------------------------------------------------------------------*/
/* TODOC */
int
rf2xx_receiving_packet(void)
{
  uint8_t radio_state;
  #ifndef CODE_OPT_MACROS
  radio_state = hal_subregister_read(SR_TRX_STATUS);
  #else
  radio_state = rf2xx_get_trx_state();
  #endif
  if ((radio_state == BUSY_RX) || (radio_state == BUSY_RX_AACK)) {
    DEBUGFLOW('B');
    return 1;
  } else {
    return 0;
  }
}

/*---------------------------------------------------------------------------*/
/* TODOC */
static int
rf2xx_pending_packet(void)
{
  if (pending) DEBUGFLOW('p');
  return pending;
}
/*----------------------------------------------------------------------------*/
/** \brief  This function will download a frame to the radio transceiver's
 *          transmit buffer and send it.
 *
 *  \param  data_length Length of the frame to be transmitted. 1 to 128 bytes are the valid lengths.
 *  \param  *data   Pointer to the data to transmit
 *
 *  \retval RADIO_SUCCESS Frame downloaded and sent successfully.
 *  \retval RADIO_INVALID_ARGUMENT If the dataLength is 0 byte or more than 127
 *                               bytes the frame will not be sent.
 *  \retval RADIO_WRONG_STATE It is only possible to use this function in the
 *                          PLL_ON and TX_ARET_ON state. If any other state is
 *                          detected this error message will be returned.
 */
#ifdef HAL_HANDLERS
radio_status_t
radio_send_data(uint8_t data_length, uint8_t *data)
{
    /*Check function parameters and current state.*/
    if (data_length > RF230_MAX_TX_FRAME_LENGTH){
#if RADIOSTATS
        RF2xx_sendfail++;
#endif
        return RADIO_INVALID_ARGUMENT;
    }

     /* If we are busy, return */
        if ((rf2xx_get_trx_state() == BUSY_TX) || (rf2xx_get_trx_state() == BUSY_TX_ARET) )
        {
#if RADIOSTATS
        RF2xx_sendfail++;
#endif
        return RADIO_WRONG_STATE;
        }

    rf2xx_set_trx_state(TRX_OFF);
    rf2xx_set_trx_state(TX_ARET_ON);

    /*Do frame transmission.*/

    #ifndef ATMEL_HAL_MISC
    /* Toggle the SLP_TR pin to initiate the frame transmission. */
    hal_set_slptr_high();
    hal_set_slptr_low();
    #endif /* !ATMEL_HAL_MISC */

    hal_frame_write(data, data_length); /* Then write data to the frame buffer. */

#if RADIOSTATS
    RF2xx_sendpackets++;
#endif

    return RADIO_SUCCESS;
}
#endif /* HAL_HANDLERS */

/*---------------------------------------------------------------------------*/
/** \brief This function flushes the RX buffer by setting rx_frame length to 0.
 */
static void
flushrx(void)
{
  rxframe.length=0;
}

/*---------------------------------------------------------------------------*/
/* TODOC */
#ifndef CODE_OPT_TEST /* Disabled for code size optimisation. */
uint8_t *
radio_frame_data(void)
{
	return rx_frame.data;
}
#endif

/*---------------------------------------------------------------------------*/
/* TODOC */
#ifndef CODE_OPT_TEST /* Disabled for code size optimisation. */
uint8_t
radio_frame_length(void)
{
	return rx_frame.length;
}
#endif

/** @} */
/** @} */
/*EOF*/
