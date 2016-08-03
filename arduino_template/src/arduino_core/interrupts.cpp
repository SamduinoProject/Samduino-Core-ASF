/**
 * \file interrupts.cpp
 *
 * \brief Hardware Interrupt Service Routines source.
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

#ifdef __cplusplus
//extern "C" {
//#endif

#include <asf.h>
#include "pins_sam4s8b.h"
#include "PinIO.h"
//#include "HardwareSerialUart.h"

#define NUM_USER_INTERRUPTS 64
void (*user_interrupts[NUM_USER_INTERRUPTS])();

uint8_t usb_dtr_prev_value = false;

void usb_dtr_changed(uint8_t port, uint8_t set)
{
	if(set == false && usb_dtr_prev_value == true)
	{
		rstc_start_software_reset(RSTC);
	}
	usb_dtr_prev_value = set;
}

extern HardwareSerialUsart Serial1;
extern HardwareSerialUsart Serial2;

extern HardwareSerialUart Serial3;
extern HardwareSerialUart Serial4;

void UART0_Handler()
{
	uint32_t uart_status = uart_get_status(UART0);
	if(uart_status & UART_SR_RXRDY)
	{
		Serial3.rx_ready_callback();
	}
	
	if(uart_status & UART_SR_TXEMPTY)
	{
		Serial3.tx_empty_callback();
	}
}

void UART1_Handler()
{
	uint32_t uart_status = uart_get_status(UART1);
	if(uart_status & UART_SR_RXRDY)
	{
		Serial4.rx_ready_callback();
	}
	
	if(uart_status & UART_SR_TXEMPTY)
	{
		Serial4.tx_empty_callback();
	}
}

void USART0_Handler()
{
	uint32_t usart_status = usart_get_status(USART0);
	if(usart_status & US_CSR_RXRDY)
	{
		Serial1.rx_ready_callback();
	}
	
	if(usart_status & US_CSR_TXRDY)
	{
		Serial1.tx_empty_callback();
	}
}

void USART1_Handler()
{
	uint32_t usart_status = usart_get_status(USART1);
	if(usart_status & US_CSR_RXRDY)
	{
		Serial2.rx_ready_callback();
	}
	
	if(usart_status & US_CSR_TXRDY)
	{
		Serial2.tx_empty_callback();
	}
}

//arduino modes are LOW, CHANGE, RISING, FALLING, HIGH
void attachInterrupt(uint8_t interrupt, void (*function)(void), int mode)
{
	if(interrupt < NUM_USER_INTERRUPTS)
	{
		uint32_t interrupt_attributes = PIO_IT_AIME;
		//change the mode into PIO correct mask
		if(mode == RISING)
		{
			interrupt_attributes |= PIO_IT_RISE_EDGE;
		}
		else if(mode == FALLING)
		{
			interrupt_attributes |= PIO_IT_FALL_EDGE;
		}
		else if(mode == LOW)
		{
			interrupt_attributes |= PIO_IT_LOW_LEVEL;
		}
		else if(mode == HIGH)
		{
			interrupt_attributes |= PIO_IT_HIGH_LEVEL;
		}
		else if(mode == CHANGE)
		{
			interrupt_attributes |= PIO_IT_EDGE;
		}
		//add the interrupt function pointer to array
		uint32_t internal_pin_index = GET_PIN_INDEX(interrupt);
		user_interrupts[internal_pin_index] = function;
		//now we need to configure the interrupt to fire in the pio
		Pio* pin_pio = get_pio_ptr(interrupt);
		uint32_t pin_shift = GET_PIN_SHIFT(interrupt);
		pio_enable_interrupt(pin_pio, (1<<pin_shift));
		pio_configure_interrupt(pin_pio, (1<<pin_shift), interrupt_attributes);
	}
}

void detachInterrupt(uint8_t interrupt)
{
	if(interrupt < NUM_USER_INTERRUPTS)
	{
		user_interrupts[interrupt] = NULL;
	}
}

void PIOA_Handler()
{
	//digitalWrite(19, HIGH);
	uint32_t status = pio_get_interrupt_status(PIOA);
	status &= pio_get_interrupt_mask(PIOA);
	for(int i = 0; i < 32; i++)
	{
		if((status >> i) & 0x01 && user_interrupts[i])
		{
			user_interrupts[i]();
		}
	}
}

void PIOB_Handler()
{
	//digitalWrite(19, HIGH);
	uint32_t status = pio_get_interrupt_status(PIOB);
	status &= pio_get_interrupt_mask(PIOB);
	for(int i = 0; i < 32; i++)
	{
		if((status >> i) & 0x01 && user_interrupts[i+32])
		{
			user_interrupts[i+32]();
		}
	}
}

//#ifdef __cplusplus
//}
#endif