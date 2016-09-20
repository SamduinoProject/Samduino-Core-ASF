/*
  TwoWire.cpp - TWI/I2C library for Wiring & Arduino
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

extern "C" {
  #include <stdlib.h>
  #include <string.h>
  #include <inttypes.h>
}

#include "Wire.h"

volatile uint32_t lastStatus = 0;

TwoWire::TwoWire(Twi* twiPtr)
{
	//set the peripheral pointer
	twiPeripheral = twiPtr;
}

void TwoWire::begin(void)
{		
	//IRQn twiIrqn = TWI0_IRQn;
	if(twiPeripheral == TWI0)
	{
		//enable clock to the peripheral
		sysclk_enable_peripheral_clock(ID_TWI0);
		//set gpio pins to TWI control which is peripheral A Mux setting
		pio_configure(PIOA, PIO_PERIPH_A, PIO_PA4A_TWCK0, PIO_DEFAULT);
		pio_configure(PIOA, PIO_PERIPH_A, PIO_PA3A_TWD0, PIO_DEFAULT);
		//twiIrqn = TWI0_IRQn;
	}
	else if(twiPeripheral == TWI1)
	{
		//enable clock to the peripheral
		sysclk_enable_peripheral_clock(ID_TWI1);
		//set gpio pins to TWI control which is peripheral A Mux setting
		pio_configure(PIOB, PIO_PERIPH_A, PIO_PB5_IDX, PIO_DEFAULT);
		pio_configure(PIOB, PIO_PERIPH_A, PIO_PB4_IDX, PIO_DEFAULT);
		//twiIrqn = TWI1_IRQn;
	}
	
	twi_reset(twiPeripheral);
	twi_options_t defaultOptions;
	defaultOptions.chip = 0;
	defaultOptions.smbus = 0;
	defaultOptions.master_clk = sysclk_get_peripheral_hz();
	defaultOptions.speed = 50000; //100khz standard default speed
	twi_master_setup(twiPeripheral, &defaultOptions);
	
	//setup the buffers
	rx_buffer_size = 0;
	rx_buffer_head = rx_buffer;
	rx_buffer_tail = rx_buffer;
	rx_buffer_end = &rx_buffer[TWI_BUFFER_SIZE-1];

	tx_buffer_size = 0;
	tx_buffer_head = tx_buffer;
	tx_buffer_tail = tx_buffer;
	tx_buffer_end = &tx_buffer[TWI_BUFFER_SIZE-1];
	
	//twi_enable_interrupt(twiPeripheral, (TWI_IER_RXRDY | TWI_IER_ENDTX));// | TWI_IER_ENDTX));
	//NVIC_EnableIRQ(twiIrqn);
	//twi_enable_master_mode(twiPeripheral);
	//twi_master_init(twiPeripheral, &defaultOptions);
}

void TwoWire::begin(uint8_t address)
{
	begin();
	//set up the periphieral
	twi_reset(twiPeripheral);
	twi_options_t options;
	options.chip = address;
	options.smbus = 0;
	options.master_clk = sysclk_get_main_hz();
	options.speed = 50000; //100khz standard default speed
	twi_master_init(twiPeripheral, &options);
}

void TwoWire::begin(int address)
{
	begin((uint8_t)address);
}

void TwoWire::end(void)
{
	twi_disable_master_mode(twiPeripheral);
	if(twiPeripheral == TWI0)
	{
		sysclk_disable_peripheral_clock(ID_TWI0);
	}
	else if(twiPeripheral == TWI1)
	{
		sysclk_disable_peripheral_clock(ID_TWI1);
	}
}

void TwoWire::setClock(uint32_t clock)
{
	twi_set_speed(twiPeripheral, clock, sysclk_get_main_hz());
}

//this is a read
uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity, uint32_t iaddress, uint8_t isize, uint8_t sendStop)
{	
	twi_packet_t packet;
	uint8_t tempBuffer[256];
	packet.chip = address;
	
	for(uint8_t i = 0; i < isize; i++)
	{
		packet.addr[i] = (iaddress >> (i*8));
	}
	packet.addr_length = isize;
	packet.length = quantity;
	packet.buffer = tempBuffer;
	if(twi_master_read(twiPeripheral, &packet) == TWI_SUCCESS)
	{
		for(uint8_t i = 0; i < quantity; i++)
		{
			rx_buffer_append(tempBuffer[i]);
		}
		return 0;
	}
	else
	{
		return -1;
	}
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity, uint8_t sendStop) {
	return requestFrom((uint8_t)address, (uint8_t)quantity, (uint32_t)0, (uint8_t)0, (uint8_t)sendStop);
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity)
{
	return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)true);
}

uint8_t TwoWire::requestFrom(int address, int quantity)
{
	return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)true);
}

uint8_t TwoWire::requestFrom(int address, int quantity, int sendStop)
{
	return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)sendStop);
}

void TwoWire::beginTransmission(uint8_t address)
{
	txAddress = address;
}

void TwoWire::beginTransmission(int address)
{
	beginTransmission((uint8_t)address);
}

//
//	Originally, 'endTransmission' was an f(void) function.
//	It has been modified to take one parameter indicating
//	whether or not a STOP should be performed on the bus.
//	Calling endTransmission(false) allows a sketch to
//	perform a repeated start.
//
//	WARNING: Nothing in the library keeps track of whether
//	the bus tenure has been properly ended with a STOP. It
//	is very possible to leave the bus in a hung state if
//	no call to endTransmission(true) is made. Some I2C
//	devices will behave oddly if they do not see a STOP.
//
uint8_t TwoWire::endTransmission(uint8_t sendStop)
{
	volatile uint32_t writeRes = 0;
	/*
	uint8_t stopSent = 0;
	//this actually starts the tx and sends all queued bytes
	if(tx_buffer_size < 2 && sendStop)
	{
		twiPeripheral->TWI_CR = TWI_CR_START | TWI_CR_STOP;
		stopSent = 1;
	}
	else
	{
		twiPeripheral->TWI_CR = TWI_CR_START;
	}
	while(tx_buffer_size > 0)
	{
		//send data
		uint8_t sendByte;
		tx_buffer_remove(&sendByte);
		twi_write_byte(twiPeripheral, sendByte);
		while(twiPeripheral->TWI_SR & TWI_SR_TXCOMP == 0); //wait for tx to complete
	}
	if(sendStop && !stopSent)
	{
		twiPeripheral->TWI_CR = TWI_CR_STOP;
		while (!(twiPeripheral->TWI_SR & TWI_SR_TXCOMP));
	}
	*/
	
	if(tx_buffer_size > 0)
	{
		twi_packet_t packet;
		uint8_t sendBuffer[32];
		packet.chip = txAddress;
		packet.addr_length = 0;
		packet.length = tx_buffer_size;
		packet.buffer = sendBuffer;
		for(uint8_t i = 0; i < packet.length; i++)
		{
			tx_buffer_remove(&sendBuffer[i]);
		}
		//if(twi_master_write(twiPeripheral, &packet) != TWI_SUCCESS)
		writeRes = twi_master_write(twiPeripheral, &packet);
		if(writeRes == TWI_SUCCESS)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	
	return 0;
}

