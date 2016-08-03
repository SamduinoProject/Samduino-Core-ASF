/**
 * \file PinIO.cpp
 *
 * \brief PinIO library for digital and analog I/O on the pin level.
 * facilitates basic pin read/write functionality.
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

#include "PinIO.h"
#include "pins_sam4s8b.h"
#include "Arduino.h"

Pio* get_pio_ptr(uint8_t pin)
{
	if(pin < PIO_PB0_IDX)
	{
		return PIOA;
	}
	else
	{
		return PIOB;
	}
}

void pinMode(uint8_t pin, uint8_t mode)
{
	uint8_t internal_pin_index = GET_PIN_INDEX(pin);
	uint8_t internal_pin_shift = GET_PIN_SHIFT(pin);
	Pio* pio_ptr = get_pio_ptr(internal_pin_index);
	//volatile int pioAddr = (int) pio_ptr;
	pio_ptr->PIO_PER = (1<<internal_pin_shift);
	if(mode == INPUT)
	{
		pio_set_input(pio_ptr, (1<<internal_pin_shift), PIO_DEFAULT);
	}
	else if(mode == INPUT_PULLUP)
	{
		pio_set_input(pio_ptr, (1<<internal_pin_shift), PIO_PULLUP);
	}
	else if(mode == INPUT_PULLDOWN)
	{
		pio_set_input(pio_ptr, (1<<internal_pin_shift), PIO_DEFAULT);
		//ASF doesn't have built in support for setting pull down, so we do it manually here
		pio_pull_down(pio_ptr, (1<<internal_pin_shift), (1<<internal_pin_shift));
	}
	else if(mode == OUTPUT)
	{
		pio_set_output(pio_ptr, (1<<internal_pin_shift), LOW, DISABLE, ENABLE);
	}
}

int digitalRead(uint8_t pin)
{
	//make sure the pin is in range of I/O
	if(pin >= NUMBER_PINS)
	{
		return NOT_A_PIN;
	}
	
	return pio_get_pin_value(GET_PIN_INDEX(pin));
}


void digitalWrite(uint8_t pin, uint8_t state)
{
	uint8_t internal_pin_index = GET_PIN_INDEX(pin);
	uint8_t internal_pin_shift = GET_PIN_SHIFT(pin);
	Pio* pio_ptr = get_pio_ptr(internal_pin_index);
	
	if(state == HIGH)
	{
		pio_set(pio_ptr, (1<<internal_pin_shift));
	}
	else
	{
		pio_clear(pio_ptr, (1<<internal_pin_shift));
	}
}


int analogRead(uint8_t pin)
{
	//set this pin to connect to adc.  ADC is periph b for all adc pins
	Pio* pioPtr = get_pio_ptr(PINS[pin]);
	pio_configure(pioPtr, PIO_PERIPH_B, pin, PIO_DEFAULT);
	adc_channel_num_t adc_channel = ADC_CHANNEL_0;
	for(unsigned int i = 0; i < sizeof(ADC_PINS); i++)
	{
		if(pin == ADC_PINS[i])
		{
			adc_channel = ADC_CHANNEL_PINS[i];
			break;
		}
	}
	adc_enable_channel(ADC, adc_channel);
	//adc_enable_interrupt(ADC, ADC_IER_DRDY);
	adc_configure_trigger(ADC, ADC_TRIG_SW, 0);
	adc_start(ADC);
	//wait for the conversion to finish
	while((adc_get_status(ADC) & ADC_ISR_DRDY) == 0); 
	
	adc_disable_interrupt(ADC, ADC_IDR_DRDY);
	adc_disable_channel(ADC, adc_channel);
	int result = adc_get_latest_value(ADC);
	return result;
}

void analogWrite(uint8_t pin, int value)
{
	//check if it is one of the DACC pins
	if(pin == DAC0_PIN || pin == DAC1_PIN)
	{
		dacc_enable_channel(DACC, pin); //enable channel 0
		//dacc_enable_channel(DACC, 1);
		dacc_write_conversion_data(DACC, value);
	}
	//else check if it is a PWM capable pin
	
	//otherwise, nothing we can do
}

//PB13 = DAC0
//PB14 = DAC1
