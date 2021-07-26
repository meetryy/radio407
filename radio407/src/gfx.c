#include "global.h"
#include "gfx.h"
#include "lcd.h"
#include "buttons.h"

#include "ili9341_gfx.h"
#include "ili9341_font.h"

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

	gfxLabelSet(G_VFO_VAL, "%u.%u.%u", 	freqMHz, freqkHz, freqHz);

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

const ili9341_font_t *fontList[3] = {&ili9341_font_7x10, &ili9341_font_11x18, &ili9341_font_16x26};


void gfxItemsRedraw(void){
	//gfxItems[G_BAR].val += 1.0f;
	//gfxItems[G_BAR].pendUpd = 1;

	for (int itemID=0; itemID<GFX_ITEM_NR; itemID++){
		gfxItemCommon_t *i = &gfxItems[itemID];
		if (i->screen == gfxCurrentScreen){
			if (i->pendUpd){
				switch(i->type){
					case G_TYPE_LABEL: {
						int txtSize = i->size.X;
						if (txtSize > 2) txtSize = 2;
						thisTextAttr.bg_color = i->backColor;
						thisTextAttr.fg_color = i->color;
						thisTextAttr.font = fontList[txtSize];
						thisTextAttr.origin_x = i->pos.X;
						thisTextAttr.origin_y = i->pos.Y;
						ili9341_draw_string(_screen, thisTextAttr, i->text);
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
								ili9341_fill_rect(_screen, 	i->color,
															i->pos.X + 1 + oldbarLenPixels,
															i->pos.Y + 1,
															(barLenPixels - oldbarLenPixels),
															i->size.Y-2);
							}
							if (barLenPixels < oldbarLenPixels){
								ili9341_fill_rect(_screen, 	COLOR_BLACK,
															i->pos.X + 1 + barLenPixels,
															i->pos.Y + 1,
															(oldbarLenPixels - barLenPixels),
															i->size.Y-2);
							}
						}

						i->oldVal = i->val;

						//ili9341_fill_rect(_screen, COLOR_BLACK, i->pos.X+1, i->pos.Y+1, i->size.X-2, 	i->size.Y-2);
						//ili9341_fill_rect(_screen, i->color, 	i->pos.X+1, i->pos.Y+1, barLenPixels, 	i->size.Y-2);


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



