/*
 * RealTimeClock.cpp
 *
 * Created: 8/15/2016 10:19:52 AM
 *  Author: Nate
 */ 

#include "RealTimeClock.h"

String dateTimeToString(DateTime* dateTime)
{
	String ret = "";
	ret += dateTime->month;
	ret += "/";
	ret += dateTime->day;
	ret += "/";
	ret += dateTime->year;
	ret += " - ";
	ret += dateTime->hour;
	ret += ":";
	ret += dateTime->minute;
	ret += ".";
	ret += dateTime->second;
	return ret;
}

RealTimeClock::RealTimeClock()
{
	
}

int RealTimeClock::init(void)
{
	//first we need to switch to the 32K external oscillator
	//Enable the External 32K oscillator 
	pmc_switch_sclk_to_32kxtal(PMC_OSC_XTAL);

	// Wait for 32K oscillator ready
	while (!pmc_osc_is_ready_32kxtal());
	
	//configure for 24 hour mode first
	rtc_set_hour_mode(RTC, 0);
	//calibrate if necessary, might not be necessary if using external oscillator at normal temperatures
	//first number is 0 if crystal is slow, 1 if fast
	//second is the correction factor
	//third is the granularity of the correction (see data sheet for equation)
	rtc_set_calibration(RTC, 1, 8, 0);
	//init the RTC module
	NVIC_EnableIRQ(RTC_IRQn);
	rtc_enable_interrupt(RTC, RTC_IER_SECEN); //enable secends alarm interrupt to track seconds
	return 0;
}

int RealTimeClock::setDateTime(DateTime* currentDateTime)
{
	//set the hours, minutes, seconds first
	if(rtc_set_time(RTC, currentDateTime->hour, currentDateTime->minute, currentDateTime->second))
	{
		return -1; //error
	}
	
	if(rtc_set_date(RTC, currentDateTime->year, currentDateTime->month, currentDateTime->day, currentDateTime->week))
	{
		return -1;
	}
	return 0;
}

DateTime RealTimeClock::getDateTime()
{
	DateTime currentDateTime;
	rtc_get_time(RTC, &currentDateTime.hour, &currentDateTime.minute, &currentDateTime.second);
	rtc_get_date(RTC, &currentDateTime.year, &currentDateTime.month, &currentDateTime.day, &currentDateTime.week);
	return currentDateTime;
}

int RealTimeClock::tickSecond()
{
	//handle second tick event
	
	return 0;
}

RealTimeClock RealTime = RealTimeClock();

//RTC interrupt handler
void RTC_Handler(void)
{
	uint32_t rtcStatus = rtc_get_status(RTC);
	if(rtcStatus & RTC_SR_SEC)
	{
		rtc_disable_interrupt(RTC, RTC_IDR_SECDIS);
		RealTime.tickSecond();
		rtc_clear_status(RTC, RTC_SCCR_SECCLR);
		rtc_enable_interrupt(RTC, RTC_IER_SECEN);
		
	}
}