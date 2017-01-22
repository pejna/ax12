/*
 * .c file accompanying ax_12.h
 * explanations and documentation for all functions are in ax_12.h
 *
 * Created: 20.1.2017. 12:47:40
 *  Author: Juraj Pejnovic
 */ 

 #include "ax_12.h"
 #include "dynamixel.h"

unsigned short getModelNumber(unsigned char id) {
	return dxl_read_word( id, AX_MODEL_NUMBER_L);
}


unsigned char getFirmwareVersion(unsigned char id) {
		return dxl_read_word( id, AX_FIRMWARE_VERSION);
}

unsigned char getBaudRate(unsigned char id) {
	return dxl_read_word( id, AX_BAUD_RATE);

}

void setBaudRate(unsigned char id, unsigned char rate) {
	dxl_write_byte( id, AX_BAUD_RATE, rate );
}

unsigned char getReturnDelayTime(unsigned char id) {
	return dxl_read_word( id, AX_RETURN_DELAY_TIME);
}

void setReturnDelayTime(unsigned char id, unsigned char time) {
	dxl_write_byte( id, AX_RETURN_DELAY_TIME, time );
}

unsigned short getCWAngleLimit(unsigned char id) {
	return dxl_read_word( id, AX_CW_ANGLE_LIMIT_L);
}

void setCWAngleLimit(unsigned char id, unsigned short limit) {
	dxl_write_word( id, AX_CW_ANGLE_LIMIT_L, limit );
}

unsigned short getCCWAngleLimit(unsigned char id) {
	return dxl_read_word( id, AX_CCW_ANGLE_LIMIT_L);
}

void setCCWAngleLimit(unsigned char id, unsigned short limit) {
	dxl_write_word( id, AX_CCW_ANGLE_LIMIT_L, limit );
}

unsigned char getTemperatureLimit(unsigned char id){
	return dxl_read_byte( id, AX_TEMPERATURE_LIMIT);
}

unsigned char getLowestVoltageLimit(unsigned char id){
	return dxl_read_byte( id, AX_LOWEST_VOLTAGE_LIMIT);

}

void setLowestVoltageLimit(unsigned char id, unsigned char limit){
	dxl_write_byte( id, AX_LOWEST_VOLTAGE_LIMIT, limit );
}

unsigned char getHighestVoltageLimit(unsigned char id){
	return dxl_read_byte( id, AX_HIGHEST_VOLTAGE_LIMIT);
}

void setHighestVoltageLimit(unsigned char id, unsigned char limit){
	dxl_write_byte( id, AX_HIGHEST_VOLTAGE_LIMIT, limit );

}

unsigned short getMaxTorque(unsigned char id){
	return dxl_read_word( id, AX_MAX_TORQUE_L);
}

void setMaxTorque(unsigned char id, unsigned short max){
	dxl_write_word( id, AX_MAX_TORQUE_L, max );	
}

unsigned char getStatusReturnLevel(unsigned char id){
	return dxl_read_byte( id, AX_STATUS_RETURN_LEVEL);
}

void setStatusReturnLevel(unsigned char id, unsigned char level){
	dxl_write_byte( id, AX_STATUS_RETURN_LEVEL, level );
}

unsigned char getAlarmLed(unsigned char id){
	return dxl_read_byte( id, AX_ALARM_LED);
}


void setAlarmLed(unsigned char id, unsigned char errorCode){
	dxl_write_byte( id, AX_ALARM_LED, errorCode );

}

unsigned char getAlarmShutdown(unsigned char id){
	return dxl_read_byte( id, AX_ALARM_SHUTDOWN);
}

bool isTorqueEnabled(unsigned char id){
	return dxl_read_byte( id, AX_TORQUE_ENABLE);
}

void setTorqueEnable(unsigned char id, unsigned char enabled){
	dxl_write_byte( id, AX_TORQUE_ENABLE, enabled );
}

bool isLedOn(unsigned char id){
	return dxl_read_byte( id, AX_LED);
}

//sets the led on, use with ON and OFF
void setLed(unsigned char id, unsigned char on){
	dxl_write_byte( id, AX_LED, on );

}

unsigned char getCWComplianceMargin(unsigned char id){
	return dxl_read_byte( id, AX_CW_COMPLIANCE_MARGIN);
}

