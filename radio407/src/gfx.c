#include "global.h"
#include "gfx.h"
#include "lcd.h"
#include "buttons.h"
#include "gfx_palette.h"

#include "ili9341_gfx.h"
#include "ili9341_font.h"
#include "fft.h"
#include "spi.h"

#include <stdio.h>
#include <stdarg.h>


Point_t Point(int X, int Y){
	Point_t thisPoint;
	thisPoint.X = X;
	thisPoint.Y = Y;
	return thisPoint;
}

float testVFOfreq = 14.123456f;
int freqInt;
int freqMHz;
int	freqkHz;
int	freqHz;

void gfxItemsInit(void){
	testVFOfreq = 14.123456f;
	freqInt = testVFOfreq*1000000;
	freqMHz = freqInt/1000000;
	freqkHz = freqInt/1000 - freqMHz*1000;
	freqHz	= freqInt - freqkHz*1000 - freqMHz*1000000;

	gfxLabelSet(G_VFO_VAL_KHZ, "%u.%u", 	freqMHz, freqkHz);
	gfxLabelSet(G_VFO_VAL_HZ, "%u", freqHz);


	for (int i=0; i<GFX_ITEM_NR; i++)
		gfxItems[i].pendUpd = 1;


}

void gfxLabelSet(int itemID, const char *fmt, ...){
	//char txtBuf[128];
	if (gfxItems[itemID].type == G_TYPE_LABEL){
		va_list args;
		va_start(args, fmt);
		int rc = vsnprintf(gfxItems[itemID].text, sizeof(gfxItems[itemID].text), fmt, args);
		va_end(args);
		char nlBuf[] = {"\r\n"};
		strcat(gfxItems[itemID].text, nlBuf);
		gfxItems[itemID].pendUpd = 1;
	}
}

void gfxBarSet(int itemID, float value){
	if (gfxItems[itemID].type == G_TYPE_PROGRESSBAR){
		if ((value < gfxItems[itemID].max)&(value > gfxItems[itemID].min)){
			gfxItems[itemID].val = value;
			gfxItems[itemID].pendUpd = 1;
		}
	}
}


void btnTest1(void){
	ili9341_fill_rect(_screen, COLOR_CYAN, 200, 200, 20, 20);
}
void btnTest2(void){
	ili9341_fill_rect(_screen, COLOR_MAROON, 200, 200, 20, 20);
}

int gfxCurrentScreen = G_SCREEN_MAIN;


ili9341_text_attr_t thisTextAttr;
#define FONT_LIST_LEN	4
const ili9341_font_t *fontList[FONT_LIST_LEN] = {	&ili9341_font_7x10,
													&ili9341_font_11x18,
													&ili9341_font_vfo_big,
													&ili9341_font_vfo_small,
												};

int wfRedrawStage = 0;

#include "soft_sched.h"
#include "soft_timer.h"
#include "audio_cfg.h"
#include "dsp.h"
#include "flash.h"


void gfxDbgDataUpd(void){
	//gfxBarSet(G_BAR_AUDIOLOAD, getAudioLoadPossible());
	//gfxBarSet(G_BAR_ELSELOAD, everythingElseLoad);

	float dspLoad = (softSchedTotalTicks*1000/10000)/(AUDIO_BUFFER_HALF_MS)*100.0f;
	float tasksLoad = (dspTotalTime*1000/10000)/(AUDIO_BUFFER_HALF_MS)*100.0f;



	// debugPrintFast("%02X %02X %02X %02X %02X %02X %02X %02X", 	flash.UniqID[0], flash.UniqID[1], flash.UniqID[2], flash.UniqID[3],
	 //															flash.UniqID[4], flash.UniqID[5], flash.UniqID[6], flash.UniqID[7]);


	//debugPrintFast("%02X %02X %02X", flash.jM,  flash.jID,  flash.jC);
//
	//int32_t fID = flashBlockSize();
	//debugPrintFast("%08X", );

	//debugPrintFast("t%u%% d%u%%", (int)dspLoad, (int)tasksLoad);
	//debugPrintFast("%u %u %u %08X", 	tix[0], tix[1], tix[2], flash.ID);
	debugPrintFast("%08X | %02x%02X%02X | %02X", 	flash.ID, flash.jC, flash.jID, flash.jM, flash.UniqID[0]);
									//softTasks[TASK_GFX_UPDATE].ticksTook,
									//softTasks[TASK_ADC].ticksTook,
									//softTasks[TASK_DBGUPD].ticksTook);
}

#include "ui.h"

//	WF parameters
#define LCD_W	(320)
#define LCD_H	(240)

#define WF_BAR_W		(LCD_W/FFT_USEFUL_BINS)
#define FFT_POS_X		0 //((LCD_W - (FFT_USEFUL_BINS * WF_BAR_W)) / 2)
#define FFT_H  			UI_FFT_H
#define FFT_POS_Y  		(LCD_H - 25 - FFT_H)

const int pixArrW = FFT_USEFUL_BINS * WF_BAR_W;
const int pixArrH = FFT_WF_LEN;
const uint16_t numPixels = pixArrW * pixArrH;
uint16_t WFpixeldata[FFT_USEFUL_BINS * WF_BAR_W * FFT_WF_LEN];
uint16_t wfNewPixelStrip[WF_BAR_W * FFT_USEFUL_BINS];

