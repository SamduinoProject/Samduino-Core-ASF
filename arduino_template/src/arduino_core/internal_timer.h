/*
 * internal_timer.h
 *
 * Created: 3/21/2016 8:39:57 AM
 *  Author: Nate
 */ 


#ifndef INTERNAL_TIMER_H_
#define INTERNAL_TIMER_H_

#include <asf.h>
#include <limits.h>

//reserve TC0 Channel 0 for internal timer/counter to make milliseconds
#define INTERNAL_TIMER				TC0
#define INTERNAL_TIMER_CHANNEL		0

#ifdef __cplusplus
extern "C" {
#endif

//configure timer counter to interrupt at hertz rate
void internal_timer_configure(uint32_t hertz);

void start_microseconds_counter(void);

void delay(uint32_t ms_delay);
unsigned long millis(void);

#ifdef __cplusplus
}
#endif

#endif /* INTERNAL_TIMER_H_ */