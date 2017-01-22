#ifndef _DYNAMIXEL_HEADER
#define _DYNAMIXEL_HEADER

#ifdef __cplusplus
extern "C" {
#endif

#define MAXNUM_TXPARAM		(150)
#define MAXNUM_RXPARAM		(60)

#define INST_PING			(1)
#define INST_READ			(2)
#define INST_WRITE			(3)
#define INST_REG_WRITE		(4)
#define INST_ACTION			(5)
#define INST_RESET			(6)
#define INST_SYNC_WRITE		(131)

#define BROADCAST_ID		(254)

#define ERRBIT_VOLTAGE		(1)
#define ERRBIT_ANGLE		(2)
#define ERRBIT_OVERHEAT		(4)
#define ERRBIT_RANGE		(8)
#define ERRBIT_CHECKSUM		(16)
#define ERRBIT_OVERLOAD		(32)
#define ERRBIT_INSTRUCTION	(64)

#define	COMM_TXSUCCESS		(0)
#define COMM_RXSUCCESS		(1)
#define COMM_TXFAIL			(2)
#define COMM_RXFAIL			(3)
#define COMM_TXERROR		(4)
#define COMM_RXWAITING		(5)
#define COMM_RXTIMEOUT		(6)
#define COMM_RXCORRUPT		(7)

///////////// device control methods ////////////////////////

int dxl_initialize( int devIndex, int baudnum );

void dxl_terminate(void);

///////////// set/get packet methods //////////////////////////

void dxl_set_txpacket_id(unsigned char id);

void dxl_set_txpacket_instruction(unsigned char instruction);

void dxl_set_txpacket_parameter(int index, unsigned char value);

void dxl_set_txpacket_length(unsigned char length);

unsigned char dxl_get_rxpacket_error(unsigned char errbit);

unsigned char dxl_get_rxpacket_length(void);

unsigned char dxl_get_rxpacket_parameter(int index);

// utility for value

unsigned short dxl_makeword(unsigned char lowbyte, unsigned char highbyte);

unsigned char dxl_get_lowbyte(unsigned short word);

unsigned char dxl_get_highbyte(unsigned short word);

////////// packet communication methods ///////////////////////

void dxl_tx_packet(void);

void dxl_rx_packet(void);

void dxl_txrx_packet(void);

unsigned char dxl_get_result(void);

//////////// high communication methods ///////////////////////

void dxl_ping(unsigned char id);

unsigned char dxl_read_byte(unsigned char id, unsigned char address);

void dxl_write_byte(unsigned char id, unsigned char address, unsigned char value);

unsigned short dxl_read_word(unsigned char id, unsigned char address);

void dxl_write_word(unsigned char id, unsigned char address, unsigned short value);

#ifdef __cplusplus
}
#endif

#endif
