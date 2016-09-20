/* 
* usb_serial.cpp
*
* Created: 3/11/2016 9:20:37 AM
* Author: Nate
*/


#include "usb_serial.h"

usb_serial Serial;

// default constructor
usb_serial::usb_serial()
{
	rx_buffer_end = &rx_buffer[USB_SERIAL_BUFFER_SIZE - 1];
	rx_buffer_head = rx_buffer;
	rx_buffer_tail = rx_buffer;
	rx_buffer_size = 0;
	
	tx_buffer_end = &tx_buffer[USB_SERIAL_BUFFER_SIZE - 1];
	tx_buffer_head = tx_buffer;
	tx_buffer_tail = tx_buffer;
	tx_buffer_size = 0;
	transmitting = false;
} //usb_serial

// default destructor
usb_serial::~usb_serial()
{
} //~usb_serial

usb_serial::operator bool()
{
	return true;
}

void usb_serial::begin(unsigned long baud)
{
	//udc_stop();
	//udc_start();
	//stdio_usb_init();
}

void usb_serial::end(void)
{
	//stdio_usb_disable();
	udc_stop();
}

int usb_serial::available(void)
{
	return rx_buffer_size;
}

int usb_serial::read(void)
{
	//return udi_cdc_getc();
	uint8_t data = 0;
	if(rx_buffer_size > 0)
	{
		rx_buffer_dequeue(&data);
		return data;
	}
	else
	{
		if(udi_cdc_is_rx_ready())
		{
			return udi_cdc_getc();
		}
		else
		{
			return -1;
		}
	}
}

int usb_serial::peek(void)
{
	return (*rx_buffer_head);
}

void usb_serial::flush(void)
{
	//TODO: actually clear the buffers
}

size_t usb_serial::write(uint8_t data)
{
	//current code
	/*
	if(udi_cdc_is_tx_ready())
	{
		return udi_cdc_putc(data & 0xff);
	}
	return 0;
	*/
	
	
	
	//else
	//{
	//	udi_cdc_signal_overrun();
	//	return 0;	
	//}
	//}
	//else
	//{
	//	return 0;
	//}
	
	//cpu_irq_disable();
	int temp_tx_buf_size = tx_buffer_size;
	//cpu_irq_enable();
	if(temp_tx_buf_size == 0)//!transmitting)
	{
		//transmitting = true;
		udi_cdc_putc(data);
		return 1;
	}
	else
	{
		transmitting = true;
		return tx_buffer_append(data);
	}
	
}

size_t usb_serial::write(const uint8_t* buffer, size_t bufferLength)
{
	
	//cpu_irq_disable();
	int temp_tx_buf_size = tx_buffer_size;
	//cpu_irq_enable();
	if(USB_SERIAL_BUFFER_SIZE - temp_tx_buf_size < bufferLength)
	{
		return 0;
	}
	
	
	int bytesSent = 0;
	for(size_t i = 0; i < bufferLength; i++)
	{
		//bytesSent += udi_cdc_putc(buffer[bytesSent]);
		//while(udi_cdc_is_tx_ready() == 0); //wait for tx to be ready to send
		//bytesSent += udi_cdc_putc(buffer[bytesSent]);
		bytesSent += write((uint8_t)(buffer[i] & 0xff));
	}
	return bytesSent;
}

size_t usb_serial::write(unsigned long data)
{
	return write((uint8_t)(data & 0xff));
}

size_t usb_serial::write(long data)
{
	return write((uint8_t)(data & 0xff));
}

size_t usb_serial::write(unsigned int data)
{
	return write((uint8_t)(data & 0xff));
}

size_t usb_serial::write(int data)
{
	return write((uint8_t)(data & 0xff));
}

uint8_t usb_serial::rx_buffer_enqueue(uint8_t data)
{
	if(rx_buffer_size < USB_SERIAL_BUFFER_SIZE)
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
		return 0;  //indicate the buffer was full
	}
}

uint8_t usb_serial::rx_buffer_dequeue(uint8_t* data)
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
		return 0;//indicate the buffer was empty
	}
}

uint8_t usb_serial::tx_buffer_append(uint8_t data)
{
	if(tx_buffer_size < USB_SERIAL_BUFFER_SIZE)
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
uint8_t usb_serial::tx_buffer_remove(uint8_t* data)
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

void usb_serial::rx_callback(void)
{
	//need to loop here because back to back RX may not generate multiple rx calls
	//so loop to eat all data for each call to ensure we catch all data
	
	uint8_t res = 1;
	uint16_t counter = 0;
	while(udi_cdc_is_rx_ready() && rx_buffer_size < USB_SERIAL_BUFFER_SIZE && counter < 32)
	{
		//Serial2.write(udi_cdc_getc());
		res = rx_buffer_enqueue(udi_cdc_getc());
	}
	
	/*
	uint8_t tempBuf[256];
	uint16_t avail = udi_cdc_get_nb_received_data();
	uint16_t rcvCount = udi_cdc_read_buf(tempBuf, 256);
	for(int i = 0; i < rcvCount; i++)
	{
		rx_buffer_enqueue(tempBuf[i]);
	}
	*/
}

void usb_serial_rx_notify(uint8_t port)
{
	//if(port == 0)
	{
		Serial.rx_callback();
	}
}

void usb_serial::tx_empty_callback()
{
	uint8_t data;
	
	uint8_t res = tx_buffer_remove(&data);
	
	if(res)
	{
		udi_cdc_putc(data);
	}
	else
	{
		transmitting = false;
	}
}

void usb_serial_tx_empty_notify(uint8_t port)
{
	Serial.tx_empty_callback();
}