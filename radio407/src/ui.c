#include "ui.h"
#include "global.h"
#include "main.h"
#include "gfx.h"
#include "fft.h"
#include "rtc.h"
#include "radio_state.h"
#include "lcd.h"

typedef struct{
	const uint16_t color;
	const char text[5];
} coloredLabel_t;

coloredLabel_t modLabels[MOD_NR] = {
		[MOD_USB].color = COLOR_BLUE,
		[MOD_USB].text = "USB\0",

		[MOD_LSB].color = COLOR_YELLOW,
		[MOD_LSB].text = "LSB\0",

		[MOD_CW].color = COLOR_RED,
		[MOD_CW].text = "CW\0",

		[MOD_CWN].color = COLOR_LIGHTGREY,
		[MOD_CWN].text = "CWN\0",

		[MOD_AM].color = COLOR_DARKCYAN,
		[MOD_AM].text = "USB\0",

		[MOD_FM].color = COLOR_MAGENTA,
		[MOD_FM].text = "FM\0",
};

void uiScrollBands(int delta){

}


void uiScrollModes(int delta){

}


typedef struct{
	char 	text[7];
	void 	(*funcPtrLong)();
	void 	(*funcPtrShort)();
	bool 	isActive;
} panelLabel_t;

enum lowerPanelLabels{LP_TEST1, LP_TEST2, LP_TEST3, LP_TEST4, LP_TEST5, LP_NR};

void drawTest(void){
	ili9341_fill_circle(_screen, COLOR_RED, 20, 20, 10);
}

panelLabel_t lowerPanel[LP_NR] = {
		[LP_TEST1].text = "test1",
		[LP_TEST1].isActive = 1,
		[LP_TEST1].funcPtrShort = drawTest,

		[LP_TEST2].text = "test2",
		[LP_TEST2].isActive = 1,
		[LP_TEST2].funcPtrShort = drawTest,

		[LP_TEST3].text = "test3",
		[LP_TEST3].isActive = 1,
		[LP_TEST3].funcPtrShort = drawTest,

		[LP_TEST4].text = "test4",
		[LP_TEST4].isActive = 0,
		[LP_TEST4].funcPtrShort = drawTest,

		[LP_TEST5].text = "test5",
		[LP_TEST5].isActive = 1,
		[LP_TEST5].funcPtrShort = drawTest,
};

#include "buttons.h"
#include "gfx.h"

#define LOWER_PANEL_LABELS	3
int lpFirstLabelIdx	= 0;

int btnIndexList[LOWER_PANEL_LABELS] = {B_LEFT, B_MID, B_RIGHT};
int gfxLabelsIndexList[LOWER_PANEL_LABELS] = {G_LOWER_LABEL1, G_LOWER_LABEL2, G_LOWER_LABEL3};


void uiScrollLowerPanel(int delta){
	int newFirstLabelIdx = lpFirstLabelIdx + delta * LOWER_PANEL_LABELS;
	if (newFirstLabelIdx < 0) newFirstLabelIdx = 0;
	if (newFirstLabelIdx > LOWER_PANEL_LABELS) newFirstLabelIdx -= LOWER_PANEL_LABELS;

	for (int thisLabelIdx = newFirstLabelIdx; thisLabelIdx < (newFirstLabelIdx+LOWER_PANEL_LABELS); thisLabelIdx++){
		int labelNumberOnScreen = thisLabelIdx - ( thisLabelIdx / LOWER_PANEL_LABELS ) * LOWER_PANEL_LABELS;
		if (thisLabelIdx < LOWER_PANEL_LABELS){
				Button[btnIndexList[labelNumberOnScreen]].funcPtrShort = lowerPanel[thisLabelIdx].funcPtrShort;
				Button[btnIndexList[labelNumberOnScreen]].funcPtrLong = lowerPanel[thisLabelIdx].funcPtrLong;
				//gfxItems[gfxLabelsIndexList[labelNumberOnScreen]].text = lowerPanel[thisLabelIdx].text;
				strncpy (	gfxItems[gfxLabelsIndexList[labelNumberOnScreen]].text,
							lowerPanel[thisLabelIdx].text,
							sizeof(gfxItems[gfxLabelsIndexList[labelNumberOnScreen]].text));
				Button[btnIndexList[labelNumberOnScreen]].Locked = 0;
				gfxItems[gfxLabelsIndexList[labelNumberOnScreen]].color = COLOR_GREEN;
			}

			else {
				Button[btnIndexList[labelNumberOnScreen]].funcPtrShort = 0;
				Button[btnIndexList[labelNumberOnScreen]].funcPtrLong = 0;
				strncpy (	"\0",
							lowerPanel[thisLabelIdx].text,
							sizeof("\0"));
				Button[btnIndexList[labelNumberOnScreen]].Locked = 1;
				gfxItems[gfxLabelsIndexList[labelNumberOnScreen]].color = COLOR_DARKGREY;
			}

		gfxItems[gfxLabelsIndexList[labelNumberOnScreen]].pendUpd = 1;
	}

}



void updateUiGfx(void){
	gfxItems[G_SMETER].val = (float)fftMagnitudesdB[1]/2;
	gfxItems[G_SMETER].pendUpd=1;

	//RTC_TimeTypeDef a = rtcGettime();
	gfxLabelSet(G_UPPER_TIME, "%02u:%02u:%02u", 	rtcTime.Hours, rtcTime.Minutes, rtcTime.Seconds);
	//gfxLabelSet(G_VFO_VAL_KHZ, "%05u", radio.vfoFreqHz[0]/1000);
	//gfxLabelSet(G_VFO_VAL_HZ, "%03u", radio.vfoFreqHz[0] - (radio.vfoFreqHz[0]/1000)*1000);
	//uiScrollLowerPanel(1);
}

/*
uint32_t vfoValHz[2] = {14050100, 7100200};
void uiUpdVfoVal(void){
	testVFOfreq = 14.123456f;
	freqInt = testVFOfreq*1000000;
	freqMHz = freqInt/1000000;
	freqkHz = freqInt/1000 - freqMHz*1000;
	freqHz	= freqInt - freqkHz*1000 - freqMHz*1000000;

	gfxLabelSet(G_VFO_VAL_KHZ, "%u.%u", 	freqMHz, freqkHz);
	gfxLabelSet(G_VFO_VAL_HZ, "%u", freqHz);
}
*/
