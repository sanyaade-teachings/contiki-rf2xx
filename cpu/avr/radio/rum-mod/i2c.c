/*
 * i2c.c
 *
 *  Created on: Aug 16, 2010
 *      Author: Gary
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <compat/twi.h>
#include "system.h"
#include "i2c.h"

static bool Tmp100_Present = false;
static bool HP03_Present = false;
static bool i2cBusErr = false;

unsigned char
I2C_xfer( I2C_mode mode, unsigned char data )
{

	switch ( mode )
	{
		case Start:
		case ReStart:
			// Send Start Condition
			TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
			break;

		case AddrTX:
			TWDR  = data & ~TW_READ;
			TWCR = _BV(TWINT) | _BV(TWEN);
			break;

		case AddrRX:
			TWDR  = data | TW_READ;
			TWCR = _BV(TWINT) | _BV(TWEN);
			break;

		case TX:
			 TWDR = data;
			 TWCR = _BV(TWINT) | _BV(TWEN);
			break;

		case RX_ACK:
			TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWEA); // Master reciver mode with ACK
			break;

		case RX_NACK:
			TWCR = _BV(TWINT) | _BV(TWEN); 	   // Master Receiver mode, send NAK afer the last byte
			break;

		case Stop:
			 TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN); /* send stop condition */
			 break;

		default:
		case Reset:
			TWCR =0;
			return 0x1;		// error -- wrong mode
	}
	if (mode != Stop )
	{
		while (!(TWCR & (1 << TWINT)))
		 ; /* wait for completion  */
	}
	 // Return TWI Status Register, mask the prescaler bits (TWPS1,TWPS0)
	 return (TWSR & 0xF8);

}
void
i2c_init( unsigned long f_SCK )
{
    // i2C   TWI clock init
    TWSR = 0;		// Prescaler bits off
    TWBR = (F_CPU / f_SCK - 16) / 2;
//  i.e.  TWBR = 32; == 100Kz at 8Mhz fcpu

    I2C_xfer(Reset,0);
}
static u8 tmp100_ctrl;
_Bool
TMP100_init(unsigned char resolution )
{
#if (APP ==SENSOR )
	if (i2cBusErr)
		return false;

//	tmp100_ctrl = resolution|0x1;	// the ADC resolution plus shutdown mode for one shot operation
	tmp100_ctrl = resolution ;

	if ( I2C_xfer(Start,0) != TW_START)
    {
    	I2C_xfer(Reset,0);
    	i2cBusErr = true;
    }
    if (I2C_xfer(AddrTX, TMP100_I2C_Addr)  == TW_MT_SLA_ACK)
    {
    	Tmp100_Present = true;
        I2C_xfer(TX, TMP100_Ctrl_Reg); 	// internal register address
        I2C_xfer(TX, tmp100_ctrl);		// ADC resolution and Shutdown mode
    }

    I2C_xfer(Stop,0);
    return Tmp100_Present;
#else
    return  0;
#endif
}
float
TMP100_read( void )
{
#if (APP == SENSOR)

	volatile union {
		unsigned char byte[2];
		short val;
	} reading;


	float result;

	if (!Tmp100_Present)
		return 0.0;

	// read temp
	I2C_xfer(Start,0);
	I2C_xfer(AddrTX, TMP100_I2C_Addr );


	/*
	// to trigger the one shot temp conversion -- Doesn't seem to make a diff
	I2C_xfer(TX, TMP100_Ctrl_Reg); 		// internal register address
    I2C_xfer(TX, tmp100_ctrl |0x80);	// trigger OneShot ADC
    I2C_xfer(ReStart,0);	// restart for read mode next
    I2C_xfer(AddrTX, TMP100_I2C_Addr );
	*/
	I2C_xfer(TX, TMP100_Temp_Reg);
	I2C_xfer(ReStart,0);	// restart for read mode next
	I2C_xfer(AddrRX,TMP100_I2C_Addr);
	I2C_xfer(RX_ACK,0);
	reading.byte[1] = TWDR;
	I2C_xfer(RX_NACK,0);
	reading.byte[0] = TWDR;
	I2C_xfer(Stop,0);
	reading.val >>=4;
	// calc the result in deg C
	result = reading.val* 0.0625;

	return result;
#endif
}
#define HP03_EEPROM_ADDR 0xA0
#define HP03_ADC_ADDR 0xEE
static union {
	u16 vals[9];
	u8  bytes[18];
	struct
	{
		u16   C1,C2,C3,C4,C5,C6,C7;
		u8 A,B,C,D;
	} Coeff;

} HP03_Cal;

