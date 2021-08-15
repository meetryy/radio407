#pragma once
#include <stdint.h>

enum taskName{	TASK_WF_SCROLL,
				//TASK_GFX_FFT,
				//TASK_GFX_WF,
				TASK_GFX_ALL,
				//TASK_GFX_UPDATE,
				TASK_ADC,
				TASK_DBGUPD,
				TASK_NR};

extern uint16_t softSchedTotalTicks;

typedef struct{
	uint8_t 		executeNow;
	uint8_t			isEnabled;
	uint32_t		nextTime;
	uint16_t		periodMs;
	uint16_t		ticksTook;
	float			msTook;
	void 			(*funcPtr)();
} softTask_t;

#define SYNC_TASK_NR	3
extern uint16_t tix[SYNC_TASK_NR];

extern softTask_t softTasks[TASK_NR];

void processSoftTasksAsync(void);
void processSoftTasksSync(void);










