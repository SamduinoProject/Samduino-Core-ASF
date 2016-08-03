/**
 * \file HardwareSerialUart.h
 *
 * \brief UART peripheral library for SAMBO platforms
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

#ifndef HardwareSerial_h
#define HardwareSerial_h

#include <asf.h>

#include "Stream.h"

/** \brief The RX buffer size in bytes **/
#define SERIAL_RX_BUFFER_SIZE		255

/** \brief the TX bufer size in bytes **/
#define SERIAL_TX_BUFFER_SIZE		255

#ifdef __cplusplus

/** \brief Class to encapsulate the UART Serial Peripherals **/
class HardwareSerialUart : public Stream
{
	public:
		/********************************************//**
		\brief Constructor for the Uart Hardware Serial Module.  This is not
		meant to be called by the user, but is used to statically constructed
		for each peripheral.
		@param[in]	peripheral_pointer		pointer to the base address of
											the hardware peripheral regs
		@return								none (constructor).
		***********************************************/
		HardwareSerialUart(Uart* periperhal_pointer);
		
		/********************************************//**
		\brief Start the serial connection
		@param[in]	baud	the baud rate of the serial connection
		@return				void
		***********************************************/
		void begin(unsigned long baud);
		
		/********************************************//**
		\brief Open the serial connection
		@param[in]	baud	the baud rate of the serial connection
		@return				void
		***********************************************/
		void begin(unsigned long, uint8_t);
				
		/********************************************//**
		\brief Close the serial connection
		@return				void
		***********************************************/
		void end();
		
		/********************************************//**
		\brief Get the number of bytes available in this serial's buffer
		@return				the number of bytes available
		***********************************************/
		virtual int available(void);
		
		/********************************************//**
		\brief Get the next byte in the	rx queue without removing it
		@return				the next byte available in the rx buffer
		***********************************************/
		virtual int peek(void);
		
		/********************************************//**
		\brief Get the next byte in the rx queue and remove it from the buffer
		@return				the next byte available in the rx buffer
		***********************************************/
		virtual int read(void);
		
		/********************************************//**
		\brief Get the number of free bytes in the tx buffer that are
		available for write
		@return				the number of free bytes in the tx buffer
		***********************************************/
		int availableForWrite(void);
		
		/********************************************//**
		\brief Flush the rx and tx buffers
		@return				void
		***********************************************/
		virtual void flush(void);
		
		/********************************************//**
		\brief Write a byte to the serial tx buffer to be transmitted
		@return				the number of bytes written
		***********************************************/
		virtual size_t write(uint8_t data);
		
		/********************************************//**
		\brief Write a byte to the serial tx buffer to be transmitted.  Only
		writes the lower byte of the data passed in.
		@return				the number of bytes written
		***********************************************/
		inline size_t write(unsigned long n) { return write((uint8_t)n); }
			
		/********************************************//**
		\brief Write a byte to the serial tx buffer to be transmitted.  Only
		writes the lower byte of the data passed in.
		@return				the number of bytes written
		***********************************************/
		inline size_t write(long n) { return write((uint8_t)n); }
			
		/********************************************//**
		\brief Write a byte to the serial tx buffer to be transmitted.  Only
		writes the lower byte of the data passed in.
		@return				the number of bytes written
		***********************************************/
		inline size_t write(unsigned int n) { return write((uint8_t)n); }
			
		/********************************************//**
		\brief Write a byte to the serial tx buffer to be transmitted.  Only
		writes the lower byte of the data passed in.
		@return				the number of bytes written
		***********************************************/
		inline size_t write(int n) { return write((uint8_t)n); }
			
		using Print::write; // pull in write(str) and write(buf, size) from Print
		operator bool() { return true; }

		/********************************************//**
		\brief Callback function meant to be called by the serial peripheral's
		interrupt service routine when the peripheral's tx register is empty
		and can accept more data.
		@return				void
		***********************************************/
		void tx_empty_callback(void);
		
		/********************************************//**
		\brief Callback function meant to be called by the serial peripheral's
		interrupt service routine when the peripheral's rx data buffer is full
		so that the data can be added to the software buffer to make room for
		more data in the hardware buffer.
		@return				void
		***********************************************/
		void rx_ready_callback(void);

	protected:
		/** \brief The rx buffer **/
		uint8_t rx_buffer[SERIAL_RX_BUFFER_SIZE];
		
		/** \brief Pointer to the end of the rx buffer **/
		uint8_t* rx_buffer_end;
		
		/** \brief Pointer to the head of the data in the rx buffer
		The head is where the next read will come from **/
		volatile uint8_t* rx_buffer_head;
		
		/** \brief Pointer to the tail of the data in the rx buffer
		The tail is where the next write will place its data **/
		uint8_t* rx_buffer_tail;
		
		/** \brief The number of bytes in the rx buffer **/
		volatile uint8_t rx_buffer_size;
		
		/********************************************//**
		\brief Append a byte to the rx buffer.
		@param[in]	data	the data to be appended to the rx buffer
		@return				the number of bytes written
		***********************************************/
		uint8_t rx_buffer_append(uint8_t data);
		
		/********************************************//**
		\brief Remove a byte from the rx buffer.
		@param[in]	data	pointer to fill with data from the rx buffer
		@return				the number of bytes written
		***********************************************/
		uint8_t rx_buffer_remove(uint8_t* data);

		/** \brief The tx buffer **/
		uint8_t tx_buffer[SERIAL_TX_BUFFER_SIZE];
		
		/** \brief Pointer to the end of the tx buffer **/
		uint8_t* tx_buffer_end;
		
		/** \brief Pointer to the head of the data in the rx buffer
		The head is where the next read will come from **/
		volatile uint8_t* tx_buffer_head;
		
		/** \brief Pointer to the tail of the data in the rx buffer
		The tail is where the next write will place its data **/
		volatile uint8_t* tx_buffer_tail;
		
		/** \brief Holds the number of bytes in the tx buffer **/
		volatile uint8_t tx_buffer_size;
	
		/********************************************//**
		\brief Append a byte to the tx buffer.
		@param[in]	data	the data to be appended to the tx buffer
		@return				the number of bytes written
		***********************************************/
		uint8_t tx_buffer_append(uint8_t data);
		
		/********************************************//**
		\brief Append a byte to the tx buffer.
		@param[in]	data	pointer to fill with data from the tx buffer
		@return				the number of bytes written
		***********************************************/
		uint8_t tx_buffer_remove(uint8_t* data);
		
		/** \brief Pointer to the base of the hardware peripheral that this
		class is encapsulating **/
		Uart* uart_peripheral;
};

/** \brief The extern definition of the serial module Serial3 which
encapsulates UART0 **/
extern HardwareSerialUart Serial3;

/** \brief The extern definition of the serial module Serial4 which
encapsulates UART1 **/
extern HardwareSerialUart Serial4;

//TODO: figure out what to do with this....??
extern void serialEventRun(void) __attribute__((weak));

#endif //__cplusplus

#endif
