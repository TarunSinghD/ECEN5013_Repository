

#include "system_MKL25Z4.h"
#ifndef INCLUDES_PROFILER_H_
#define INCLUDES_PROFILER_H_

#define MOD_VAL 40			//to get time period of 10Us
#define T1CLK  	4

void start_time(void);
void end_time(void);
void init_profiler(void);

extern volatile uint16_t overflow_count;
#endif /* INCLUDES_PROFILER_H_ */
