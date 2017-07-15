#ifndef _AVRTWI_H_
#define _AVRTWI_H_ 

#ifndef NULL
#define NULL 0
#endif 

#define REPEATED_START true
#define DEFAULT_FREQUENCY 100000UL
/*
 * R/~W bit in SLA+R/W address field.
 */
#define I2C_READ		  1
#define I2C_WRITE		  0
#define I2C_READ_ACK	  2
#define I2C_READ_NAK      3

#define I2C_OK			  0
#define I2C_NOK		     -1
#define I2C_START_NOK    -2
#define I2C_SLA_NAK	     -3
#define I2C_TRANSMIT_NAK -4
#define I2C_READ_NOK     -5
#define I2C_INVALID_PARAMETER -6

/* TWSR values (not bits) */
/* Master */
#define TW_START		    0x08
#define TW_REP_START		0x10
/* Master Transmitter */
#define TW_MT_SLA_ACK		0x18
#define TW_MT_SLA_NACK		0x20
#define TW_MT_DATA_ACK		0x28
#define TW_MT_DATA_NACK		0x30
#define TW_MT_ARB_LOST		0x38
/* Master Receiver */
#define TW_MR_ARB_LOST		0x38
#define TW_MR_SLA_ACK		0x40
#define TW_MR_SLA_NACK		0x48
#define TW_MR_DATA_ACK		0x50
#define TW_MR_DATA_NACK		0x58
/* Slave Transmitter */
#define TW_ST_SLA_ACK		0xA8
#define TW_ST_ARB_LOST_SLA_ACK	0xB0
#define TW_ST_DATA_ACK		0xB8
#define TW_ST_DATA_NACK		0xC0
#define TW_ST_LAST_DATA		0xC8
/* Slave Receiver */
#define TW_SR_SLA_ACK		0x60
#define TW_SR_ARB_LOST_SLA_ACK	0x68
#define TW_SR_GCALL_ACK		0x70
#define TW_SR_ARB_LOST_GCALL_ACK 0x78
#define TW_SR_DATA_ACK		0x80
#define TW_SR_DATA_NACK		0x88
#define TW_SR_GCALL_DATA_ACK	0x90
#define TW_SR_GCALL_DATA_NACK	0x98
#define TW_SR_STOP		0xA0
/* Misc */
#define TW_NO_INFO		0xF8
#define TW_BUS_ERROR		0x00

/*
 * The lower 3 bits of TWSR are reserved on the ATmega163.
 * The 2 LSB carry the prescaler bits on the newer ATmegas.
 */
#define TW_STATUS_MASK		(_BV(TWS7)|_BV(TWS6)|_BV(TWS5)|_BV(TWS4)|\
				_BV(TWS3))
#define TW_STATUS		(TWSR & TW_STATUS_MASK)


#endif  