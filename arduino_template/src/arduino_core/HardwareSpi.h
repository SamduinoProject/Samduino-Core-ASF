/*
 * ArduinoSpi.h
 *
 * Created: 6/26/2016 12:15:59 PM
 *  Author: Nate
 */ 


#ifndef ARDUINOSPI_H_
#define ARDUINOSPI_H_

#include <asf.h>
#include "Arduino.h"

//undef the spi from ASF
//#ifdef SPI
//#undef SPI
//#endif

class HardwareSpi
{
public:
	void begin();
	void end();
	
	uint8_t transfer(uint8_t data);
	uint16_t transfer(uint16_t data);
	void transfer(void* buf, size_t count);
	int transfer(uint8_t* txBuffer, uint8_t* rxBuffer, uint16_t bufferLength);

	//TODO: support this in software since sam4s has no LSB first order settings
	//Generally, LSB first is not used anymore with modern peripherals
	void setBitOrder(uint8_t bitOrder);
	//TODO: make this change the data mode to comply with arduino
	void setDataMode(uint8_t dataMode);
	//TODO: make this modify the spi peripheral clock register to comply with arduino
	void setClock(uint32_t clock);

	
};

extern HardwareSpi SPI;


#endif /* ARDUINOSPI_H_ */