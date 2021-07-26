#include "global.h"
#include "gfx.h"

//gfxItemCommon_t gfxItems[GFX_ITEM_NR];

gfxItemCommon_t gfxItems[GFX_ITEM_NR] = {
	[G_DEBUG_STRING].type = G_TYPE_LABEL,
	[G_DEBUG_STRING].pos.X = 2,
	[G_DEBUG_STRING].pos.Y = 2,
	[G_DEBUG_STRING].size.X = 1,
	[G_DEBUG_STRING].isShown = 1,
	[G_DEBUG_STRING].color = COLOR_WHITE,
	[G_DEBUG_STRING].backColor = COLOR_BLACK,
	[G_DEBUG_STRING].highlighted = 0,
	[G_DEBUG_STRING].highlightable = 0,
	[G_DEBUG_STRING].text = "",
	[G_DEBUG_STRING].screen = G_SCREEN_MAIN,

	[G_VFO_VAL].type = G_TYPE_LABEL,
	[G_VFO_VAL].pos.X = 50,
	[G_VFO_VAL].pos.Y = 50,
	[G_VFO_VAL].size.X = 2,
	[G_VFO_VAL].isShown = 1,
	[G_VFO_VAL].color = COLOR_GREEN,
	[G_VFO_VAL].backColor = COLOR_BLACK,
	[G_VFO_VAL].highlighted = 0,
	[G_VFO_VAL].highlightable = 0,
	[G_VFO_VAL].text = "",
	[G_VFO_VAL].screen = G_SCREEN_MAIN,

	[G_BAR_AUDIOLOAD].type = G_TYPE_PROGRESSBAR,
	[G_BAR_AUDIOLOAD].pos.X = 5,
	[G_BAR_AUDIOLOAD].pos.Y = 100,
	[G_BAR_AUDIOLOAD].size.X = 200,
	[G_BAR_AUDIOLOAD].size.Y = 15,
	[G_BAR_AUDIOLOAD].isShown = 1,
	[G_BAR_AUDIOLOAD].color = COLOR_GREEN,
	[G_BAR_AUDIOLOAD].backColor = COLOR_BLACK,
	[G_BAR_AUDIOLOAD].highlightable = 0,
	[G_BAR_AUDIOLOAD].screen = G_SCREEN_MAIN,
	[G_BAR_AUDIOLOAD].val = 0.0f,
	[G_BAR_AUDIOLOAD].min = 0.0f,
	[G_BAR_AUDIOLOAD].max = 100.0,

	[G_BAR_ELSELOAD].type = G_TYPE_PROGRESSBAR,
	[G_BAR_ELSELOAD].pos.X = 5,
	[G_BAR_ELSELOAD].pos.Y = 120,
	[G_BAR_ELSELOAD].size.X = 200,
	[G_BAR_ELSELOAD].size.Y = 15,
	[G_BAR_ELSELOAD].isShown = 1,
	[G_BAR_ELSELOAD].color = COLOR_RED,
	[G_BAR_ELSELOAD].backColor = COLOR_BLACK,
	[G_BAR_ELSELOAD].highlightable = 0,
	[G_BAR_ELSELOAD].screen = G_SCREEN_MAIN,
	[G_BAR_ELSELOAD].val = 0.0f,
	[G_BAR_ELSELOAD].min = 0.0f,
	[G_BAR_ELSELOAD].max = 100.0f,

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



