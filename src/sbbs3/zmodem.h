/*
 * zmodem.h
 * zmodem constants
 * (C) Mattheij Computer Service 1994
 */

/* $Id: zmodem.h,v 1.39 2006/02/24 09:50:50 rswindell Exp $ */

#ifndef _ZMODEM_H
#define _ZMODEM_H

#include <stdio.h>	/* FILE */

/*
 * ascii constants
 */

#ifndef SOH
#define	SOH			0x01
#define	STX			0x02
#define	EOT			0x04
#define	ENQ			0x05
#define	ACK			0x06
#if 0
#define	LF			0x0a
#define	CR			0x0d
#endif
#define DLE			0x10
#define	XON			0x11
#define	XOFF		0x13
#define	NAK			0x15
#define	CAN			0x18
#endif

/*
 * zmodem constants
 */

#define ZBLOCKLEN	1024		/* "true" Zmodem max subpacket length */

#define ZMAXHLEN    0x10		/* maximum header information length */
#define ZMAXSPLEN	0x400		/* maximum subpacket length */


#define	ZPAD		0x2a		/* pad character; begins frames */
#define	ZDLE		0x18		/* ctrl-x zmodem escape */
#define	ZDLEE		0x58		/* escaped ZDLE */	

#define	ZBIN		0x41		/* binary frame indicator (CRC16) */
#define	ZHEX		0x42		/* hex frame indicator */
#define	ZBIN32		0x43		/* binary frame indicator (CRC32) */
#define	ZBINR32		0x44		/* run length encoded binary frame (CRC32) */

#define	ZVBIN		0x61		/* binary frame indicator (CRC16) */
#define	ZVHEX		0x62		/* hex frame indicator */
#define	ZVBIN32		0x63		/* binary frame indicator (CRC32) */
#define	ZVBINR32	0x64		/* run length encoded binary frame (CRC32) */

#define	ZRESC		0x7e		/* run length encoding flag / escape character */

/*
 * zmodem frame types
 */

#define	ZRQINIT		0x00		/* request receive init (s->r) */
#define	ZRINIT		0x01		/* receive init (r->s) */
#define	ZSINIT		0x02		/* send init sequence (optional) (s->r) */
#define	ZACK		0x03		/* ack to ZRQINIT ZRINIT or ZSINIT (s<->r) */
#define	ZFILE		0x04		/* file name (s->r) */
#define	ZSKIP		0x05		/* skip this file (r->s) */
#define	ZNAK		0x06		/* last packet was corrupted (?) */
#define	ZABORT		0x07		/* abort batch transfers (?) */
#define	ZFIN		0x08		/* finish session (s<->r) */
#define	ZRPOS		0x09		/* resume data transmission here (r->s) */
#define	ZDATA		0x0a		/* data packet(s) follow (s->r) */
#define	ZEOF		0x0b		/* end of file reached (s->r) */
#define	ZFERR		0x0c		/* fatal read or write error detected (?) */
#define	ZCRC		0x0d		/* request for file CRC and response (?) */
#define	ZCHALLENGE	0x0e		/* security challenge (r->s) */
#define	ZCOMPL		0x0f		/* request is complete (?) */	
#define	ZCAN		0x10		/* pseudo frame; 
								   other end cancelled session with 5* CAN */
#define	ZFREECNT	0x11		/* request free bytes on file system (s->r) */
#define	ZCOMMAND	0x12		/* issue command (s->r) */
#define	ZSTDERR		0x13		/* output data to stderr (??) */

/*
 * ZDLE sequences
 */

#define	ZCRCE		0x68		/* CRC next, frame ends, header packet follows */
#define	ZCRCG		0x69		/* CRC next, frame continues nonstop */
#define	ZCRCQ		0x6a		/* CRC next, frame continuous, ZACK expected */
#define	ZCRCW		0x6b		/* CRC next, frame ends,       ZACK expected */
#define	ZRUB0		0x6c		/* translate to rubout 0x7f */
#define	ZRUB1		0x6d		/* translate to rubout 0xff */

