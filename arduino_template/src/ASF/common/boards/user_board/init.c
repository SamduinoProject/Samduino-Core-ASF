/**
 * \file
 *
 * \brief User board initialization template
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <asf.h>
#include <board.h>
#include <conf_board.h>

#include "arduino_core/internal_timer.h"


#define DACC_ANALOG_CONTROL (DACC_ACR_IBCTLCH0(0x02) \
| DACC_ACR_IBCTLCH1(0x02) \
| DACC_ACR_IBCTLDACCORE(0x01))


void board_init(void)
{
	/* This function is meant to contain board-specific initialization code
	 * for, e.g., the I/O pins. The initialization can rely on application-
	 * specific board configuration, found in conf_board.h.
	 */
	WDT->WDT_MR = WDT_MR_WDDIS;  //disable watchdog timer
	
	//the following determines if pins are used for JTAG or for IO
	//if we are debugging, do nothing as they reset to JTAG mode
	//However, if bootloading, they need to be set (1) so they can be use as GPIO
	#ifdef BOOTLOADING
	MATRIX->CCFG_SYSIO = (CCFG_SYSIO_SYSIO7 | CCFG_SYSIO_SYSIO6 | CCFG_SYSIO_SYSIO5 | CCFG_SYSIO_SYSIO4);
	#endif
	
	// Configure HSMCI pins for SD Card
	gpio_configure_pin(PIN_HSMCI_MCCDA_GPIO, PIN_HSMCI_MCCDA_FLAGS);
	gpio_configure_pin(PIN_HSMCI_MCCK_GPIO, PIN_HSMCI_MCCK_FLAGS);
	gpio_configure_pin(PIN_HSMCI_MCDA0_GPIO, PIN_HSMCI_MCDA0_FLAGS);
	gpio_configure_pin(PIN_HSMCI_MCDA1_GPIO, PIN_HSMCI_MCDA1_FLAGS);
	gpio_configure_pin(PIN_HSMCI_MCDA2_GPIO, PIN_HSMCI_MCDA2_FLAGS);
	gpio_configure_pin(PIN_HSMCI_MCDA3_GPIO, PIN_HSMCI_MCDA3_FLAGS);
	/* Configure SD/MMC card detect pin */
	gpio_configure_pin(SD_MMC_0_CD_GPIO, SD_MMC_0_CD_FLAGS);
	
	//enable clocks to the PIO controllers so we can generate interrupts
	sysclk_enable_peripheral_clock(ID_PIOA);
	sysclk_enable_peripheral_clock(ID_PIOB);
	NVIC_EnableIRQ(PIOA_IRQn);
	NVIC_EnableIRQ(PIOB_IRQn);
	//pio_enable_interrupt(PIOA, 0xffffffff);
	//pio_enable_interrupt(PIOB, 0xffffffff);
	
	//init and start up the adc
	sysclk_enable_peripheral_clock(ID_ADC);
	adc_init(ADC, sysclk_get_main_hz(), sysclk_get_main_hz() / 32, 1024);
	adc_configure_timing(ADC, 0, ADC_SETTLING_TIME_3, 1);
	adc_set_resolution(ADC, ADC_MR_LOWRES_BITS_12);
	//adc_enable_channel(ADC, ADC_CHANNEL_3);
	NVIC_EnableIRQ(ADC_IRQn);
	//adc_start(ADC);

	//configure timer counter to create milliseconds counter for Arduino
	//delay/millis functions
	//internal_timer_configure(1000);
	start_microseconds_counter();
	
	//configure the DAC
	sysclk_enable_peripheral_clock(ID_DACC);
	dacc_reset(DACC);
	dacc_set_transfer_mode(DACC, 0); //half word mode?
	dacc_set_timing(DACC, 0x1, 0, 0xff);
	//dacc_enable_channel(DACC, 0); //enable channel 0
	//dacc_enable_channel(DACC, 1);
	dacc_set_analog_control(DACC, DACC_ANALOG_CONTROL);
	
	//start the usb stack regardless so that resets over dtr are detected
	udc_start();
	
}
