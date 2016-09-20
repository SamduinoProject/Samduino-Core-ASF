/*
 * internal_timer.cpp
 *
 * Created: 3/21/2016 8:43:06 AM
 *  Author: Nate
 */ 


#include "internal_timer.h"
#include "SchedulerModule.h"

volatile uint64_t ms_counter = 0;
volatile uint64_t us_counter = 0;

/*
void internal_timer_configure(uint32_t hertz)
{
	uint32_t div;
	uint32_t tcclks;
	uint32_t sysclk = sysclk_get_cpu_hz();
	uint32_t counts;

	pmc_enable_periph_clk(ID_TC0);

	tc_find_mck_divisor(hertz, sysclk, &div, &tcclks, sysclk);

	tc_init(INTERNAL_TIMER, INTERNAL_TIMER_CHANNEL, tcclks | TC_CMR_CPCTRG);

	//find the number of timer counter counts to use to generate timer
	counts = (sysclk / div) / hertz;
	tc_write_rc(INTERNAL_TIMER, INTERNAL_TIMER_CHANNEL, counts);

	//reset our internal ms counter
	ms_counter = 0;

	//enable interrupts
	tc_enable_interrupt(INTERNAL_TIMER, INTERNAL_TIMER_CHANNEL, TC_IER_CPCS);
	NVIC_EnableIRQ(TC0_IRQn);
	tc_start(INTERNAL_TIMER, INTERNAL_TIMER_CHANNEL);

}
*/

/*
Starts a timer counter on a microsecond tick with an interrupt for each millisecond.  This is
important so that we can get 1us accuracy on counters and delays, but only interrupt once a millisecond
to update the millisecond counter.  Because the value in the timer register for this counter can be divided
by 60 to get microseconds and then the milliseconds counter multiplied by 1000 and added to the raw register
we can get both milliseconds and microseconds this way with minimal interrupt
*/
void start_microseconds_counter()
{
	//uint32_t div;
	uint32_t tcclks;
	//uint32_t sysclk = sysclk_get_cpu_hz();
	uint32_t counts;

	pmc_enable_periph_clk(ID_TC0);
	pmc_enable_periph_clk(ID_TC2);

	//get divisor for 1 micro second tick
	//tc_find_mck_divisor(100000000, sysclk, &div, &tcclks, sysclk);
	//the tcclks = timer counter clock select 0 is MCK/2 = 60MHz
	tcclks = 0;
	
	tc_init(INTERNAL_TIMER, INTERNAL_TIMER_CHANNEL, tcclks | TC_CMR_CPCTRG);

	//counts should be a thousand so microseconds overflow ticks up the millis counter
	//counts = (sysclk / div) / 100000000;
	//since tick rate is 60MHz and we want a us counter, counts needs to get us there
	//so counts * 1000 = 60MHz -> 60MHz/1000 = counts = 60000
	counts = 60000;
	tc_write_rc(INTERNAL_TIMER, INTERNAL_TIMER_CHANNEL, counts);

	//reset our internal ms counter
	ms_counter = 0;

	//enable interrupts
	
	tc_enable_interrupt(INTERNAL_TIMER, INTERNAL_TIMER_CHANNEL, TC_IER_CPCS);
	NVIC_EnableIRQ(TC0_IRQn);
	tc_start(INTERNAL_TIMER, INTERNAL_TIMER_CHANNEL);
	
	//setup the 10 us interrupt for high precision event handler but don't start till later when necessary
	tc_init(INTERNAL_TIMER, 2, tcclks | TC_CMR_CPCTRG);
	tc_write_rc(INTERNAL_TIMER, 2, counts/100);
	tc_enable_interrupt(INTERNAL_TIMER, 2, TC_IER_CPCS);
	NVIC_EnableIRQ(TC2_IRQn);
	//tc_start(INTERNAL_TIMER, 2); not starting here, letting scheduluer start
}

void delay(uint32_t ms_delay)
{
	//get current counter value
	uint64_t current_value = ms_counter;
	uint64_t wait_till_value = 0;

	wait_till_value = current_value + ms_delay;
	
	//wait till the value is hit as a "delay"
	while(ms_counter != wait_till_value);
	
}

void delayMicroseconds(unsigned int us)
{
	//get current counter value
	uint64_t current_value = micros();
	uint64_t wait_till_value = 0;

	wait_till_value = current_value + us;
	
	//wait till the value is hit as a "delay"
	while(micros() < wait_till_value);
}

uint64_t millis(void)
{
	return ms_counter;
}

uint64_t micros()
{
	//first get the microseconds counter ticks register value
	unsigned long microSeconds = (tc_read_rc(INTERNAL_TIMER, INTERNAL_TIMER_CHANNEL)/60);
	microSeconds += (millis() * 1000);
	return microSeconds;
}

void TC0_Handler()
{
	uint32_t status = tc_get_status(INTERNAL_TIMER, INTERNAL_TIMER_CHANNEL);
	
	//if the interrupt is on this
	if(status & TC_SR_CPCS)
	{
		ms_counter++;
		SchedulerMillis.handleEvents(SCHEDULER_HIGH_PRIORITY);
	}
}

void TC2_Handler()
{
	uint32_t status = tc_get_status(INTERNAL_TIMER, 2);
	
	//if the interrupt is on this
	if(status & TC_SR_CPCS)
	{
		us_counter++;
		SchedulerMicros.handleEvents(SCHEDULER_HIGH_PRIORITY);
	}
}