/**
 * \file peripherals.h
 *
 * \brief Header file to consolidate includes of peripheral
 * encapsulation classes and their instances
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


#ifndef PERIPHERALS_H_
#define PERIPHERALS_H_

#include "arduino_code.h"

#include "arduino_core/usb_serial.h"

extern usb_serial Serial;

#include "arduino_core/HardwareSerialUsart.h"
extern HardwareSerialUsart Serial1;
extern HardwareSerialUsart Serial2;

#include "arduino_core/HardwareSerialUart.h"
extern HardwareSerialUart Serial3;
extern HardwareSerialUart Serial4;

#include "arduino_core/Wire.h"
extern TwoWire Wire;
extern TwoWire Wire2;

//#include "arduino_core/pins_sam4s8b.h"
#include "arduino_core/PinIO.h"
//grab the pins
#include "pins_sam4s8b.h"
#include "Arduino.h"

//not sure this is the best way to accomplish this, but because atmel defines
//their SPI peripheral pointer as SPI, we have to undef it to allow for the
//typical Arduino usage.
#undef SPI

//create arduion spi
#include "HardwareSpi.h"
extern HardwareSpi SPI;

//create the flash module
#include "FlashMemory.h"
extern FlashMemory Flash;

//create the sd card module
#include "SDCard.h"
extern SDCardModule SDCard;

//create the real time clock module
#include "RealTimeClock.h"
extern RealTimeClock RealTime;

#endif /* PERIPHERALS_H_ */