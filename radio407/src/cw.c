#include "cw.h"
#include "global.h"
#include "soft_timer.h"
#include "pins.h"
#include <stdbool.h>

//const int toQueue[2][5] = 	{{0, 		0x02, 		0x0E, 		0x3A, 			0x2E},
//							{0, 		0x0E, 		0x02, 		0x2E, 			0x3A}};

enum cwPaddles 				{CW_P_NONE, CW_P_L, 	CW_P_R, 	CW_P_LR, 		CW_P_RL};

const int toQueue[2][5] = 	{{0, 		0x01, 		0x07, 		0x1D, 			0x17},
							{0, 		0x07, 		0x01, 		0x17, 			0x1D}};
const int msgLens[5] = 		{0, 		1, 			3, 			5, 				5};

enum cwStates {CW_STATE_SILENCE, CW_STATE_TX, CW_STATE_PAUSE};
enum cwKeyModes {CW_MODE_MANUAL, CW_MODE_AUTO};


struct CW_t CW;

void cwChangeSpeed(int newWPM){
	if ((newWPM > 0) && (newWPM<=50)){
		CW.speedWPM = newWPM;
		float msPerDot = (60.0f / (50.0f * (float)CW.speedWPM)) * 1000.0f;
		CW.timerTicksPerDot = (int)msPerDot * CW.timerHz / 1000;
	}
}

void cwInit(void){
	CW.paddleState = CW_P_NONE;
	CW.paddleOldState = CW.paddleOldState;
	CW.txState = 0;
	CW.sendQueue = 0;
	//CW.ptrToTimer = &preciseTimerCounter;

	CW.timerHz = SOFT_TIMER_HZ;
	cwChangeSpeed(10);
	CW.timerCounter = 0;
	CW.paddlesReversed = 0;
}




void cwTimerRoutine(void){
	CW.timerCounter++;									// increment timer
	if (CW.timerCounter >= CW.timerTicksPerDot) {		// every time
		CW.timerCounter = 0;							// zero out timer
		if (CW.msgLenLeftInBuf > 0) CW.msgLenLeftInBuf--;	// decrement new msg lock counter



		if (!CW.txState && (CW.msgLenLeftInBuf == 0)){
			CW.sendQueue = toQueue[CW.paddlesReversed][CW.paddleState];	// add to queue
			CW.msgLenLeftInBuf = msgLens[CW.paddleState];
		}

		CW.txState = CW.sendQueue & 0x01;				// tx least sig-t bit
			CW.sendQueue = CW.sendQueue >> 1;				// shift queue

	}
}


void cwInputCallback(uint16_t GPIO_Pin){
	bool L = !HAL_GPIO_ReadPin(KEY_L_PORT, KEY_L_PIN);
	bool R = !HAL_GPIO_ReadPin(KEY_R_PORT, KEY_R_PIN);

	CW.paddleInput =  (R | (L << 1));
	if (CW.paddleInput != CW.paddleOldInput){
		/*
		if (CW.paddleInput == 0x00) 									CW.paddleState = CW_P_NONE;
		if (CW.paddleInput == 0x01) 									CW.paddleState = CW_P_L;
		if (CW.paddleInput == 0x02) 									CW.paddleState = CW_P_R;
		if ((CW.paddleInput == 0x03) && (CW.paddleOldState == 0x01)) 	CW.paddleState = CW_P_LR;
		if ((CW.paddleInput == 0x03) && (CW.paddleOldState == 0x02)) 	CW.paddleState = CW_P_RL;
		*/

		if (CW.paddleInput <  0x03) CW.paddleState = CW.paddleInput;
		if (CW.paddleInput == 0x03) CW.paddleState = 2 + CW.paddleOldInput;

		CW.paddleOldInput = CW.paddleInput;
	}
}


/*
void dash(){                                                                    //добавить в очередь тире
if ((cwcycle==0)&(cwtoq)){
cwqueue=14;}
}

void dot(){                                                                     //добавить в очередь точку
if ((cwcycle==0)&(cwtoq)){
cwqueue=2;}
}
 */

/*
void cwStateUpdate(void){
if (CW.state != CW.oldState){

	switch (CW.state){
		case CW_STATE_SILENCE: {
			break;
		}
		case CW_STATE_DOT: {
			break;
		}
		case CW_STATE_DASH: {
			break;
		}
		case CW_STATE_BETWEEN: {
			break;
		}


	}

CW.oldState = CW.state;
}
}
*/


	/*
	void cwReadPaddles(void){
		bool L = HAL_GPIO_ReadPin(KEY_L_PORT, KEY_L_PIN);
		bool R = HAL_GPIO_ReadPin(KEY_R_PORT, KEY_R_PIN);

		CW.paddleState =  (R || (L << 1));
		if (CW.paddleState != CW.paddleOldState){
			CW.paddleOldState = CW.paddleState;
			if (CW.paddleState == 0x00) CW.state = CW_P_NONE;
			if (CW.paddleState == 0x01) CW.state = CW_P_R;
			if (CW.paddleState == 0x10) {CW.state = CW_P_L;
			if ((CW.paddleOldState == 0x10) && (CW.paddleState == 0x11)) CW.state = CW_P_LR;
			if ((CW.paddleOldState == 0x01) && (CW.paddleState == 0x11)) CW.state = CW_P_RL;
		}
	}
	*/
