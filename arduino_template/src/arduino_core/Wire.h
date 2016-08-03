/*
  TwoWire.h - TWI/I2C library for Arduino & Wiring
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Modified 2012 by Todd Krein (todd@krein.org) to implement repeated starts
  Modified 2016 by Nate Kamrath (nate@samduino.com) for Samduino Port
*/

#ifndef TwoWire_h
#define TwoWire_h

#include <asf.h>
#include <inttypes.h>
#include "Stream.h"

#define BUFFER_LENGTH 32

// WIRE_HAS_END means Wire has end()
#define WIRE_HAS_END 1

class TwoWire : public Stream
{
  public:
    TwoWire(Twi* twiPtr);
    void begin();
    void begin(uint8_t);
    void begin(int);
    void end();
    void setClock(uint32_t);
    void beginTransmission(uint8_t);
    void beginTransmission(int);
    uint8_t endTransmission(void);
    uint8_t endTransmission(uint8_t);
    uint8_t requestFrom(uint8_t, uint8_t);
    uint8_t requestFrom(uint8_t, uint8_t, uint8_t);
	uint8_t requestFrom(uint8_t, uint8_t, uint32_t, uint8_t, uint8_t);
    uint8_t requestFrom(int, int);
    uint8_t requestFrom(int, int, int);
    virtual size_t write(uint8_t);
    virtual size_t write(const uint8_t *, size_t);
    virtual int available(void);
    virtual int read(void);
    virtual int peek(void);
    virtual void flush(void);
    void onReceive( void (*)(int) );
    void onRequest( void (*)(void) );

    inline size_t write(unsigned long n) { return write((uint8_t)n); }
    inline size_t write(long n) { return write((uint8_t)n); }
    inline size_t write(unsigned int n) { return write((uint8_t)n); }
    inline size_t write(int n) { return write((uint8_t)n); }
    using Print::write;
	
private:
	Twi* twiPeripheral;
	uint8_t rxBuffer[];
	uint8_t rxBufferIndex;
	uint8_t rxBufferLength;

	uint8_t txAddress;
	uint8_t txBuffer[];
	uint8_t txBufferIndex;
	uint8_t txBufferLength;

	uint8_t transmitting;
	void (*user_onRequest)(void);
	void (*user_onReceive)(int);
	void onRequestService(void);
	void onReceiveService(uint8_t*, int);
	
	//moved from twi.c arduion to here because each TWI module needs these
	//and Samduino has more than one!
	volatile uint8_t twi_state;
	volatile uint8_t twi_slarw;
	volatile uint8_t twi_sendStop;			// should the transaction end with a stop
	volatile uint8_t twi_inRepStart;			// in the middle of a repeated start

	void (*twi_onSlaveTransmit)(void);
	void (*twi_onSlaveReceive)(uint8_t*, int);

	uint8_t twi_masterBuffer[BUFFER_LENGTH];
	volatile uint8_t twi_masterBufferIndex;
	volatile uint8_t twi_masterBufferLength;

	uint8_t twi_txBuffer[BUFFER_LENGTH];
	volatile uint8_t twi_txBufferIndex;
	volatile uint8_t twi_txBufferLength;

	uint8_t twi_rxBuffer[BUFFER_LENGTH];
	volatile uint8_t twi_rxBufferIndex;

	volatile uint8_t twi_error;
	
};

extern TwoWire Wire;
extern TwoWire Wire2;

#endif

