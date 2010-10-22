/* Copyright (c) 2008  ATMEL Corporation
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
*/
/*
  $Id: sensors.h,v 1.1 2009/05/20 20:52:01 mvidales Exp $
*/

#ifndef SENSORS_H
#define SENSORS_H
#include "mac.h"

/// Support for changing all node's interval response time.
#define REPORT_ALL    2
// Support for pining all nodes.
#define PING_ALL      1
void allNodes(u8 func, u16 val);
void StartSensorBC_interval(void);
void StartSensorReadings(void);		// Init and start automatic sensor reading transmissions to COORD
void sensorRequestReading(u16 addr, u16 time);
u8 sensorCalBusy(void);

// Sensor type enum -- not to exceed width of Sensor type field in struct tAD_data & sftSensorReading .
typedef enum {None,Temp1,Temp2,Baro,Accel_X,Accel_Y,Accel_Z,V_Co2,V_Hc,RSSI,V_bat} tSensor_data_type;
// Broadcast data frame type -- do not exceed bitfield lenght below
typedef enum {BC_NONE, BC_SENSOR_DATA,} tBC_DataType;

typedef struct
{
	tSensor_data_type 	SensorType :4 ;		// 16 different sensor types, i.e. temp, baro, angle, etc..
	unsigned short 		ADC_Value  :12;		// with 12 bits resolution each
}__attribute__((packed)) tAD_data;

typedef struct
{
	unsigned short 		Unused 	 :1;	// spare
	tBC_DataType 		DataType :3;	// for different data packages sent  via the BC interface -- for now only sensor AD data
	unsigned short SensorUnitID  :12;	// The unique umber of the broadcasting device -- Could be part of the IEEE address
									    // or possibly we could send the BC frame with a long address ??
// union the folowing should different data types be needed
	tAD_data Readings[10];			// the individual readings the sensor broadcasts
} __attribute__((packed)) tBC_Data;

#ifndef CAL
/// Calibration flag, only compiles calibration code in if the flag is set.
#define CAL 0
#endif

#if (APP == SENSOR)


// What kind of node are we going to be?
#define CAL_POINTS 1  // 1-point cal

#define RETRY_WAIT_PERIOD 50   // Time (mS) to wait after a packet failed to try again.

// Numbering must be consecutive from 1
#define SENSOR_NONE		 0
#define SENSOR_NET       1  // Network stats , RSSI
#define SENSOR_TEMP1  	 2
#define SENSOR_GAS 		 3
#define SENSOR_BAT		 4
#define SENSOR_TEMP2	 5
#define SENSOR_BARO		 6
#define SENSOR_ALL 		 7 		// all of the above in sequence -- must be last


#ifndef SENSOR_TYPE
#error "APP==SENSOR but SENSOR_TYPE not defined";
#endif

/*
   data_structures Data Structures

   The structures listed above describe the frames sent between a
   sensor node and the coordinator.  The 'sft' prefix stands for
   "sensor frame type".
*/

/*
   Sensor frame types
*/
#define SET_NODE_NAME          2   ///< Frame directing the node to change its name string
#define REQ_READING_FRAME      3   ///< Frame requesting that a node begin sending sensor readings
#define READING_FRAME          4   ///< Frame containing a node's sensor reading
#define CAL_REQ_INFO_FRAME     5   ///< Frame requesting a node's calibration information
#define CAL_INFO_FRAME         6   ///< Frame containing a node's calibration information
#define REQ_RAW_DATA_FRAME     7   ///< Frame requesting a node's raw data (A/D) readings
#define RAW_DATA_FRAME         8   ///< Frame containing a node's raw data (A/D) readings
#define CAL_CMD_FRAME          9   ///< Frame sent from coordinator commanding a node to perform a calibration
/** @} */

/// Length of node name string
#define NAME_LENGTH 8
/** Sensor reading packet, sent by sensor node to report its data to
    the coordinator.
*/

// Save cal data (sensor node), used to interactively build the info
	// over time by getting data back from coordinator
	typedef struct{
		double reading[2];  // Entered readings (from coord)
		u16 ad[2];          // A/D readings from sensor (matching
	} __attribute__((packed)) tCalData;

typedef struct{
    u8    				Frametype;    	// Frame type, see   READING_FRAME -- NOTE: this is a waste of space when only 8 frame types are known
    tSensor_data_type 	SensorType :4 ;	// the kind of the reading
    unsigned short    SensorUnitID :12; // part of the MAC address for absolute sensor identification
    float 				reading;
} __attribute__((packed)) sftSensorReading;

/** Sensor calibration request packet, sent by coordinator to ask
    sensor node to reply with its cal info
*/
typedef struct{
    u8    type;          ///< Frame type, see   CAL_REQ_INFO_FRAME and   REQ_RAW_DATA_FRAME
} __attribute__((packed)) sftRequest;

/** Sensor data request packet, sent by coordinator to ask
    sensor node to reply with its computed data
*/
typedef struct{
    u8    type;          ///< Frame type, see   CAL_REQ_INFO_FRAME and   REQ_RAW_DATA_FRAME
    u16   time;          ///< Interval between data frames, in 100mSec intervals.
} __attribute__((packed)) sftRequestData;


/** Sensor calibration info packet, sent by sensor node to report its data to the
    coordinator
*/
typedef struct{
    u8    type;          ///< Frame type, see   CAL_INFO_FRAME
    u8    calType;       ///< Calibration type, 1=1point, 2=2point
    u16   addr;          ///< Node address
    u8    units[5];      ///< Units of sensor reading, as an ASCII string
} __attribute__((packed)) sftCalInfo;

/** Change name of node packet, sent to sensor node */
typedef struct{
    u8    type;          ///< Frame type, see   SET_NODE_NAME
    char  name[NAME_LENGTH]; ///< Name of sensor
} __attribute__((packed)) sftSetName;

/** Raw data (A/D reading) from a sensor node.
*/
typedef struct{
    u8    type;          ///< Frame type, see   RAW_DATA_FRAME
    u16   reading;       ///< Current A/D reading
} __attribute__((packed)) sftRawData;

/** Calibration command frame, sent from the coordinator to a
    end/router node, commanding the node to perform a calibration.
    This packet contains the data required for the calibration.
*/
typedef struct{
    u8    type;           ///< Frame type, see   CAL_CMD_FRAME
    u8    index;          ///< Which reading is this - first or second (0 or 1)?
    u8    reading[8];     ///< The user-entered cal reading, as asciiz string
} __attribute__((packed)) sftCalCommand;


extern u16 node_addr;

void Sensor_HW_Init( void);
void sensorRcvPacket(u8 *payload, u8 len);

void sensorRequestCalInfo(u16 addr);
void sensorRequestRawData(u16 addr);
void sensorSendSetNodeName(u16 addr, char *name);
void sensorSendCalPoint(u8 index, char *str);

char *sensorGetName(void);
void sensorSendSetNodeName(u16 addr, char *name);
void sensorPacketSendSucceed(void);
void sensorPacketSendFailed(void);
void sensorLostNetwork(void);

void sixlowpan_sensorPerSend(u8 len, u8 * data);
void sixlowpan_sensorSend(u16 addr, u8 len, u8 * data);
void sixlowpan_sensorReturn(u8 len, u8 * data);
void SensorSendReading(void);

#if NODETYPE == COORD
	extern char node_name[NAME_LENGTH];
//	extern sftCalInfo coordCalInfo;
#endif

#endif	// APP==SENSOR
/** @} */

#endif
