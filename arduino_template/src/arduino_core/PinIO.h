/**
 * \file PinIO.h
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


#ifndef PINIO_H_
#define PINIO_H_

#include <asf.h>

#ifdef __cplusplus
extern "C" {
#endif

void pinMode(uint8_t pin, uint8_t mode);

/********************************************//**
\brief Read the state of a digital input
@param[in]	pin		the pin number to read
@return				the digital value read from the specified pin.
					will return NOT_A_PIN if pin is not in I/O.
***********************************************/
int digitalRead(uint8_t pin);

/********************************************//**
\brief Read the state of a digital input
@param[in]	pin		the pin number to write to
@param[in]  state	the state to write to the pin
@return				void
***********************************************/
void digitalWrite(uint8_t pin, uint8_t state);

/********************************************//**
\brief Read the state of a digital input
@param[in]	pin		the pin number to write to
@return				the analog value read from the ADC channel
***********************************************/
int analogRead(uint8_t pin);

void analogWrite(uint8_t pin, int value);

Pio* get_pio_ptr(uint8_t pin);

#ifdef __cplusplus
}
#endif

#endif /* PINIO_H_ */