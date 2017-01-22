#include "dxl_hal.h"
#include "dynamixel.h"

#define ID					(2)
#define LENGTH				(3)
#define INSTRUCTION			(4)
#define ERRBIT				(4)
#define PARAMETER			(5)
#define DEFAULT_BAUDNUMBER	(1)

unsigned char gbInstructionPacket[MAXNUM_TXPARAM+10] = {0};
unsigned char gbStatusPacket[MAXNUM_RXPARAM+10] = {0};
unsigned char gbRxPacketLength = 0;
unsigned char gbRxGetLength = 0;
unsigned char gbCommStatus = COMM_RXSUCCESS;
int giBusUsing = 0;


int dxl_initialize( int devIndex, int baudnum ) {
	float baudrate;	
	baudrate = 2000000.0f / (float)(baudnum + 1);
	
	if( dxl_hal_open(devIndex, baudrate) == 0 )
		return 0;

	gbCommStatus = COMM_RXSUCCESS;
	giBusUsing = 0;
	return 1;
}

void dxl_terminate() {
	dxl_hal_close();
}

void dxl_tx_packet() {
	unsigned char i;
	unsigned char TxNumByte, RealTxNumByte;
	unsigned char checksum = 0;

	if( giBusUsing == 1 )
		return;
	
	giBusUsing = 1;

	if( gbInstructionPacket[LENGTH] > (MAXNUM_TXPARAM+2) ) {
		gbCommStatus = COMM_TXERROR;
		giBusUsing = 0;
		return;
	}
	
	if( gbInstructionPacket[INSTRUCTION] != INST_PING
		&& gbInstructionPacket[INSTRUCTION] != INST_READ
		&& gbInstructionPacket[INSTRUCTION] != INST_WRITE
		&& gbInstructionPacket[INSTRUCTION] != INST_REG_WRITE
		&& gbInstructionPacket[INSTRUCTION] != INST_ACTION
		&& gbInstructionPacket[INSTRUCTION] != INST_RESET
		&& gbInstructionPacket[INSTRUCTION] != INST_SYNC_WRITE ) {
		
		gbCommStatus = COMM_TXERROR;
		giBusUsing = 0;
		return;
	}
	
	gbInstructionPacket[0] = 0xff;
	gbInstructionPacket[1] = 0xff;
	for( i = 0; i < (gbInstructionPacket[LENGTH] + 1); ++i )
		checksum += gbInstructionPacket[i+2];
	gbInstructionPacket[gbInstructionPacket[LENGTH] + 3] = ~checksum;
	
	if( gbCommStatus == COMM_RXTIMEOUT || gbCommStatus == COMM_RXCORRUPT ) {
		dxl_hal_clear();
	}

	TxNumByte = gbInstructionPacket[LENGTH] + 4;
	RealTxNumByte = dxl_hal_tx( gbInstructionPacket, TxNumByte );

	if( TxNumByte != RealTxNumByte ) {
		gbCommStatus = COMM_TXFAIL;
		giBusUsing = 0;
		return;
	}

	if( gbInstructionPacket[INSTRUCTION] == INST_READ ) {
		dxl_hal_set_timeout( gbInstructionPacket[PARAMETER + 1] + 6 );
	} else {
		dxl_hal_set_timeout( 6 );
	}

	gbCommStatus = COMM_TXSUCCESS;
}

void dxl_rx_packet() {
	unsigned char i, j, nRead;
	unsigned char checksum = 0;

	if( giBusUsing == 0 ) {
		return;
	}

	if( gbInstructionPacket[ID] == BROADCAST_ID ) {
		gbCommStatus = COMM_RXSUCCESS;
		giBusUsing = 0;
		return;
	}
	
	if( gbCommStatus == COMM_TXSUCCESS ) {
		gbRxGetLength = 0;
		gbRxPacketLength = 6;
	}
	
	nRead = dxl_hal_rx( (unsigned char*) &gbStatusPacket[gbRxGetLength], gbRxPacketLength - gbRxGetLength );
	gbRxGetLength += nRead;
	if( gbRxGetLength < gbRxPacketLength ) {
		if( dxl_hal_timeout() == 1 ) {
			if(gbRxGetLength == 0) {
				gbCommStatus = COMM_RXTIMEOUT;
			} else {
				gbCommStatus = COMM_RXCORRUPT;
			}
			giBusUsing = 0;
			return;
		}
	}
	
	// Find packet header
	for( i = 0; i < (gbRxGetLength - 1); ++i ) {
		if( gbStatusPacket[i] == 0xff && gbStatusPacket[i + 1] == 0xff ) {
			break;
		} else if( i == gbRxGetLength - 2 && gbStatusPacket[gbRxGetLength - 1] == 0xff ) {
			break;
		}
	}	

	if( i > 0 ) {
		for( j = 0; j < (gbRxGetLength - i); ++j ) {
			gbStatusPacket[j] = gbStatusPacket[j + i];
		}

		gbRxGetLength -= i;		
	}

	if( gbRxGetLength < gbRxPacketLength ) {
		gbCommStatus = COMM_RXWAITING;
		return;
	}

	// Check id pairing
	if( gbInstructionPacket[ID] != gbStatusPacket[ID]) {
		gbCommStatus = COMM_RXCORRUPT;
		giBusUsing = 0;
		return;
	}
	
	gbRxPacketLength = gbStatusPacket[LENGTH] + 4;
	if( gbRxGetLength < gbRxPacketLength ) {
		nRead = dxl_hal_rx( (unsigned char*)&gbStatusPacket[gbRxGetLength], gbRxPacketLength - gbRxGetLength );
		gbRxGetLength += nRead;
		if( gbRxGetLength < gbRxPacketLength ) {
			gbCommStatus = COMM_RXWAITING;
			return;
		}
	}

	// Check checksum
	for( i=0; i<(gbStatusPacket[LENGTH] + 1); ++i ) {
		checksum += gbStatusPacket[i+2];
	}
	checksum = ~checksum;

	if( gbStatusPacket[gbStatusPacket[LENGTH] + 3] != checksum ) {
		gbCommStatus = COMM_RXCORRUPT;
		giBusUsing = 0;
		return;
	}
	
	gbCommStatus = COMM_RXSUCCESS;
	giBusUsing = 0;
}

