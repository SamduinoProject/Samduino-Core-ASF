/*
 * ArduinoSpi.cpp
 *
 * Created: 6/26/2016 12:16:14 PM
 *  Author: Nate
 */ 


#include "HardwareSpi.h"

#define SPI_PTR ((Spi    *)0x40008000U)

void HardwareSpi::begin()
{
	//configure spi pins
	pio_configure(PIOA, PIO_PERIPH_A, (PIO_PA14A_SPCK | PIO_PA13A_MOSI | PIO_PA12A_MISO), PIO_DEFAULT);
	sysclk_enable_peripheral_clock(ID_SPI);
	
	spi_reset(SPI_PTR);
	spi_set_master_mode(SPI_PTR);
	spi_disable_mode_fault_detect(SPI_PTR);
	spi_disable_loopback(SPI_PTR);
	//spi_set_peripheral_chip_select_value(spi, spi_get_pcs(0));  //sets the chip select value
	spi_disable_peripheral_select_decode(SPI_PTR);
	
	spi_set_bits_per_transfer(SPI_PTR, 0, SPI_CSR_BITS_8_BIT);
	spi_set_baudrate_div(SPI_PTR, 0, spi_calc_baudrate_div(10000000, sysclk_get_cpu_hz()));
	spi_configure_cs_behavior(SPI_PTR, 0, SPI_CS_KEEP_LOW);
	spi_set_clock_polarity(SPI_PTR, 0, 0);
	spi_set_clock_phase(SPI_PTR, 0, 1);
	
	spi_enable(SPI_PTR);
}

void HardwareSpi::end()
{
	spi_disable(SPI_PTR);
}

uint8_t HardwareSpi::transfer(uint8_t data)
{
	spi_write(SPI_PTR, data, 0, 0);
	uint16_t readData;
	uint8_t cs;
	return spi_read(SPI_PTR, &readData, &cs);
	return readData & 0xff;
}

uint16_t HardwareSpi::transfer(uint16_t data)
{
	spi_write(SPI_PTR, data, 0, 0);
	uint16_t readDataH = 0;
	uint16_t readDataL = 0;
	uint8_t cs = 0;
	
	//read/write msb first
	spi_write(SPI_PTR, (data >> 8), 0, 0);
	spi_read(SPI_PTR, &readDataH, &cs);
	spi_write(SPI_PTR, (data & 0xff), 0, 0);
	spi_read(SPI_PTR, &readDataL, &cs);

	//combine read data high and low
	readDataH = ((readDataH << 8) | (readDataL & 0xff));

	return readDataH;
}

void HardwareSpi::transfer(void* buf, size_t count)
{
	transfer((uint8_t*)buf, (uint8_t*)buf, count);
}

int HardwareSpi::transfer(uint8_t* txBuffer, uint8_t* rxBuffer, uint16_t bufferLength)
{
	for(int i = 0; i < bufferLength; i++)
	{
		rxBuffer[i] = transfer(txBuffer[i]);
	}
	return 0;
}

void HardwareSpi::setBitOrder(uint8_t bitOrder)
{
	
}

HardwareSpi SPI;