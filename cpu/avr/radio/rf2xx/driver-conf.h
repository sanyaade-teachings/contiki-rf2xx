#define TODO 0

#define DEFAULT_VALUE 1

/** Define transceiver model (hal.h) */
#define ATMEL_RADIO
/** Use one of pre-defined boards (hal.h) */
#define ATMEL_BOARD_SPEC	0

/** Use Atmel's hal_spi_init() (hal.c) */
#define ATMEL_SPI_INIT		DEFAULT_VALUE

/** Use Atmel's Radio Interrupt Routine (hal.c) */
#define ATMEL_RADIO_ISR		0

/** Set rx_mode in hal_register_write() (hal.c) */
#define ATMEL_REGISTER_WRITE	!DEFAULT_VALUE

/** Use various Atmel's techniques in HAL (hal.c)
 ** This include poking of SLP_TR in hal_frame_write(),
 ** a one-line-worth thing in hal_register_read()
 **
 ** WHAT ELSE?
 ************************************************/
#define ATMEL_HAL_MISC		DEFAULT_VALUE

/** Don't use a variable for "dummy" reads (hal.c)
 ** There is no need for DUMMY_WRITE_VOID
 ************************************************/
#define DUMMY_READ_VOID		DEFAULT_VALUE

/** If this is TRUE then we use less function definitions
 ** and put the code in-line for rearly used functions.
 ***********************************************/
#define CODE_OPT_TEST 1

#define CODE_OPT_MACROS 0

/* CSMA is not yet in use. */
#define RADIO_CONF_ENABLE_CSMA 0

#define HAL_HANDLERS 0
#define HAL_CALC_CRC 0
#define RF2XX_CONF_TIMESTAMPS 0
#define RF2XX_CONF_AUTO_CRC 0
#define RF2XX_CONF_BATTERY_MONITOR 0
#define RF2XX_CONF_CALIBRATION 0
#define RF2XX_CONF_ALWAYS_ON 1
#define RF2XX_CONF_TIMESTAMPS 0
#define RF2XX_CONF_BATTERY_MONITOR 0
#define RF2XX_CONF_WAKEUP_DOUBLE_DELAY 0
#define RF2XX_CONF_AUTORETRIES 0

#define HAL_MINIMAL 1

#define DEBUG 0
