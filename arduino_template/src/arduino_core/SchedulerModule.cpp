/*
 * Scheduler.cpp
 *
 * Created: 7/16/2016 12:24:17 PM
 *  Author: Nate
 */ 

#include "SchedulerModule.h"

SchedulerModule::SchedulerModule(SchedulerTimeUnits units)
{
	//start from reset
	timeUnits = units;
	reset();
}

int SchedulerModule::reset()
{
	//make sure we aren't enabled until an event is added
	//so that no one tries to update us until it is needed
	disable();
	//make sure all events are marked as inactive and num events is 0 after reset
	for(int i = 0; i < NUM_PRIORITIES; i++)
	{
		for(int j = 0; j < (MAX_EVENTS/NUM_PRIORITIES); j++)
		{
			eventArray[i][j].isActive = 0;
		}
		numEvents[i] = 0;
	}
	return 0;
}

int SchedulerModule::disable()
{
	enabled = 0;
	return 0;
}

int SchedulerModule::enable()
{
	if(timeUnits == SCHEDULER_10US && numEvents[0] == 1)
	{
		tc_start(TC0, 2);
	}
	enabled = 1;
	return 0;
}

int SchedulerModule::schedule(void(*functionPtr)(void* arg), void* arg, uint32_t interval, uint32_t numRuns, uint8_t priority)
{
	if(priority >= NUM_PRIORITIES || functionPtr == NULL || interval == 0)
	{
		return -1;  //error in parameters
	}
	
	if(numEvents[priority] == (MAX_EVENTS/NUM_PRIORITIES))
	{
		return -2; //error no room to schedule at that priority
	}
	
	//setup the event in the correct priority
	SchedulerEvent* eventPtr = NULL;// = &eventArray[priority][numEvents[priority]];
	
	for(int i = 0; i < (MAX_EVENTS/NUM_PRIORITIES); i++)
	{
		if(eventArray[priority][i].isActive == false)
		{
			eventPtr = &eventArray[priority][i];
			break;
		}
	}
	
	eventPtr->eventFunctionPtr = functionPtr;
	eventPtr->eventArg = arg;
	eventPtr->interval = interval;
	eventPtr->runsRemaining = numRuns;
	eventPtr->elapsed = false;
	
	if(timeUnits == SCHEDULER_1MS)
	{
		eventPtr->elapsedAt = millis() + interval;
	}
	else
	{
		eventPtr->elapsedAt = micros() + interval;
	}
	
	numEvents[priority]++;
	eventPtr->isActive = true;
	enable();
	return 0;	
}

int SchedulerModule::schedule(void(*functionPtr)(), uint32_t interval, uint32_t numRuns, uint8_t priority)
{
	if(priority >= NUM_PRIORITIES || functionPtr == NULL || interval == 0)
	{
		return -1;  //error in parameters
	}
	
	if(numEvents[priority] == (MAX_EVENTS/NUM_PRIORITIES))
	{
		return -2; //error no room to schedule at that priority
	}
	
	//setup the event in the correct priority
	SchedulerEvent* eventPtr = NULL;// = &eventArray[priority][numEvents[priority]];
	
	for(int i = 0; i < (MAX_EVENTS/NUM_PRIORITIES); i++)
	{
		if(eventArray[priority][i].isActive == false)
		{
			eventPtr = &eventArray[priority][i];
			break;
		}
	}
	
	eventPtr->eventFunctionPtr = (void(*)(void*))functionPtr;
	eventPtr->eventArg = NULL;
	eventPtr->interval = interval;
	eventPtr->runsRemaining = numRuns;
	eventPtr->elapsed = false;
	
	if(timeUnits == SCHEDULER_1MS)
	{
		eventPtr->elapsedAt = millis() + interval;
	}
	else
	{
		eventPtr->elapsedAt = micros() + interval;
	}
	
	numEvents[priority]++;
	eventPtr->isActive = true;
	enable();
	return 0;
}

//handle any elapsed events
int SchedulerModule::handleEvents(int priorityLevel)
{
	//if not enabled or there aren't any events at this priority level
	if(!enabled || numEvents[priorityLevel] == 0)
	{
		return 0; //not enabled just return
	}
	
	uint64_t currentTime = millis();
	if(timeUnits == SCHEDULER_10US)
	{
		currentTime = micros();
	}
	
	for(int i = 0; i < (MAX_EVENTS/NUM_PRIORITIES); i++)
	{
		if(eventArray[priorityLevel][i].isActive && eventArray[priorityLevel][i].elapsedAt <= currentTime)
		{
			eventArray[priorityLevel][i].eventFunctionPtr(eventArray[priorityLevel][i].eventArg);
			if(eventArray[priorityLevel][i].runsRemaining > 0)
			{
				if(eventArray[priorityLevel][i].runsRemaining == 1)
				{
					eventArray[priorityLevel][i].isActive = false;
					numEvents[priorityLevel]--;
				}
				else
				{
					eventArray[priorityLevel][i].runsRemaining--;
				}
			}
			eventArray[priorityLevel][i].elapsed = 0;
			eventArray[priorityLevel][i].elapsedAt += eventArray[priorityLevel][i].interval;
		}
	}
	return 0;
}



//handle any elapsed events
int SchedulerModule::handleAllEvents()
{
	if(!enabled)
	{
		return 0; //not enabled just return
	}
	
	uint64_t currentTime = millis();
	if(timeUnits == SCHEDULER_10US)
	{
		currentTime = micros();
	}
	
	for(int i = 0; i < NUM_PRIORITIES; i++)
	{
		for(int j = 0; j < (MAX_EVENTS/NUM_PRIORITIES); j++)
		{
			if(eventArray[i][j].isActive && eventArray[i][j].elapsedAt <= currentTime)
			{
				eventArray[i][j].eventFunctionPtr(eventArray[i][j].eventArg);
				if(eventArray[i][j].runsRemaining > 0)
				{
					if(eventArray[i][j].runsRemaining == 1)
					{
						eventArray[i][j].isActive = false;
						numEvents[i]--;
					}
					else
					{
						eventArray[i][j].runsRemaining--;
					}
				}
				eventArray[i][j].elapsed = 0;
				eventArray[i][j].elapsedAt += eventArray[i][j].interval;
			}	
		}
	}
	return 0;
}

SchedulerModule SchedulerMillis = SchedulerModule(SCHEDULER_1MS);
SchedulerModule SchedulerMicros = SchedulerModule(SCHEDULER_10US);