// TODO: possibly add ack checking and refine error condition
void HP03_init( )
{
#if (APP ==SENSOR )
	u8 i;
		// initialize the HP03 device by reading the calibration coefficients from it's 24c02 like eeprom memory


		// This enables the 32Khz oscialltor on TOSC1 and TOSC2 -- Used for clock on the HP03S Temp/baro device
		// OSC is otherwise not used unless RUMSLEEP is configured, then the 32Khz based timer is used for sleeping also
	    ASSR |= (1 << AS2);
	    DDRA = 0x80 ; 		// enable PA7 as output -- Contriols XCLR line on HP03S device
	    PORTA =0;			// XCLR Low


		if ( I2C_xfer(Start,0) != TW_START)
	    {
	    	I2C_xfer(Reset,0);
	    	i2cBusErr = true;
	    	return;
	    }
	    if (I2C_xfer(AddrTX, HP03_EEPROM_ADDR )  == TW_MT_SLA_ACK)
	    {
	    	HP03_Present = true;	// The HP03 acknowledged an address cycle on the EEPROM address
	        I2C_xfer(TX, 16); 	// Set word pointer to 16 for read of first coefficient, -- will auto increment
	        I2C_xfer(ReStart,0);	// switch to master read mode
	        I2C_xfer(AddrRX, HP03_EEPROM_ADDR); // readdress in read mode now
	        for (i = 0; i<7; i++)				// Read words
	        {
	        	I2C_xfer(RX_ACK,0);				// read cal coeffs MSB
	        	HP03_Cal.vals[i] = (TWDR<<8);
	        	I2C_xfer(RX_ACK,0);				// read cal coeffs LSB
	        	HP03_Cal.vals[i] += TWDR;
	        }

	        for (i = 14; i<18; i++)						// Read bytes
	     	{
	     	        	I2C_xfer(RX_ACK,0);				// read cal coeffs ABCD
	     	        	HP03_Cal.bytes[i] = TWDR;
	     	}

	        I2C_xfer(RX_NACK,0); // one more to stop properly
	    }
		I2C_xfer(Stop,0);		 // and finish by transition into stop state
#endif
}

bool HP03_Read(float * t , float *p)
{
#if (APP ==SENSOR )
	u8 i;
	u16 Y;
	union
	{
		u8 bytes[2];
		u16 val;
	} D2, D1; // D2 = raw Temperatur data , D1 = Raw Pressure data

	float X, Z;
	float dUT;
	float temp;
	float Offs;
	float Sens;
	float Pressure;

	if (!HP03_Present || i2cBusErr)
		return false;

	PORTA |= 0x80;			// XCLR high

	// the temperature Reading
	if ( ( I2C_xfer(Start,0)) != TW_START)
	{
	   	I2C_xfer(Reset,0);
	   	i2cBusErr = true;
	   	return false;
	}

	 I2C_xfer(AddrTX, HP03_ADC_ADDR );
	 I2C_xfer(TX, 0xff);
	 I2C_xfer(TX, 0xE8);	// Temperatur reading address
	 I2C_xfer(Stop,0);
// TODO: This should be a MacAlarm kind of delay, so that the unit is notwound up tight waiting for the delay
	 delay_us(40000);		// delay 40 ms for the result to arrive
	 // get result now
	 I2C_xfer(Start,0);
	 I2C_xfer(AddrTX, HP03_ADC_ADDR );
	 I2C_xfer(TX, 0xFD);
	 I2C_xfer(ReStart,0);
	 I2C_xfer(AddrRX, HP03_ADC_ADDR );
	 I2C_xfer(RX_ACK,0);				// read temp data msb
	 D2.bytes[1] = TWDR;
	 I2C_xfer(RX_NACK,0);				// read temp data lsb
	 D2.bytes[0] = TWDR;
	 I2C_xfer(Stop,0);


	 // The Pressure reading
	 I2C_xfer(Start,0);
	 I2C_xfer(AddrTX, HP03_ADC_ADDR );
	 I2C_xfer(TX, 0xff);
	 I2C_xfer(TX, 0xF0);	// Pressure reading address
	 I2C_xfer(Stop,0);
	 delay_us(40000);		// delay 40 ms for the result to arrive
    // get result now
	 I2C_xfer(Start,0);
	 I2C_xfer(AddrTX, HP03_ADC_ADDR );
	 I2C_xfer(TX, 0xFD);
	 I2C_xfer(ReStart,0);
	 I2C_xfer(AddrRX, HP03_ADC_ADDR );
	 I2C_xfer(RX_ACK,0);				// read temp data msb
	 D1.bytes[1] = TWDR;
	 I2C_xfer(RX_NACK,0);				// read temp data lsb
	 D1.bytes[0] = TWDR;
	 I2C_xfer(Stop,0);


	 if ( D2.val < HP03_Cal.Coeff.C5 )
	 	 Z = HP03_Cal.Coeff.B;
	 else
		 Z= HP03_Cal.Coeff.A;

	X = (float)D2.val - HP03_Cal.Coeff.C5;

	//Y =  pow(2,HP03_Cal.Coeff.C);
    for (Y=1,i = 0; i<HP03_Cal.Coeff.C; i++)
		Y*=2;

	// dUT = X-(X*X/16384.0) * Z / Y;
	dUT = X-X*X*Z / ( 16384.0 * Y) ;

	//Y = pow(2,HP03_Cal.Coeff.D;
	 for (Y=1,i = 0; i<HP03_Cal.Coeff.D; i++)
		Y*=2;

	temp = (250.0 + (dUT * HP03_Cal.Coeff.C6/65536.0) - ( dUT /Y ) ) /10;
	*t = temp;

	Offs = (HP03_Cal.Coeff.C2 +  (HP03_Cal.Coeff.C4-1024.0)* dUT/16384.0)* 4;
	Sens = HP03_Cal.Coeff.C1 + (HP03_Cal.Coeff.C3 * dUT / 1024.0);
	X = (Sens * (D1.val-7168.0) / 16384.0) - Offs;
	Pressure = ((X /32.0) + HP03_Cal.Coeff.C7/10.0);	// in hPa
	*p = Pressure;
#endif
	return true;

}
