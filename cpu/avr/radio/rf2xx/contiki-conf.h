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
#define ATMEL_REGISTER_WRITE	DEFAULT_VALUE

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
