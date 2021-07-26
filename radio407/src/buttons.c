#include "buttons.h"
#include "global.h"
#include "adc.h"

ButtonStruct_t Button[BUTTON_NR] = {
		[B_ENC1].HasLongPress = 1,
		[B_ENC1].Locked = 0,
		[B_ENC1].funcPtrLong = btnTest1,
		[B_ENC1].funcPtrShort = btnTest2,
};
const uint16_t btnADCvalues[BUTTON_NR] = {0, 30, 120, 300, 645, 1245, 2390};
uint8_t	btnADCdelta = 20;
uint16_t btnNoneADC	= 3995;

void btnUpdateFromADC(void){
	int16_t thisBtnADC = adcCh[ADC_BUTTONS].ADCsmooth;
	if (thisBtnADC < btnNoneADC){
		// button is pressed
		for (uint8_t i = 0; i<BUTTON_NR; i++){
			if ((thisBtnADC < (btnADCvalues[i]+btnADCdelta)) && (thisBtnADC > (btnADCvalues[i]-btnADCdelta))){
				Button[i].State = PRESSED;
				break;
			}
			//else {
			//	Button[i].State = RELEASED;
			//}
		}
	}
	else{
		for (uint8_t i = 0; i<BUTTON_NR; i++)
			Button[i].State = RELEASED;
	}

	btnScan();
}

//bool (*f)();
//f = A;
//f();
#include <stdbool.h>


void btnScan (void) {
	ButtonStruct_t* b;
	for (uint8_t i = 0; i<BUTTON_NR; i++){
		b = &Button[i];
		if (!b->Locked){
			//b->LongPress = 0;
			if ((b->State == PRESSED) && (b->OldState == PRESSED) && !b->waitForRelease){
				b->EndTimer = HAL_GetTick();
				if ((b->EndTimer - b->StartTimer) >= LONGPRESS_MS){
					if (b->HasLongPress)
							b->ProcessingPending = PRESSED_LONG;
					else 	b->ProcessingPending = PRESSED;
					b->waitForRelease = 1;
					b->OldState = b->State;
					// call long press function
					b->funcPtrLong();
					b->ProcessingPending = RELEASED;
					b->test1++;
					break;
				}
			}

			if ((b->State == PRESSED) && (b->OldState == RELEASED)){
				b->StartTimer = HAL_GetTick();
				b->OldState = b->State;
				break;
			}

			if	((b->State == RELEASED) && (b->OldState == PRESSED)){
				b->EndTimer = HAL_GetTick();
				if (!b->waitForRelease){
					if ((b->EndTimer - b->StartTimer) < LONGPRESS_MS){
						b->ProcessingPending = PRESSED;
						// call short press function
						b->funcPtrShort();
						b->ProcessingPending = RELEASED;
						b->test2++;
					}
				}
				else{
					b->waitForRelease = 0;
					b->ProcessingPending = RELEASED;
				}
				b->OldState = b->State;
				break;
			}

		}
	}
}