void setCWComplianceMargin(unsigned char id, unsigned char margin){
	dxl_write_byte( id, AX_CW_COMPLIANCE_MARGIN, margin );
}

unsigned char getCCWComplianceMargin(unsigned char id){
	return dxl_read_byte( id, AX_CCW_COMPLIANCE_MARGIN);
}

void setCCWComplianceMargin(unsigned char id, unsigned char margin){
	dxl_write_word( id, AX_CCW_COMPLIANCE_MARGIN, margin );
}

unsigned char getCWComplianceSlope(unsigned char id){
	return dxl_read_byte( id, AX_CW_COMPLIANCE_MARGIN);
}

void setCWComplianceSlope(unsigned char id, unsigned char step){
	dxl_write_word( id, AX_CW_COMPLIANCE_SLOPE, step );
}

unsigned char getCCWComplianceSlope(unsigned char id){
	return dxl_read_byte( id, AX_CCW_COMPLIANCE_MARGIN);
}

void setCCWComplianceSlope(unsigned char id, unsigned char step){
	dxl_write_byte( id, AX_CCW_COMPLIANCE_SLOPE, step);

}

unsigned short getGoalPosition(unsigned char id){
	return dxl_read_word( id, AX_GOAL_POSITION_L);
}

void setGoalPosition(unsigned char id, unsigned short position){
	dxl_write_word( id, AX_GOAL_POSITION_L, position );
}

unsigned short getMovingSpeed(unsigned char id){
	return dxl_read_word( id, AX_MOVING_SPEED_L);
}

void setMovingSpeed(unsigned char id, unsigned short speed){
		dxl_write_word( id, AX_MOVING_SPEED_L, speed );
}

unsigned short getTorqueLimit(unsigned char id){
	return dxl_read_word( id, AX_TORQUE_LIMIT_L);
}

void setTorqueLimit(unsigned char id, unsigned short limit){
	dxl_write_word( id, AX_TORQUE_LIMIT_L, limit );
}

unsigned short getPresentPosition(unsigned char id){
	return dxl_read_word( id, AX_PRESENT_POSITION_L);
}

unsigned short getPresentSpeed(unsigned char id){
	return dxl_read_word( id, AX_PRESENT_SPEED_L);
}

unsigned short getPresentLoad(unsigned char id){
	return dxl_read_word( id, AX_PRESENT_LOAD_L);
}

unsigned char getPresentVoltage(unsigned char id){
	return dxl_read_byte( id, AX_PRESENT_VOLTAGE);
}

unsigned char getPresentTemperature(unsigned char id){
	return dxl_read_byte( id, AX_PRESENT_TEMPERATURE);
}

unsigned char hasRegisteredInstruction(unsigned char id){
	return dxl_read_byte( id, AX_REGISTERED);
}

bool isMoving(unsigned char id){
	return dxl_read_byte( id, AX_MOVING);
}

bool isLocked(unsigned char id){
	return dxl_read_byte( id, AX_LOCK);
}

void setLocked(unsigned char id, unsigned char locked){
	dxl_write_byte( id, AX_LOCK, locked );
}

//returns values from 0x20 to 0x3FF
unsigned short getPunch(unsigned char id){
	return dxl_read_word( id, AX_PUNCH_L);
}

void setPunch(unsigned char id, unsigned short punch){
	dxl_write_word( id, AX_PUNCH_L, punch );

}

void updateMotor(Ax12 *motor){
	motor->goalPosition = getGoalPosition(motor->id);
	motor->presentPosition = getPresentPosition(motor->id);
	motor->speed = getPresentSpeed(motor->id);
}

unsigned char getCommandStatus(void){
	int result = dxl_get_result();
	switch (result) {
	case COMM_RXCORRUPT:
		return AX_STATUS_CORRUPT;
	case COMM_RXSUCCESS:
	case COMM_TXSUCCESS:
		return AX_STATUS_SUCCESS;
	case COMM_RXTIMEOUT:
		return AX_STATUS_TIMEOUT;
	case COMM_TXERROR:
		return AX_STATUS_ERROR;
	default:
		return AX_STATUS_FAIL;
	}
}