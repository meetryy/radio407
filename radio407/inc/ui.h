#pragma once
#include <stdint.h>


// graphics layout dimensions

#define	LCD_WIDTH		320
#define	LCD_HEIGHT		240

#define UI_PANEL_UP_H	25
#define UI_PANEL_LO_H	25
#define UI_PANEL_UP_TXT_OFFSET_Y	2
#define UI_PANEL_LO_TXT_OFFSET_Y	2
#define	UI_PANEL_LO_TXT_H	16
#define	UI_PANEL_R_TXT_H	16

#define	UI_WF_W			(256)
#define	UI_WF_H			30
#define	UI_FFT_H		30
#define UI_PANEL_R_W	(LCD_WIDTH - UI_WF_W)
#define UI_PANEL_R_X	(UI_WF_W + 1)
#define UI_PANEL_R_TXT_OFFSET_X	2
#define UI_PANEL_R_Y	(LCD_HEIGHT - UI_PANEL_LO_H - UI_WF_H - UI_FFT_H)
#define	UI_PANEL_R_TXT_H	16
#define UI_PANEL_R_SPACING_X	1

void updateUiGfx(void);
void uiScrollLowerPanel(int delta);

