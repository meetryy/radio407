#include "global.h"
#include "gfx.h"
#include "ui.h"

//gfxItemCommon_t gfxItems[GFX_ITEM_NR];

gfxItemCommon_t gfxItems[GFX_ITEM_NR] = {
	[G_DEBUG_STRING].type = G_TYPE_LABEL,
	[G_DEBUG_STRING].pos.X = 2,
	[G_DEBUG_STRING].pos.Y = 2,
	[G_DEBUG_STRING].size.X = 0,
	[G_DEBUG_STRING].isShown = 1,
	[G_DEBUG_STRING].color = COLOR_WHITE,
	[G_DEBUG_STRING].backColor = COLOR_BLACK,
	[G_DEBUG_STRING].highlighted = 0,
	[G_DEBUG_STRING].highlightable = 0,
	[G_DEBUG_STRING].text = "",
	[G_DEBUG_STRING].screen = G_SCREEN_MAIN,

	[G_BAR_AUDIOLOAD].type = G_TYPE_PROGRESSBAR,
	[G_BAR_AUDIOLOAD].pos.X = 5,
	[G_BAR_AUDIOLOAD].pos.Y = 100,
	[G_BAR_AUDIOLOAD].size.X = 150,
	[G_BAR_AUDIOLOAD].size.Y = 8,
	[G_BAR_AUDIOLOAD].isShown = 0,
	[G_BAR_AUDIOLOAD].color = COLOR_GREEN,
	[G_BAR_AUDIOLOAD].backColor = COLOR_BLACK,
	[G_BAR_AUDIOLOAD].highlightable = 0,
	[G_BAR_AUDIOLOAD].screen = G_SCREEN_MAIN,
	[G_BAR_AUDIOLOAD].val = 0.0f,
	[G_BAR_AUDIOLOAD].min = 0.0f,
	[G_BAR_AUDIOLOAD].max = 100.0,

	[G_BAR_ELSELOAD].type = G_TYPE_PROGRESSBAR,
	[G_BAR_ELSELOAD].pos.X = 160,
	[G_BAR_ELSELOAD].pos.Y = 100,
	[G_BAR_ELSELOAD].size.X = 150,
	[G_BAR_ELSELOAD].size.Y = 8,
	[G_BAR_ELSELOAD].isShown = 0,
	[G_BAR_ELSELOAD].color = COLOR_RED,
	[G_BAR_ELSELOAD].backColor = COLOR_BLACK,
	[G_BAR_ELSELOAD].highlightable = 0,
	[G_BAR_ELSELOAD].screen = G_SCREEN_MAIN,
	[G_BAR_ELSELOAD].val = 0.0f,
	[G_BAR_ELSELOAD].min = 0.0f,
	[G_BAR_ELSELOAD].max = 100.0f,

	[G_VFO_VAL_KHZ].type = G_TYPE_LABEL,
	[G_VFO_VAL_KHZ].pos.X = 30,
	[G_VFO_VAL_KHZ].pos.Y = UI_PANEL_UP_H + 5,
	[G_VFO_VAL_KHZ].size.X = 2,
	[G_VFO_VAL_KHZ].isShown = 1,
	[G_VFO_VAL_KHZ].color = COLOR_GREEN,
	[G_VFO_VAL_KHZ].backColor = COLOR_BLACK,
	[G_VFO_VAL_KHZ].text = "",
	[G_VFO_VAL_KHZ].screen = G_SCREEN_MAIN,

	[G_VFO_VAL_HZ].type = G_TYPE_LABEL,
	[G_VFO_VAL_HZ].pos.X = 5 * 28+2 + 30,
	[G_VFO_VAL_HZ].pos.Y = UI_PANEL_UP_H + 5 + 7,
	[G_VFO_VAL_HZ].size.X = 3,
	[G_VFO_VAL_HZ].isShown = 1,
	[G_VFO_VAL_HZ].color = COLOR_GREEN,
	[G_VFO_VAL_HZ].backColor = COLOR_BLACK,
	[G_VFO_VAL_HZ].text = "",
	[G_VFO_VAL_HZ].screen = G_SCREEN_MAIN,


// =================================




	[G_UPPER_MODE].type = G_TYPE_LABEL,
	[G_UPPER_MODE].pos.X = 2,
	[G_UPPER_MODE].pos.Y = UI_PANEL_UP_TXT_OFFSET_Y,
	[G_UPPER_MODE].size.X = 1,
	[G_UPPER_MODE].isShown = 1,
	[G_UPPER_MODE].color = COLOR_CYAN,
	[G_UPPER_MODE].backColor = COLOR_BLACK,
	[G_UPPER_MODE].text = "USB",
	[G_UPPER_MODE].screen = G_SCREEN_MAIN,

	[G_UPPER_FILTER].type = G_TYPE_LABEL,
	[G_UPPER_FILTER].pos.X = 50,
	[G_UPPER_FILTER].pos.Y = UI_PANEL_UP_TXT_OFFSET_Y,
	[G_UPPER_FILTER].size.X = 1,
	[G_UPPER_FILTER].isShown = 1,
	[G_UPPER_FILTER].color = COLOR_PINK,
	[G_UPPER_FILTER].backColor = COLOR_BLACK,
	[G_UPPER_FILTER].highlighted = 0,
	[G_UPPER_FILTER].text = "2k7",
	[G_UPPER_FILTER].screen = G_SCREEN_MAIN,

	[G_UPPER_VOLTAGE].type = G_TYPE_LABEL,
	[G_UPPER_VOLTAGE].pos.X = 250,
	[G_UPPER_VOLTAGE].pos.Y = UI_PANEL_UP_TXT_OFFSET_Y,
	[G_UPPER_VOLTAGE].size.X = 1,
	[G_UPPER_VOLTAGE].isShown = 1,
	[G_UPPER_VOLTAGE].color = COLOR_RED,
	[G_UPPER_VOLTAGE].backColor = COLOR_BLACK,
	[G_UPPER_VOLTAGE].highlighted = 0,
	[G_UPPER_VOLTAGE].text = "13.9V",
	[G_UPPER_VOLTAGE].screen = G_SCREEN_MAIN,

	[G_UPPER_TIME].type = G_TYPE_LABEL,
	[G_UPPER_TIME].pos.X = 200,
	[G_UPPER_TIME].pos.Y = UI_PANEL_UP_TXT_OFFSET_Y,
	[G_UPPER_TIME].size.X = 1,
	[G_UPPER_TIME].isShown = 1,
	[G_UPPER_TIME].color = COLOR_WHITE,
	[G_UPPER_TIME].backColor = COLOR_BLACK,
	[G_UPPER_TIME].highlighted = 0,
	[G_UPPER_TIME].text = "12:30",
	[G_UPPER_TIME].screen = G_SCREEN_MAIN,


	[G_LOWER_LABEL1].type = G_TYPE_LABEL,
	[G_LOWER_LABEL1].pos.X = 2,
	[G_LOWER_LABEL1].pos.Y = LCD_HEIGHT - UI_PANEL_LO_TXT_OFFSET_Y - UI_PANEL_LO_TXT_H,
	[G_LOWER_LABEL1].size.X = 1,
	[G_LOWER_LABEL1].isShown = 1,
	[G_LOWER_LABEL1].color = COLOR_WHITE,
	[G_LOWER_LABEL1].backColor = COLOR_BLACK,
	[G_LOWER_LABEL1].highlighted = 0,
	[G_LOWER_LABEL1].text = "FUNC1",
	[G_LOWER_LABEL1].screen = G_SCREEN_MAIN,

	[G_LOWER_LABEL2].type = G_TYPE_LABEL,
	[G_LOWER_LABEL2].pos.X = 90,
	[G_LOWER_LABEL2].pos.Y = LCD_HEIGHT - UI_PANEL_LO_TXT_OFFSET_Y - UI_PANEL_LO_TXT_H,
	[G_LOWER_LABEL2].size.X = 1,
	[G_LOWER_LABEL2].isShown = 1,
	[G_LOWER_LABEL2].color = COLOR_WHITE,
	[G_LOWER_LABEL2].backColor = COLOR_BLACK,
	[G_LOWER_LABEL2].highlighted = 0,
	[G_LOWER_LABEL2].text = "FUNC2",
	[G_LOWER_LABEL2].screen = G_SCREEN_MAIN,

	[G_LOWER_LABEL3].type = G_TYPE_LABEL,
	[G_LOWER_LABEL3].pos.X = 200,
	[G_LOWER_LABEL3].pos.Y = LCD_HEIGHT - UI_PANEL_LO_TXT_OFFSET_Y - UI_PANEL_LO_TXT_H,
	[G_LOWER_LABEL3].size.X = 1,
	[G_LOWER_LABEL3].isShown = 1,
	[G_LOWER_LABEL3].color = COLOR_WHITE,
	[G_LOWER_LABEL3].backColor = COLOR_BLACK,
	[G_LOWER_LABEL3].highlighted = 0,
	[G_LOWER_LABEL3].text = "FUNC3",
	[G_LOWER_LABEL3].screen = G_SCREEN_MAIN,

	[G_RIGHT_LABEL1].type = G_TYPE_LABEL,
	[G_RIGHT_LABEL1].pos.X = UI_PANEL_R_X + UI_PANEL_R_TXT_OFFSET_X,
	[G_RIGHT_LABEL1].pos.Y = UI_PANEL_R_Y + (UI_PANEL_R_TXT_H+UI_PANEL_R_SPACING_X) * 0,
	[G_RIGHT_LABEL1].size.X = 1,
	[G_RIGHT_LABEL1].isShown = 1,
	[G_RIGHT_LABEL1].color = COLOR_WHITE,
	[G_RIGHT_LABEL1].backColor = COLOR_BLACK,
	[G_RIGHT_LABEL1].highlighted = 0,
	[G_RIGHT_LABEL1].text = "RIG1",
	[G_RIGHT_LABEL1].screen = G_SCREEN_MAIN,

	[G_RIGHT_LABEL2].type = G_TYPE_LABEL,
	[G_RIGHT_LABEL2].pos.X = UI_PANEL_R_X + UI_PANEL_R_TXT_OFFSET_X,
	[G_RIGHT_LABEL2].pos.Y = UI_PANEL_R_Y + (UI_PANEL_R_TXT_H+UI_PANEL_R_SPACING_X)* 1,
	[G_RIGHT_LABEL2].size.X = 1,
	[G_RIGHT_LABEL2].isShown = 1,
	[G_RIGHT_LABEL2].color = COLOR_WHITE,
	[G_RIGHT_LABEL2].backColor = COLOR_BLACK,
	[G_RIGHT_LABEL2].highlighted = 0,
	[G_RIGHT_LABEL2].text = "RIG2",
	[G_RIGHT_LABEL2].screen = G_SCREEN_MAIN,

	[G_RIGHT_LABEL3].type = G_TYPE_LABEL,
	[G_RIGHT_LABEL3].pos.X = UI_PANEL_R_X + UI_PANEL_R_TXT_OFFSET_X,
	[G_RIGHT_LABEL3].pos.Y = UI_PANEL_R_Y + (UI_PANEL_R_TXT_H+UI_PANEL_R_SPACING_X)* 2,
	[G_RIGHT_LABEL3].size.X = 1,
	[G_RIGHT_LABEL3].isShown = 1,
	[G_RIGHT_LABEL3].color = COLOR_WHITE,
	[G_RIGHT_LABEL3].backColor = COLOR_BLACK,
	[G_RIGHT_LABEL3].highlighted = 0,
	[G_RIGHT_LABEL3].text = "RIG3",
	[G_RIGHT_LABEL3].screen = G_SCREEN_MAIN,

	[G_RIGHT_LABEL4].type = G_TYPE_LABEL,
	[G_RIGHT_LABEL4].pos.X = UI_PANEL_R_X + UI_PANEL_R_TXT_OFFSET_X,
	[G_RIGHT_LABEL4].pos.Y = UI_PANEL_R_Y + (UI_PANEL_R_TXT_H+UI_PANEL_R_SPACING_X)* 3,
	[G_RIGHT_LABEL4].size.X = 1,
	[G_RIGHT_LABEL4].isShown = 1,
	[G_RIGHT_LABEL4].color = COLOR_WHITE,
	[G_RIGHT_LABEL4].backColor = COLOR_BLACK,
	[G_RIGHT_LABEL4].highlighted = 0,
	[G_RIGHT_LABEL4].text = "RIG4",
	[G_RIGHT_LABEL4].screen = G_SCREEN_MAIN,

	[G_RIGHT_LABEL5].type = G_TYPE_LABEL,
	[G_RIGHT_LABEL5].pos.X = UI_PANEL_R_X + UI_PANEL_R_TXT_OFFSET_X,
	[G_RIGHT_LABEL5].pos.Y = UI_PANEL_R_Y + (UI_PANEL_R_TXT_H+UI_PANEL_R_SPACING_X)* 4,
	[G_RIGHT_LABEL5].size.X = 1,
	[G_RIGHT_LABEL5].isShown = 1,
	[G_RIGHT_LABEL5].color = COLOR_WHITE,
	[G_RIGHT_LABEL5].backColor = COLOR_BLACK,
	[G_RIGHT_LABEL5].highlighted = 0,
	[G_RIGHT_LABEL5].text = "RIG5",
	[G_RIGHT_LABEL5].screen = G_SCREEN_MAIN,

	[G_RIGHT_LABEL6].type = G_TYPE_LABEL,
	[G_RIGHT_LABEL6].pos.X = UI_PANEL_R_X + UI_PANEL_R_TXT_OFFSET_X,
	[G_RIGHT_LABEL6].pos.Y = UI_PANEL_R_Y + (UI_PANEL_R_TXT_H+UI_PANEL_R_SPACING_X)* 5,
	[G_RIGHT_LABEL6].size.X = 1,
	[G_RIGHT_LABEL6].isShown = 1,
	[G_RIGHT_LABEL6].color = COLOR_WHITE,
	[G_RIGHT_LABEL6].backColor = COLOR_BLACK,
	[G_RIGHT_LABEL6].highlighted = 0,
	[G_RIGHT_LABEL6].text = "RIG6",
	[G_RIGHT_LABEL6].screen = G_SCREEN_MAIN,


		[G_LABEL_VFO].type = G_TYPE_LABEL,
		[G_LABEL_VFO].pos.X = 40,
		[G_LABEL_VFO].pos.Y = 27,
		[G_LABEL_VFO].size.X = 2,
		[G_LABEL_VFO].isShown = 1,
		[G_LABEL_VFO].color = COLOR_WHITE,
		[G_LABEL_VFO].backColor = COLOR_BLACK,
		[G_LABEL_VFO].highlighted = 0,
		[G_LABEL_VFO].text = "",
		[G_LABEL_VFO].screen = G_SCREEN_MAIN,

	[G_LABEL_RXTX].type = G_TYPE_LABEL,
	[G_LABEL_RXTX].pos.X = 2,
	[G_LABEL_RXTX].pos.Y = 27,
	[G_LABEL_RXTX].size.X = 1,
	[G_LABEL_RXTX].isShown = 1,
	[G_LABEL_RXTX].color = COLOR_WHITE,
	[G_LABEL_RXTX].backColor = COLOR_BLACK,
	[G_LABEL_RXTX].highlighted = 0,
	[G_LABEL_RXTX].text = "Rx",
	[G_LABEL_RXTX].screen = G_SCREEN_MAIN,

	[G_LABEL_SMETER].type = G_TYPE_LABEL,
	[G_LABEL_SMETER].pos.X = 210,
	[G_LABEL_SMETER].pos.Y = 100,
	[G_LABEL_SMETER].size.X = 1,
	[G_LABEL_SMETER].isShown = 1,
	[G_LABEL_SMETER].color = COLOR_WHITE,
	[G_LABEL_SMETER].backColor = COLOR_BLACK,
	[G_LABEL_SMETER].highlighted = 0,
	[G_LABEL_SMETER].text = "S+30",
	[G_LABEL_SMETER].screen = G_SCREEN_MAIN,

	[G_SMETER].type = G_TYPE_PROGRESSBAR,
	[G_SMETER].pos.X = 2,
	[G_SMETER].pos.Y = 100,
	[G_SMETER].size.X = 200,
	[G_SMETER].size.Y = 16,
	[G_SMETER].isShown = 1,
	[G_SMETER].color = COLOR_GREEN,
	[G_SMETER].backColor = COLOR_BLACK,
	[G_SMETER].highlightable = 0,
	[G_SMETER].screen = G_SCREEN_MAIN,
	[G_SMETER].val = 0.0f,
	[G_SMETER].min = 0.0f,
	[G_SMETER].max = 100.0,




};

/*
	const int 			type;
	const Point_t 		pos;
	const Point_t 		size;
	int 		parentItem;
	bool 		isShown;
	uint16_t 	color;
	uint16_t 	backColor;
	bool 		pendUpd;
	bool		highlighted;
	bool		highlightable;
	float		val;
	char		text[GFX_ITEM_TEXT_LEN];
 */