void dxl_txrx_packet() {
	dxl_tx_packet();

	if( gbCommStatus != COMM_TXSUCCESS ) {
		return;	
	}

	do {
		dxl_rx_packet();		
	} while( gbCommStatus == COMM_RXWAITING );	
}

unsigned char dxl_get_result() {
	return gbCommStatus;
}

void dxl_set_txpacket_id( unsigned char id ) {
	gbInstructionPacket[ID] = id;
}

void dxl_set_txpacket_instruction( unsigned char instruction ) {
	gbInstructionPacket[INSTRUCTION] = instruction;
}

void dxl_set_txpacket_parameter( int index, unsigned char value ) {
	gbInstructionPacket[PARAMETER + index] = value;
}

void dxl_set_txpacket_length( unsigned char length ) {
	gbInstructionPacket[LENGTH] = length;
}

unsigned char dxl_get_rxpacket_error( unsigned char errbit ) {
	if( gbStatusPacket[ERRBIT] & errbit ) {
		return 1;
	}

	return 0;
}

unsigned char dxl_get_rxpacket_length() {
	return gbStatusPacket[LENGTH];
}

unsigned char dxl_get_rxpacket_parameter( int index ) {
	return gbStatusPacket[PARAMETER + index];
}

unsigned short dxl_makeword( unsigned char lowbyte, unsigned char highbyte ) {
	unsigned short word;

	word = highbyte;
	word = word << 8;
	word = word + lowbyte;
	return word;
}

unsigned char dxl_get_lowbyte( unsigned short word ) {
	return word;
}

unsigned char dxl_get_highbyte( unsigned short word ) {
	return word >> 8;
}

void dxl_ping( unsigned char id ) {
	while(giBusUsing);

	gbInstructionPacket[ID] = id;
	gbInstructionPacket[INSTRUCTION] = INST_PING;
	gbInstructionPacket[LENGTH] = 2;
	
	dxl_txrx_packet();
}

unsigned char dxl_read_byte( unsigned char id, unsigned char address ) {
	while(giBusUsing);

	gbInstructionPacket[ID] = id;
	gbInstructionPacket[INSTRUCTION] = INST_READ;
	gbInstructionPacket[PARAMETER] = address;
	gbInstructionPacket[PARAMETER+1] = 1;
	gbInstructionPacket[LENGTH] = 4;
	
	dxl_txrx_packet();

	return gbStatusPacket[PARAMETER];
}

void dxl_write_byte( unsigned char id, unsigned char address, unsigned char value ){
	while(giBusUsing);

	gbInstructionPacket[ID] = id;
	gbInstructionPacket[INSTRUCTION] = INST_WRITE;
	gbInstructionPacket[PARAMETER] = address;
	gbInstructionPacket[PARAMETER+1] = value;
	gbInstructionPacket[LENGTH] = 4;
	
	dxl_txrx_packet();
}

unsigned short dxl_read_word( unsigned char id, unsigned char address ) {
	while(giBusUsing);

	gbInstructionPacket[ID] = id;
	gbInstructionPacket[INSTRUCTION] = INST_READ;
	gbInstructionPacket[PARAMETER] = address;
	gbInstructionPacket[PARAMETER+1] = 2;
	gbInstructionPacket[LENGTH] = 4;
	
	dxl_txrx_packet();

	return dxl_makeword(gbStatusPacket[PARAMETER], gbStatusPacket[PARAMETER+1]);
}

void dxl_write_word( unsigned char id, unsigned char address, unsigned short value ) {
	while(giBusUsing);

	gbInstructionPacket[ID] = id;
	gbInstructionPacket[INSTRUCTION] = INST_WRITE;
	gbInstructionPacket[PARAMETER] = address;
	gbInstructionPacket[PARAMETER+1] = dxl_get_lowbyte(value);
	gbInstructionPacket[PARAMETER+2] = dxl_get_highbyte(value);
	gbInstructionPacket[LENGTH] = 5;
	
	dxl_txrx_packet();
}