/*
 * frame specific data.
 * entries are prefixed with their location in the header array.
 */

/*
 * Byte positions within header array
 */

#define FTYPE 0					/* frame type */

#define ZF0	4					/* First flags byte */
#define ZF1	3
#define ZF2	2
#define ZF3	1

#define ZP0	1					/* Low order 8 bits of position */
#define ZP1	2
#define ZP2	3
#define ZP3	4					/* High order 8 bits of file position */

/*
 * ZRINIT frame
 * zmodem receiver capability flags
 */

#define	ZF0_CANFDX		0x01	/* Receiver can send and receive true full duplex */
#define	ZF0_CANOVIO		0x02	/* receiver can receive data during disk I/O */
#define	ZF0_CANBRK		0x04	/* receiver can send a break signal */
#define	ZF0_CANCRY		0x08	/* Receiver can decrypt DONT USE */
#define	ZF0_CANLZW		0x10	/* Receiver can uncompress DONT USE */
#define	ZF0_CANFC32		0x20	/* Receiver can use 32 bit Frame Check */
#define	ZF0_ESCCTL		0x40	/* Receiver expects ctl chars to be escaped */
#define	ZF0_ESC8		0x80	/* Receiver expects 8th bit to be escaped */

#define ZF1_CANVHDR		0x01	/* Variable headers OK */

/*
 * ZSINIT frame
 * zmodem sender capability
 */

#define ZF0_TESCCTL 	0x40	/* Transmitter expects ctl chars to be escaped */
#define ZF0_TESC8   	0x80	/* Transmitter expects 8th bit to be escaped */

#define ZATTNLEN		0x20	/* Max length of attention string */
#define ALTCOFF			ZF1		/* Offset to alternate canit string, 0 if not used */

/*
 * ZFILE frame
 */

/*
 * Conversion options one of these in ZF0
 */

#define ZF0_ZCBIN		1		/* Binary transfer - inhibit conversion */
#define ZF0_ZCNL		2		/* Convert NL to local end of line convention */
#define ZF0_ZCRESUM		3		/* Resume interrupted file transfer */

/*
 * Management include options, one of these ored in ZF1
 */

#define ZF1_ZMSKNOLOC	0x80	/* Skip file if not present at rx */
#define ZF1_ZMMASK		0x1f	/* Mask for the choices below */
#define ZF1_ZMNEWL		1		/* Transfer if source newer or longer */
#define ZF1_ZMCRC		2		/* Transfer if different file CRC or length */
#define ZF1_ZMAPND		3		/* Append contents to existing file (if any) */
#define ZF1_ZMCLOB		4		/* Replace existing file */
#define ZF1_ZMNEW		5		/* Transfer if source newer */
#define ZF1_ZMDIFF		6		/* Transfer if dates or lengths different */
#define ZF1_ZMPROT		7		/* Protect destination file */
#define ZF1_ZMCHNG		8		/* Change filename if destination exists */

/*
 * Transport options, one of these in ZF2
 */

#define ZF2_ZTNOR		0		/* no compression */
#define ZF2_ZTLZW		1		/* Lempel-Ziv compression */
#define ZF2_ZTRLE		3		/* Run Length encoding */

/*
 * Extended options for ZF3, bit encoded
 */

#define ZF3_ZCANVHDR	0x01	/* Variable headers OK */
								/* Receiver window size override */
#define ZF3_ZRWOVR 		0x04	/* byte position for receive window override/256 */
#define ZF3_ZXSPARS		0x40	/* encoding for sparse file operations */

/*
 * ZCOMMAND frame
 */

#define ZF0_ZCACK1		0x01	/* Acknowledge, then do command */