//	This provides backwards compatibility with the original
//	definition, and expected behaviour, of endTransmission
//
uint8_t TwoWire::endTransmission(void)
{
	return endTransmission(true);
}

// must be called in:
// slave tx event callback
// or after beginTransmission(address)
size_t TwoWire::write(uint8_t data)
{
	tx_buffer_append(data); //add data to tx buffer

	//if(tx_buffer_size == 0 && twiPeripheral->TWI_SR & TWI_SR_TXRDY)
	//{
	//	twi_write_byte(twiPeripheral, data);
	//}
	//else
	//{
	//	while(tx_buffer_size == TWI_BUFFER_SIZE);  //wait for room to append
		
	//	twi_enable_interrupt(twiPeripheral, TWI_IER_ENDTX);  //enable tx complete interrupt
	//}
	return 1;
}

// must be called in:
// slave tx event callback
// or after beginTransmission(address)
size_t TwoWire::write(const uint8_t *data, size_t quantity)
{
	for(unsigned int i = 0; i < quantity; i++)
	{
		write(data[i]);
	}
	return quantity;
}

// must be called in:
// slave rx event callback
// or after requestFrom(address, numBytes)
int TwoWire::available(void)
{
	return rx_buffer_size;
}

// must be called in:
// slave rx event callback
// or after requestFrom(address, numBytes)
int TwoWire::read(void)
{
	uint8_t data;
	uint8_t status = rx_buffer_remove(&data);
	if(status <= 0)
	{
		return -1;
	}
	else
	{
		return data;
	}
}

// must be called in:
// slave rx event callback
// or after requestFrom(address, numBytes)
int TwoWire::peek(void)
{
	if (rx_buffer_size == 0)
	{
		return -1;
	}
	else
	{
		return (*rx_buffer_head);
	}
}

void TwoWire::flush(void)
{
	// XXX: to be implemented.
}