void scrollWF(void){
	// scroll waterfall
	for (int row = (FFT_WF_LEN - 1); row > 0; row--){
		for (int col = 0; col < pixArrW; col++){
			WFpixeldata[col + (row) * pixArrW] = WFpixeldata[col + (row-1) * pixArrW];
		}
	}

	//add lower spectrum scope row to waterfall[0]
	for (int i=0; i<(WF_BAR_W*FFT_USEFUL_BINS); i++){
		uint16_t color_le = __LEu16(&wfNewPixelStrip[i]);
		WFpixeldata[i] = color_le;
	}

	//gfxItems[G_FFT_WF].pendUpd = 1;
}

/*

*/


#define WF_REDRAW_STAGES	(2)

void gfxFFTredraw(void){
		if (wfRedrawStage < WF_REDRAW_STAGES-1) wfRedrawStage++;
		else wfRedrawStage = 0;

		int startBin = 1 + wfRedrawStage * FFT_USEFUL_BINS / WF_REDRAW_STAGES;
		int endBin = startBin + FFT_USEFUL_BINS / WF_REDRAW_STAGES;

		for (int bin=startBin; bin<endBin; bin++){
			if (fftMagnitudes[bin] != fftMagnitudesOld[bin]){

				int thisBarX = FFT_POS_X + bin * WF_BAR_W;
				uint16_t thisColor = fftPowerColors[fftMagnitudesdB[bin]*5];

				if (fftMagnitudes[bin] < fftMagnitudesOld[bin]){
					//spiBusy = 1;
					ili9341_fill_rect_up(	_screen,
											COLOR_BLACK,
											thisBarX,
											FFT_POS_Y,
											WF_BAR_W,
											FFT_H);
					//spiBusy = 0;
				}

				//spiBusy = 1;
				ili9341_fill_rect_up(	_screen,
										(thisColor),
										thisBarX,
										FFT_POS_Y,
										WF_BAR_W,
										fftMagnitudesdB[bin]*FFT_H/50);
				//spiBusy = 0;

				wfNewPixelStrip[bin * WF_BAR_W] = thisColor;
				wfNewPixelStrip[bin * WF_BAR_W + 1] = thisColor;
				fftMagnitudesOld[bin] = fftMagnitudes[bin];

			}
		}
}

void gfxWFredraw(){
	//static wfUpdStage;
	//if (wfUpdStage < WF_UPD_STAGES) wfUpdStage++;
	//else wfUpdStage=0;
	// col + (WF_BAR_W/2) * pixArrW

	//FFT_USEFUL_BINS * WF_BAR_W * FFT_WF_LEN
	//int addr = (FFT_USEFUL_BINS * WF_BAR_W * FFT_WF_LEN / (half + 1));
	//int addr = (half) * (FFT_USEFUL_BINS * WF_BAR_W * FFT_WF_LEN / 2);
	//uint16_t *pic = &WFpixeldata[addr];

	//spiBusy = 1;
	ili9341_fill_data(	_screen,
						0,
						FFT_POS_X,
						239 - FFT_WF_LEN - 25,// + (FFT_WF_LEN / 2 * half),
						FFT_USEFUL_BINS * WF_BAR_W,
						FFT_WF_LEN,///2,
						WFpixeldata);
	//spiBusy = 0;
}

void gfxItemsRedraw(void){
	bool skip = 0;
	for (int itemID=0; itemID<GFX_ITEM_NR; itemID++){
		gfxItemCommon_t *i = &gfxItems[itemID];
		if (i->screen == gfxCurrentScreen){
			if (i->pendUpd && i->isShown){
				switch(i->type){
					case G_TYPE_LABEL: {
						int txtSize = i->size.X;
						if (txtSize > (FONT_LIST_LEN-1)) txtSize = FONT_LIST_LEN-1;
						thisTextAttr.bg_color = i->backColor;
						thisTextAttr.fg_color = i->color;
						thisTextAttr.font = fontList[txtSize];
						thisTextAttr.origin_x = i->pos.X;
						thisTextAttr.origin_y = i->pos.Y;
						//spiBusy = 1;
							ili9341_draw_string(_screen, thisTextAttr, i->text);
						//spiBusy = 0;
						break;}

					case G_TYPE_PROGRESSBAR:{
						int	barLenPixels = (int)((i->val/i->max)*(float)i->size.X-2);
						if (barLenPixels < 0) barLenPixels = 0;
						if (barLenPixels > (i->size.X-2)) barLenPixels = i->size.X-2;

						int	oldbarLenPixels = (int)((i->oldVal/i->max)*(float)i->size.X-2);
						if (barLenPixels < 0) barLenPixels = 0;
						if (barLenPixels > (i->size.X-2)) oldbarLenPixels = i->size.X-2;

						ili9341_draw_rect(_screen, COLOR_WHITE, i->pos.X, 	i->pos.Y,	i->size.X, 		i->size.Y);
						if (barLenPixels != oldbarLenPixels){
							if (barLenPixels > oldbarLenPixels){
								//spiBusy = 1;
								ili9341_fill_rect(_screen, 	i->color,
															i->pos.X + 2 + oldbarLenPixels,
															i->pos.Y + 1,
															(barLenPixels - oldbarLenPixels),
															i->size.Y-2);
								//spiBusy = 0;
							}

							if (barLenPixels < oldbarLenPixels){
								//spiBusy = 1;
								ili9341_fill_rect(_screen, 	COLOR_BLACK,
															i->pos.X + 2 + barLenPixels,
															i->pos.Y + 1,
															(oldbarLenPixels - barLenPixels),
															i->size.Y-2);
								//spiBusy = 0;
							}
						}

						i->oldVal = i->val;
						break;
					}

					case G_TYPE_INDICATOR: {
						break;
					}

					default: break;
				}
				gfxItems[itemID].pendUpd = 0;
			}
		}
	}
}