typedef struct {

	BYTE	rxd_header[ZMAXHLEN];							/* last received header */
	int		rxd_header_len;									/* last received header size */
	ulong	rxd_header_pos;									/* last received header position value */

	/*
	 * receiver capability flags
	 * extracted from the ZRINIT frame as received
	 */

	BOOL can_full_duplex;
	BOOL can_overlap_io;
	BOOL can_break;
	BOOL can_fcs_32;
	BOOL want_fcs_16;
	BOOL escape_ctrl_chars;	
	BOOL escape_8th_bit;

	/*
	 * file management options.
	 * only one should be on
	 */

	int management_newer;
	int management_clobber;
	int management_protect;

	/* from zmtx.c */

	BYTE tx_data_subpacket[8192];
	BYTE rx_data_subpacket[8192];							/* zzap = 8192 */

	char		current_file_name[MAX_PATH+1];
	ulong		current_file_size;
	time_t		current_file_time;
	unsigned	current_file_num;
	unsigned	total_files;
	ulong		total_bytes;
	unsigned	files_remaining;
	unsigned	bytes_remaining;
	ulong		transfer_start_pos;
	time_t		transfer_start_time;

	int receive_32bit_data;
	int use_crc16;
	long ack_file_pos;				/* file position used in acknowledgement of correctly */
									/* received data subpackets */

	int last_sent;

	int n_cans;

	/* Stuff added by RRS */

	/* Status */
	BOOL		cancelled;
	BOOL		local_abort;
	BOOL		file_skipped;
	BOOL		no_streaming;
	unsigned	recv_bufsize;	/* Receiver specified buffer size */
	long		crc_request;
	unsigned	errors;
	unsigned	consecutive_errors;

	/* Configuration */
	BOOL		escape_telnet_iac;
	unsigned	init_timeout;
	unsigned	send_timeout;
	unsigned	recv_timeout;
	unsigned	crc_timeout;
	unsigned	max_errors;
	unsigned	block_size;
	unsigned	max_block_size;

	/* Callbacks */
	void*		cbdata;
	int			(*lputs)(void*, int level, const char* str);
	int			(*send_byte)(void*, BYTE ch, unsigned timeout);
	int			(*recv_byte)(void*, unsigned timeout);
	void		(*progress)(void*, ulong current_pos);
	BOOL		(*is_connected)(void*);
	BOOL		(*is_cancelled)(void*);
	BOOL		(*data_waiting)(void*, unsigned timeout);

} zmodem_t;

void		zmodem_init(zmodem_t*, void* cbdata
						,int	(*lputs)(void*, int level, const char* str)
						,void	(*progress)(void*, ulong current_pos)
						,int	(*send_byte)(void*, BYTE ch, unsigned timeout)
						,int	(*recv_byte)(void*, unsigned timeout)
						,BOOL	(*is_connected)(void*)
						,BOOL	(*is_cancelled)(void*)
						,BOOL	(*data_waiting)(void*, unsigned timeout)
						);
char*		zmodem_ver(char *buf);
const char* zmodem_source(void);
int			zmodem_rx(zmodem_t* zm);
int			zmodem_tx(zmodem_t* zm, BYTE ch);
int			zmodem_abort_receive(zmodem_t*);
int			zmodem_send_ack(zmodem_t*, long pos);
int			zmodem_send_nak(zmodem_t*);
int			zmodem_send_zskip(zmodem_t* zm);
int			zmodem_send_zrinit(zmodem_t*);
int			zmodem_send_pos_header(zmodem_t* zm, int type, long pos, BOOL hex);
int			zmodem_get_zrinit(zmodem_t*);
int			zmodem_get_zfin(zmodem_t* zm);
BOOL		zmodem_get_crc(zmodem_t*, long length, ulong* crc);
void		zmodem_parse_zrinit(zmodem_t*);
void		zmodem_parse_zfile_subpacket(zmodem_t* zm);
int			zmodem_send_zfin(zmodem_t*);
BOOL		zmodem_send_file(zmodem_t*, char* name, FILE* fp, BOOL request_init, time_t* start, ulong* bytes_sent);
int			zmodem_recv_files(zmodem_t* zm, const char* download_dir, ulong* bytes_received);
int			zmodem_recv_init(zmodem_t* zm);
unsigned	zmodem_recv_file_data(zmodem_t*, FILE*, ulong offset);
int			zmodem_recv_file_frame(zmodem_t* zm, FILE* fp);
int			zmodem_recv_header_and_check(zmodem_t* zm);
#endif