// behind the scenes function that is called when data is received
void TwoWire::onReceiveService(uint8_t* inBytes, int numBytes)
{
	// don't bother if user hasn't registered a callback
	if(!user_onReceive){
		return;
	}
	// don't bother if rx buffer is in use by a master requestFrom() op
	// i know this drops data, but it allows for slight stupidity
	// meaning, they may not have read all the master requestFrom() data yet
	if(rxBufferIndex < rxBufferLength){
		return;
	}
	// copy twi rx buffer into local read buffer
	// this enables new reads to happen in parallel
	for(uint8_t i = 0; i < numBytes; ++i){
		rxBuffer[i] = inBytes[i];
	}
	// set rx iterator vars
	rxBufferIndex = 0;
	rxBufferLength = numBytes;
	// alert user program
	user_onReceive(numBytes);
}

// behind the scenes function that is called when data is requested
void TwoWire::onRequestService(void)
{
	// don't bother if user hasn't registered a callback
	if(!user_onRequest){
		return;
	}
	// reset tx buffer iterator vars
	// !!! this will kill any pending pre-master sendTo() activity
	txBufferIndex = 0;
	txBufferLength = 0;
	// alert user program
	user_onRequest();
}

// sets function called on slave write
void TwoWire::onReceive( void (*function)(int) )
{
	user_onReceive = function;
}

// sets function called on slave read
void TwoWire::onRequest( void (*function)(void) )
{
	user_onRequest = function;
}

uint8_t TwoWire::rx_buffer_append(uint8_t data)
{
	if(rx_buffer_size < SERIAL_USART_RX_BUFFER_SIZE)
	{
		*rx_buffer_tail = data;
		
		if(rx_buffer_tail == rx_buffer_end)
		{
			rx_buffer_tail = rx_buffer;
		}
		else
		{
			rx_buffer_tail++;
		}
		cpu_irq_disable();
		rx_buffer_size++;
		cpu_irq_enable();
		return 1;
	}
	else
	{
		//else no room
		return 0;
	}
}
uint8_t TwoWire::rx_buffer_remove(uint8_t* data)
{
	if(rx_buffer_size > 0)
	{
		*data = *rx_buffer_head;
		
		if(rx_buffer_head == rx_buffer_end)
		{
			rx_buffer_head = rx_buffer;
		}
		else
		{
			rx_buffer_head++;
		}
		cpu_irq_disable();
		rx_buffer_size--;
		cpu_irq_enable();
		return 1;
	}
	else
	{
		//nothing to remove
		return 0;
	}
}

uint8_t TwoWire::tx_buffer_append(uint8_t data)
{
	if(tx_buffer_size < SERIAL_USART_RX_BUFFER_SIZE)
	{
		*tx_buffer_tail = data;
		if(tx_buffer_tail == tx_buffer_end)
		{
			tx_buffer_tail = tx_buffer;
		}
		else
		{
			tx_buffer_tail++;
		}
		cpu_irq_disable();
		tx_buffer_size++;
		cpu_irq_enable();
		return 1;
	}
	else
	{
		//else no room
		return 0;
	}
}
uint8_t TwoWire::tx_buffer_remove(uint8_t* data)
{
	if(tx_buffer_size > 0)
	{
		*data = *tx_buffer_head;
		
		if(tx_buffer_head == tx_buffer_end)
		{
			tx_buffer_head = tx_buffer;
		}
		else
		{
			tx_buffer_head++;
		}
		cpu_irq_disable();
		tx_buffer_size--;
		cpu_irq_enable();
		return 1;
	}
	else
	{
		//nothing to remove
		return 0;
	}
}

void TwoWire::tx_ready_callback(void)
{
	if(tx_buffer_size == 0)
	{
		twi_disable_interrupt(twiPeripheral, TWI_IER_ENDTX);
		return;
	}
	else
	{
		uint8_t data;
		tx_buffer_remove(&data);
		twi_write_byte(twiPeripheral, data);
	}
}

void TwoWire::rx_ready_callback(void)
{
	uint8_t data = twi_read_byte(twiPeripheral);
	rx_buffer_append(data);
}

TwoWire Wire = TwoWire(TWI0);
TwoWire Wire2 = TwoWire(TWI1);

//Interrupt handlers for the TWI modules
void TWI0_Handler()
{
	volatile uint32_t status = twi_get_interrupt_status(TWI0) & twi_get_interrupt_mask(TWI0);
	if(status & TWI_IER_RXRDY)
	{
		Wire.rx_ready_callback();
	}
	
	if(status & TWI_IER_ENDTX)
	{
		Wire.tx_ready_callback();
	}
}

