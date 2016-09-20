/**
 * \file HardwareSerialUsart.h
 *
 * \brief USART peripheral library for SAMBO platforms
 *
 * Copyright (c) 2016 Nate Kamrath. All rights reserved.
 *
 * \sambo_license_start
 *
 * \page "SAMBO License"
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL AUTHORS BE LIABLE 
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \sambo_license_stop
 *
 */


#ifndef __HARDWARESERIALUSART_H__
#define __HARDWARESERIALUSART_H__

#include <asf.h>

#include "Stream.h"

#define SERIAL_USART_RX_BUFFER_SIZE		512

// Define config for Serial.begin(baud, config);
#define SERIAL_5N1 0x00
#define SERIAL_6N1 0x02
#define SERIAL_7N1 0x04
#define SERIAL_8N1 0x06
#define SERIAL_5N2 0x08
#define SERIAL_6N2 0x0A
#define SERIAL_7N2 0x0C
#define SERIAL_8N2 0x0E
#define SERIAL_5E1 0x20
#define SERIAL_6E1 0x22
#define SERIAL_7E1 0x24
#define SERIAL_8E1 0x26
#define SERIAL_5E2 0x28
#define SERIAL_6E2 0x2A
#define SERIAL_7E2 0x2C
#define SERIAL_8E2 0x2E
#define SERIAL_5O1 0x30
#define SERIAL_6O1 0x32
#define SERIAL_7O1 0x34
#define SERIAL_8O1 0x36
#define SERIAL_5O2 0x38
#define SERIAL_6O2 0x3A
#define SERIAL_7O2 0x3C
#define SERIAL_8O2 0x3E

#ifdef __cplusplus

class HardwareSerialUsart : public Stream
{
public:
	HardwareSerialUsart(Usart* peripheral_pointer);

	void begin(unsigned long baud);
	void begin(unsigned long, uint8_t);
	void end();
	virtual int available(void);
	virtual int peek(void);
	virtual int read(void);
	int availableForWrite(void);
	virtual void flush(void);
	virtual size_t write(uint8_t data);
	inline size_t write(unsigned long n) { return write((uint8_t)n); }
	inline size_t write(long n) { return write((uint8_t)n); }
	inline size_t write(unsigned int n) { return write((uint8_t)n); }
	inline size_t write(int n) { return write((uint8_t)n); }
	using Print::write; // pull in write(str) and write(buf, size) from Print
	operator bool() { return true; }

	//interrupt callbacks to service sending/receiving data
	void tx_empty_callback(void);
	void rx_ready_callback(void);

	protected:
	volatile uint8_t rx_buffer[SERIAL_USART_RX_BUFFER_SIZE];
	volatile uint8_t* rx_buffer_end;
	volatile uint8_t* rx_buffer_head;
	volatile uint8_t* rx_buffer_tail;
	volatile uint16_t rx_buffer_size;
	uint8_t rx_buffer_append(uint8_t data);
	uint8_t rx_buffer_remove(uint8_t* data);

	volatile uint8_t tx_buffer[SERIAL_USART_RX_BUFFER_SIZE];
	volatile uint8_t* tx_buffer_end;
	volatile uint8_t* tx_buffer_head;
	volatile uint8_t* tx_buffer_tail;
	volatile uint16_t tx_buffer_size;
	
	uint8_t tx_buffer_append(uint8_t data);
	uint8_t tx_buffer_remove(uint8_t* data);

	Usart* usart_peripheral;

}; //HardwareSerialUsart

#endif //__cplusplus

#endif //__HARDWARESERIALUSART_H__
