/*
 * Header meant for easy AX-12+ and AX-12A Dynamixel motor control.
 * Use http://support.robotis.com/en/product/actuator/dynamixel/ax_series/dxl_ax_actuator.htm#Actuator_Address_10
 * for more explanations.
 * Created: 20.1.2017. 12:48:09
 *  Author: Juraj Pejnovic
 */ 


#ifndef AX_12_H_
#define AX_12_H_

//utility bool typedef
# ifndef BOOL
#define BOOL

typedef unsigned char bool;

#define TRUE						(1)
#define FALSE						(0)

# endif

#define AX_MODEL_NUMBER_L			(0)
#define AX_MODEL_NUMBER_H			(1)

#define AX_FIRMWARE_VERSION			(2)
#define	AX_ID						(3)
#define	AX_BAUD_RATE				(4)
#define	AX_RETURN_DELAY_TIME		(5)

#define	AX_CW_ANGLE_LIMIT_L			(6)
#define AX_CW_ANGLE_LIMIT_H			(7)

#define AX_CCW_ANGLE_LIMIT_L		(8)
#define AX_CCW_ANGLE_LIMIT_H		(9)

#define AX_TEMPERATURE_LIMIT		(11)

#define AX_LOWEST_VOLTAGE_LIMIT		(12)
#define AX_HIGHEST_VOLTAGE_LIMIT	(13)

#define AX_MAX_TORQUE_L				(14)
#define AX_MAX_TORQUE_H				(15)

#define AX_STATUS_RETURN_LEVEL		(16)
#define AX_ALARM_LED				(17)
#define AX_ALARM_SHUTDOWN			(18)
#define AX_TORQUE_ENABLE			(24)
#define AX_LED						(25)

#define	AX_CW_COMPLIANCE_MARGIN		(26)
#define AX_CCW_COMPLIANCE_MARGIN	(27)

#define AX_CW_COMPLIANCE_SLOPE		(28)
#define AX_CCW_COMPLIANCE_SLOPE		(29)

#define AX_GOAL_POSITION_L			(30)	//goal position lowest byte
#define AX_GOAL_POSITION_H			(31)	//goal position highest byte

#define AX_MOVING_SPEED_L			(32)
#define AX_MOVING_SPEED_H			(33)

#define AX_TORQUE_LIMIT_L			(34)
#define AX_TORQUE_LIMIT_H			(35)

#define AX_PRESENT_POSITION_L		(36)	//present position lowest byte
#define AX_PRESENT_POSITION_H		(37)	//present position highest byte

#define AX_PRESENT_SPEED_L			(38)
#define AX_PRESENT_SPEED_H			(39)

#define AX_PRESENT_LOAD_L			(40)	
#define AX_PRESENT_LOAD_H			(40)

#define AX_PRESENT_VOLTAGE			(42)
#define AX_PRESENT_TEMPERATURE		(43)
#define AX_REGISTERED				(44)
#define AX_MOVING					(46)	//1 if moving, 0 if not moving
#define AX_LOCK						(47)

#define AX_PUNCH_L					(48)
#define AX_PUNCH_H					(49)

#define AX_ERROR_VOLTAGE			(0x1)
#define AX_ERROR_ANGLE				(0x2)
#define AX_ERROR_OVERHEAT			(0x4)
#define AX_ERROR_RANGE				(0x8)
#define AX_ERROR_CHECKSUM			(0x10)
#define AX_ERROR_OVERLOAD			(0x20)
#define AX_ERROR_INSTRUCTION		(0x40)

#define ON							(1)
#define OFF							(0)

#define AX_STATUS_SUCCESS			(0)		//successfull is 0 for use in while loops e.g. while(commandStatus()) will run until succesfull
#define AX_STATUS_TIMEOUT			(1)
#define AX_STATUS_CORRUPT			(2)
#define AX_STATUS_FAIL				(3)
#define AX_STATUS_WAITING			(4)
#define AX_STATUS_ERROR				(5)

