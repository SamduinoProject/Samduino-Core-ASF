/*
 * RealTimeClock.h
 *
 * Created: 8/15/2016 10:19:42 AM
 *  Author: Nate
 */ 


#ifndef REALTIMECLOCK_H_
#define REALTIMECLOCK_H_

struct DateTime
{
	uint32_t year;
	uint32_t month;
	uint32_t day;
	uint32_t week;
	uint32_t hour;
	uint32_t minute;
	uint32_t second;
};

String dateTimeToString(DateTime* dateTime);

class RealTimeClock
{
	public:
		RealTimeClock();
		int init(void);
		int setDateTime(DateTime* currentDateTime);
		DateTime getDateTime();
		//tick functions should only be called by interrupt handlers
		int tickSecond();
	private:	
};

extern RealTimeClock RealTime;

#endif /* REALTIMECLOCK_H_ */