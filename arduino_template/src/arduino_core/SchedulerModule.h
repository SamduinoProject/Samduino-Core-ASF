/*
 * Scheduler.h
 *
 * Created: 7/16/2016 12:24:06 PM
 *  Author: Nate
 */ 


#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <asf.h>

#define MAX_EVENTS 20
#define NUM_PRIORITIES 2

#define SCHEDULER_HIGH_PRIORITY 0
#define SCHEDULER_LOW_PRIORITY 1

#ifdef __cplusplus

struct SchedulerEvent
{
	uint8_t isActive;
	void (*eventFunctionPtr)(void*);
	void* eventArg;
	uint32_t interval;
	uint32_t runsRemaining;	
	uint32_t elapsedAt;
	uint8_t elapsed;
};

enum SchedulerTimeUnits
{
	SCHEDULER_1MS,
	SCHEDULER_10US	
};

class SchedulerModule
{
public:
	SchedulerModule(SchedulerTimeUnits units);
	int reset();
	int disable();
	int enable();
	//2D array of scheduled events where each array is a different priority level (0 highest N-1 lowest)
	int schedule(void(*functionPtr)(void*), void* arg, uint32_t intervalMs, uint32_t numRuns, uint8_t priority);
	int schedule(void(*functionPtr)(), uint32_t intervalMs, uint32_t numRuns, uint8_t priority);
	
	int handleEvents(int priorityLevel);
	int handleAllEvents();
	
private:
	SchedulerEvent eventArray[NUM_PRIORITIES][(MAX_EVENTS/NUM_PRIORITIES)] ;
	int numEvents[NUM_PRIORITIES];
	uint8_t enabled;
	SchedulerTimeUnits timeUnits;
};


extern SchedulerModule SchedulerMillis;
extern SchedulerModule SchedulerMicros;

#endif //__cplusplus

#endif /* SCHEDULER_H_ */