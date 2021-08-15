#include "global.h"
#include "soft_sched.h"
#include "soft_timer.h"

#include "fft.h"
#include "gfx.h"
#include "adc.h"
#include "spi.h"
#include "lcd.h"
#include "buttons.h"

softTask_t softTasks[TASK_NR]= {
		[TASK_DBGUPD].isEnabled = 1,
		[TASK_DBGUPD].periodMs = 200,
		[TASK_DBGUPD].funcPtr = gfxDbgDataUpd,
		[TASK_DBGUPD].executeNow = 0,

		[TASK_ADC].isEnabled = 1,
		[TASK_ADC].periodMs = 100,
		[TASK_ADC].funcPtr = btnUpdateFromADC,
		[TASK_ADC].executeNow = 0,

		[TASK_WF_SCROLL].isEnabled = 1,
		[TASK_WF_SCROLL].periodMs = 150,
		[TASK_WF_SCROLL].funcPtr = scrollWF,
		[TASK_WF_SCROLL].executeNow = 0,

};

uint16_t softSchedTotalTicks;

uint32_t softShedTimer = 0;
uint32_t divisionTimer = 0;

#define SOFT_TASK_PERIOD_HZ			1000
#define SOFT_TASK_PERIOD_TIMER_VAL	(SOFT_TIMER_HZ/SOFT_TASK_PERIOD_HZ)

void processSoftTasksAsync(void){
	if (divisionTimer < SOFT_TASK_PERIOD_TIMER_VAL){
		divisionTimer++;
	}

	else {
		divisionTimer = 0;
		softShedTimer = preciseTimerValue();
		uint16_t totalTicks = 0;
		for (int i=0;i<TASK_NR;i++){

			if ((softTasks[i].isEnabled & (softShedTimer >= softTasks[i].nextTime)) | softTasks[i].executeNow){
			//if (softShedTimer >= softTasks[i].nextTime){

				uint32_t timeNow = preciseTimerValue();
				softTasks[i].nextTime = timeNow + softTasks[i].periodMs*10;//SOFT_MS(softTasks[i].periodMs);
				softTasks[i].funcPtr();
				softTasks[i].executeNow = 0;
				softTasks[i].ticksTook = preciseTimerValue() - timeNow;
				totalTicks += softTasks[i].ticksTook;
				if (totalTicks>0) softSchedTotalTicks = totalTicks;

			}
		}
	}
}



#include "dsp.h"
#include "ui.h"

bool* syncSchedFlagPtr =  &dspRingHalf;
bool syncSchedFlagPtrOld;

uint16_t tix[SYNC_TASK_NR] = {0};

int currSyncTask = 0;

/*
const void (*gfxQueuePtr[SYNC_TASK_NR])() = {
		gfxWFredraw,
		gfxFFTredraw,
		gfxItemsRedraw,
};
*/

void processSoftTasksSync(void){

	if (*syncSchedFlagPtr != syncSchedFlagPtrOld){
		//gfxUpdateQueue();


		if (currSyncTask < SYNC_TASK_NR) currSyncTask++;
		else currSyncTask = 0;

		uint16_t timeStart = preciseTimerValue();

		//while (spiBusy) {}
		//if (!spiBusy){
			switch (currSyncTask){
				//case 0: {gfxWFredraw(0); break;}
				case 0: {gfxWFredraw(); break;}
				case 1: {gfxFFTredraw(); break;}
				case 2: {gfxItemsRedraw(); break;}
		//	}
		}

		updateUiGfx();
		//gfxQueuePtr[currSyncTask]();
		tix[currSyncTask] = preciseTimerValue()-timeStart;
		//

		syncSchedFlagPtrOld = *syncSchedFlagPtr;
	}
}





