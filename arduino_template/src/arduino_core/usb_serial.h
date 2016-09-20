/* 
* usb_serial.h
*
* Created: 3/11/2016 9:20:37 AM
* Author: Nate
*/


#ifndef __USB_SERIAL_H__
#define __USB_SERIAL_H__

#include <asf.h>

#include "Stream.h"

#ifdef __cplusplus

/********************************************//**
\brief Called by the usb stack every time the USB Serial receives a byte.
The usb stack provides a place to call this function.  
See config/conf_usb.h UDI_CDC_RX_NOTIFY to change this function
@param[in]	port	the port the data was received on 
@return				void.
***********************************************/
extern "C" void usb_serial_rx_notify(uint8_t port);

extern "C" void usb_serial_tx_empty_notify(uint8_t port);

/********************************************//**
\brief Size in bytes of the USB Serial RX buffer
***********************************************/
#define USB_SERIAL_BUFFER_SIZE			512

/********************************************//**
\brief Class to encapsulate the USB Serial device
***********************************************/
class usb_serial : public Stream
{
//variables
public:
	usb_serial();
	~usb_serial();

	operator bool();
	
	/********************************************//**
	\brief Open USB Serial connection.
	@param[in]	baud		this parameter is here to compatible with
							Arduino but has no effect.
	@return					void.
	***********************************************/
	void begin(unsigned long baud);
	
	/********************************************//**
	\brief Close the USB Serial connection.
	@return					void.
	***********************************************/
	void end(void);
	
	/********************************************//**
	\brief Get the number of bytes available in the USB Serial RX buffer
	@return					void.
	***********************************************/
	virtual int available(void);
	
	/********************************************//**
	\brief Read one byte from the USB Serial RX buffer.  This removes
	the byte from the buffer.
	@return					the byte read out of the RX buffer
	***********************************************/
	virtual int read(void);
	
	/********************************************//**
	\brief Peek at the next byte in the USB Serial RX buffer.  This does
	not remove the byte from the buffer.
	@return					the next byte in the Serial RX buffer.
	***********************************************/
	virtual int peek(void);
	
	/********************************************//**
	\brief Flush all data out of the USB Serial buffers.
	@return					void
	***********************************************/
	virtual void flush(void);
	
	/********************************************//**
	\brief Write a byte to the USB Serial.
	@param[in]	data		the data to write to the USB Serial.
	@return					the number of bytes written
	***********************************************/
	virtual size_t write(uint8_t data);
	
	/********************************************//**
	\brief Write a buffer to the USB Serial.
	@param[in]	data		the data buffer to write to the USB Serial.
	@param[in]	bufferLength	the length of the buffer to write
	@return					the number of bytes written
	***********************************************/
	virtual size_t write(const uint8_t* buffer, size_t bufferLength);
	
	/********************************************//**
	\brief Write a byte to the USB Serial.  Writes only the least significant
	byte of the data passed in
	@param[in]	data		the data to write to the USB Serial.
	@return					the number of bytes written
	***********************************************/
	size_t write(unsigned long data);
	
	/********************************************//**
	\brief Write a byte to the USB Serial.  Writes only the least significant
	byte of the data passed in
	@param[in]	data		the data to write to the USB Serial.
	@return					the number of bytes written
	***********************************************/
	size_t write(long data);
	
	/********************************************//**
	\brief Write a byte to the USB Serial.  Writes only the least significant
	byte of the data passed in
	@param[in]	data		the data to write to the USB Serial.
	@return					the number of bytes written
	***********************************************/
	size_t write(unsigned int data);
	
	/********************************************//**
	\brief Write a byte to the USB Serial.  Writes only the least significant
	byte of the data passed in
	@param[in]	data		the data to write to the USB Serial.
	@return					the number of bytes written
	***********************************************/
	size_t write(int data);
	
	using Print::write; // pull in write(str) and write(buf, size) from Print
	
	/********************************************//**
	\brief USB Serial RX callback function.  This function should be called
	every time data is received on the USB Serial line so that the data
	is added to the RX buffer correctly.  The usb stack provides a place to
	call a notify function on rx and this function is indirectly called by
	that function.  See usb_serial_rx_notify at the top of this file for
	the wrapper function that calls this function.
	@return					void
	***********************************************/
	void rx_callback(void);
	
	void tx_empty_callback(void);
	
private:
	/********************************************//**
	\brief Removes a byte from the rx buffer.
	@param[out]	data		pointer to fill with data from the rx buffer
	@return					1 if a byte was removed, 0 otherwise
	***********************************************/
	uint8_t rx_buffer_dequeue(uint8_t* data);
	
	/********************************************//**
	\brief Adds a byte to the rx buffer.
	@param[out]	data		byte to add to the rx buffer
	@return					1 if a byte was added, 0 otherwise
	***********************************************/
	uint8_t rx_buffer_enqueue(uint8_t data);
	
	/** \brief the rx buffer **/
	uint8_t rx_buffer[USB_SERIAL_BUFFER_SIZE];
	
	/** \brief pointer to the end of the rx buffer **/
	uint8_t* rx_buffer_end;
	
	/** \brief pointer to the current head of the rx buffer, next byte out **/
	uint8_t* rx_buffer_head;
	
	/** \brief pointer to the current tail of the rx buffer, next spot to fill **/
	uint8_t* rx_buffer_tail;
	
	/** \brief counter to keep track of the size of the rx buffer for convenience **/
	uint16_t rx_buffer_size;
	
	//tx buffer stuff
	volatile uint8_t tx_buffer[USB_SERIAL_BUFFER_SIZE];
	volatile uint8_t* tx_buffer_end;
	volatile uint8_t* tx_buffer_head;
	volatile uint8_t* tx_buffer_tail;
	volatile uint16_t tx_buffer_size;
	
	uint8_t tx_buffer_append(uint8_t data);
	uint8_t tx_buffer_remove(uint8_t* data);
	
	bool transmitting;
	
}; //usb_serial


extern usb_serial Serial;  /** extern declaration of Serial module **/
//usb_serial Serial;

#endif //__cplusplus

#endif //__USB_SERIAL_H__