#define AX_SPEED_JOINT_MINIMUM		(0)
#define AX_SPEED_JOINT_MAXIMUM		(1023)
#define AX_SPEED_WHEEL_MINIMUM		(1024)
#define AX_SPEED_WHEEL_MAXIMUM		(2047)

typedef struct{
	unsigned char id;
	unsigned short speed;
	unsigned short presentPosition;
	unsigned short goalPosition;
}Ax12;

typedef struct{
	unsigned char direction;
	unsigned short loadRation;
}PresentLoad;

//gets the model number
unsigned short getModelNumber(unsigned char id);

//get the firmware version
unsigned char getFirmwareVersion(unsigned char id);

//returns int from 0 to 254
unsigned char getBaudRate(unsigned char id);

void setBaudRate(unsigned char id, unsigned char rate);

//delay time per data value that takes from the transmission of Instruction Packet until the return of Status Packet
unsigned char getReturnDelayTime(unsigned char id);

//0 to 254 (0xFE) can be used, and the delay time per data value is 2 microseconds
void setReturnDelayTime(unsigned char id, unsigned char time);

/*
CW/CCW Angle Limit
The angle limit allows the motion to be restrained.
The range and the unit of the value is the same as Goal Position(Address 30, 31).
CW Angle Limit: the minimum value of Goal Position(Address 30, 31)
CCW Angle Limit: the maximum value of Goal Position(Address 30, 31)
The following two modes can be set pursuant to the value of CW and CCW.
Operation Type	CW / CCW
Wheel Mode		both are 0
Joint Mode		neither at 0
The wheel mode can be used to wheel-type operation robots since motors of the robots spin infinitely.
The joint mode can be used to multi-joints robot since the robots can be controlled with specific angles.
*/
unsigned short getCWAngleLimit(unsigned char id);

void setCWAngleLimit(unsigned char id, unsigned short limit);

unsigned short getCCWAngleLimit(unsigned char id);

void setCCWAngleLimit(unsigned char id, unsigned short limit);

unsigned char getTemperatureLimit(unsigned char id);

/*
It is the operation range of voltage.
50 to 250 (0x32 ~ 0x96) can be used.  The unit is 0.1V.
For example, if the value is 80, it is 8V.
*/
unsigned char getLowestVoltageLimit(unsigned char id);

void setLowestVoltageLimit(unsigned char id, unsigned char limit);

unsigned char getHighestVoltageLimit(unsigned char id);

void setHighestVoltageLimit(unsigned char id, unsigned char limit);

/*
It is the torque value of maximum output. 0 to 1023 (0x3FF) can be used, and the unit is about 0.1%.
For example, Data 1023 (0x3FF) means that Dynamixel will use 100% of the maximum torque it can produce while Data 512 (0x200) means that Dynamixel will use 50% of the maximum torque. When the power is turned on, Torque Limit (Addresses 34 and 35) uses the value as the initial value.
*/
unsigned short getMaxTorque(unsigned char id);

void setMaxTorque(unsigned char id, unsigned short max);

/*
It decides how to return Status Packet. There are three ways like the below table.
	Value		Return of Status Packet
	0			No return against all commands (Except PING Command)
	1			Return only for the READ command
	2			Return for all commands

*/
unsigned char getStatusReturnLevel(unsigned char id);

void setStatusReturnLevel(unsigned char id, unsigned char level);


/*
Meant to be used with AX_ERROR defines. USE bitwise AND (&) with selected AX_ERROR define to check
*/
unsigned char getAlarmLed(unsigned char id);

/*
Use AX_ERROR defines with bitwise OR ( | ) to make the errorCode
*/
void setAlarmLed(unsigned char id, unsigned char errorCode);

unsigned char getAlarmShutdown(unsigned char id);

/************************************************************************/
/* EEPROM value functions                                               */
/************************************************************************/

//is torque enabled, use with TRUE and FALSE defines
bool isTorqueEnabled(unsigned char id);

//sets the torque enabled, use with TRUE and FALSE
void setTorqueEnable(unsigned char id, unsigned char enabled);

//is LED lamp turned on , use with TRUE and FALSE
bool isLedOn(unsigned char id);

//sets the led on, use with ON and OFF
void setLed(unsigned char id, unsigned char on);

