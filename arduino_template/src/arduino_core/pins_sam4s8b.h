/*
 * pins_sam4s8b.h
 *
 * Created: 3/15/2016 12:50:45 PM
 *  Author: Nate
 */ 


#ifndef PINS_SAM4S8B_H_
#define PINS_SAM4S8B_H_

#include <asf.h>
//#include "arduino_core/Arduino.h"

#define PIOA_FIRST_PIN			0
#define PIOA_NUM_PINS			10
#define PIOB_FIRST_PIN			(PIOA_FIRST_PIN + PIOA_NUM_PINS)
#define PIOB_NUM_PINS			10

/*
//Analog to Digital Converter Pins
#define ADC0					PA17
#define ADC1					PA18
#define ADC2					PA19
#define ADC3					PA20
#define ADC4					PB0
#define ADC5					PB1
#define ADC6					PB2
#define ADC7					PB3
#define ADC8					PA21
#define ADC9					PA22

//these only available on packages with more pinsd
#define ADC10					PC13
#define ADC11					PC15
#define ADC12					PC12
#define ADC13					PC29
#define ADC14					PC30 

//Digital to Analog pins
#define DAC0					PB13
#define DAC1					PB14

#define NUMBER_PINS				3
//Digital I/O Pins
#define DIGITAL_IO_1			PA17
#define DIGITAL_IO_2			PA18
#define DIGITAL_IO_3			PA19

//abstraction layer for generic "pins"
#define PIN1					DIGITAL_IO_1
#define PIN2					DIGITAL_IO_2
#define PIN3					DIGITAL_IO_3
*/

/*
mapping of pins that maps the integer number (1, 2...etc) that arduino uses
to the PIOX_PXX that atmel uses internally.  Index of the pins array
is the arduino number, data at that index is the index of the pin
according to internal atmel definitions
*/ 
#define DAC0_PIN 0
#define DAC1_PIN 1

#define NUMBER_PINS	35
const uint8_t PINS[NUMBER_PINS] = {
	PIO_PB13_IDX, PIO_PB14_IDX, PIO_PB7_IDX, PIO_PB6_IDX , PIO_PA0_IDX, PIO_PA1_IDX, PIO_PA2_IDX,
	PIO_PB4_IDX, PIO_PB5_IDX, PIO_PA3_IDX, PIO_PA4_IDX, PIO_PA5_IDX, PIO_PA6_IDX, PIO_PA9_IDX,
	PIO_PA10_IDX, PIO_PA14_IDX, PIO_PA12_IDX, PIO_PA13_IDX, PIO_PA17_IDX, PIO_PA18_IDX, PIO_PA19_IDX,
	PIO_PA20_IDX, PIO_PB0_IDX, PIO_PB1_IDX, PIO_PB2_IDX, PIO_PB3_IDX, PIO_PA21_IDX, PIO_PA22_IDX,
	PIO_PA23_IDX, PIO_PA16_IDX, PIO_PA15_IDX, PIO_PA24_IDX, PIO_PA25_IDX, PIO_PA8_IDX, PIO_PA7_IDX
};

#define A0 PIO_PA17_IDX
#define A1 PIO_PA18_IDX
#define A2 PIO_PA19_IDX
#define A3 PIO_PA20_IDX
#define A4 PIO_PB0_IDX
#define A5 PIO_PB1_IDX
#define A6 PIO_PB2_IDX
#define A7 PIO_PB3_IDX
#define A8 PIO_PA21_IDX
#define A9 PIO_PA22_IDX

const uint8_t ADC_PINS[] = {
	A0,
	A1,
	A2,
	A3,
	A4,
	A5,
	A6,
	A7,
	A8,
	A9
};

const adc_channel_num_t ADC_CHANNEL_PINS[] = {
	ADC_CHANNEL_0,
	ADC_CHANNEL_1,
	ADC_CHANNEL_2,
	ADC_CHANNEL_3,
	ADC_CHANNEL_4,
	ADC_CHANNEL_5,
	ADC_CHANNEL_6,
	ADC_CHANNEL_7,
	ADC_CHANNEL_8,
	ADC_CHANNEL_9
};

#define NUMBER_ANALOG_PINS 10
const uint8_t ANALOG_PINS[NUMBER_ANALOG_PINS] = {
	A0, A1, A2, A3, A4, A5, A6, A7, A8, A9 
};
								   
#define GET_PIN_INDEX(pin) (PINS[pin])// % 32)
#define GET_PIN_SHIFT(pin) (PINS[pin] % 32)


//#ifdef __cplusplus
//extern "C" {
//#endif
//
//void pinMode(uint8_t pin, uint8_t mode);
//
//void digitalWrite(uint8_t pin, uint8_t state);
//
//#ifdef __cplusplus
//}
//#endif

#endif /* PINS_SAM4S8B_H_ */