//returns values between 0 and 255
unsigned char getCWComplianceMargin(unsigned char id);

//accepts values between 0 and 255
void setCWComplianceMargin(unsigned char id, unsigned char margin);

//returns values between 0 and 255
unsigned char getCCWComplianceMargin(unsigned char id);

//accepts values between 0 and 255
void setCCWComplianceMargin(unsigned char id, unsigned char margin);

/*
It exists in each direction of CW/CCW and sets the level of Torque near the goal position.
Compliance Slope is set in 7 steps, the higher the value, the more flexibility is obtained.
Data representative value is actually used value.  That is, even if the value is set to 25, 16 is used internally as the representative value.

Step	Data Value			Data Representative Value
1		0 (0x00) ~ 3(0x03)	2 (0x02)
2		4(0x04) ~ 7(0x07)	4 (0x04)
3		8(0x08)~15(0x0F)	8 (0x08)
4		16(0x10)~31(0x1F)	16 (0x10)
5		32(0x20)~63(0x3F)	32 (0x20)
6		64(0x40)~127(0x7F)	64 (0x40)
7		128(0x80)~254(0xFE)	128 (0x80)
*/

//Returns values from "Data Representative Value" column
unsigned char getCWComplianceSlope(unsigned char id);

//accepts values from 0 to 255
void setCWComplianceSlope(unsigned char id, unsigned char step);

//Returns values from "Data Representative Value" column
unsigned char getCCWComplianceSlope(unsigned char id);

//accepts values from 0 to 255
void setCCWComplianceSlope(unsigned char id, unsigned char step);

//returns values from 0 to 1023, 512 is centre position
unsigned short getGoalPosition(unsigned char id);

//accepts values from 0 to 1023
void setGoalPosition(unsigned char id, unsigned short position);

/*
returns 0 to 1023 if the motor is in joint mode
returns 0 to 2047 if the motor is in wheel mode
*/
unsigned short getMovingSpeed(unsigned char id);

/*
accepts 0 to 1023 if the motor is in joint mode
accepts 0 to 2047 if the motor is in wheel mode
*/
void setMovingSpeed(unsigned char id, unsigned short speed);

//returns values from 0 to 1023, 512 is about 50%
unsigned short getTorqueLimit(unsigned char id);

//accepts values from 0 to 1023
void setTorqueLimit(unsigned char id, unsigned short limit);

//returns values from 0 to 1023
unsigned short getPresentPosition(unsigned char id);

//returns values from 0 to 2047
unsigned short getPresentSpeed(unsigned char id);

/*
returns present load of the motor
bits 0 to 9 are data bits, bit 10 is direction bit, 0 = CCW, 1 = CW
all 11 bits can be read at once, it that case 0 to 1023 are CCW values, 
1024 to 2047 are CW values
*/
unsigned short getPresentLoad(unsigned char id);

//returns current voltage, number returned is 10 times greater than current voltage, e.g. for 1,4V it returns 14
unsigned char getPresentVoltage(unsigned char id);

//returns present temperature in Celsius degrees
unsigned char getPresentTemperature(unsigned char id);

//returns FALSE if no commands are transmitted by REG_WRITE, TRUE if there are commands transmited
bool hasRegisteredInstruction(unsigned char id);

//returns TURE if motor is moving, FALSE if it is not
bool isMoving(unsigned char id);

//returns TRUE if EEPROM values cannot be modified, FALSE if they can be modified
bool isLocked(unsigned char id);

//accepts TRUE or FALSE, locks the EEPROM values to modifications, of set to TRUE, motor must be restarted to reset to FALSE
void setLocked(unsigned char id, unsigned char locked);

//returns values from 0x20 to 0x3FF
unsigned short getPunch(unsigned char id);

//accepts values from 0x20 to 0x3FF
void setPunch(unsigned char id, unsigned short punch);

//updates the given motor with current information, id must be set
void updateMotorInfo(Ax12 *motor);

Ax12 getMotorInfo(unsigned char id);

//checks the status of previous command given
unsigned char getCommandStatus(void);

#endif /* AX_12_H_ */