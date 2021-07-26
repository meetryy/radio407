#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef struct {
int X;
int Y;
} Point_t;

enum gfxItemList {
	G_DEBUG_STRING,
	G_TEST_FLOAT,
	G_VFO_VAL,
	G_BAR,
	G_BAR_AUDIOLOAD,
	G_BAR_ELSELOAD,
	GFX_ITEM_NR
};

enum gfxItemTypes {
	G_TYPE_LABEL,
	G_TYPE_PROGRESSBAR,
	G_TYPE_INDICATOR,
	G_TYPE_WINDOW,
};

enum gfxScreens {
	G_SCREEN_MAIN,
	G_SCREEN_NR
};

enum gfxItemFlags{
	G_FLAG_BAR_SHAPE = 1,
	G_FLAG1 = 2,
	G_FLAG2 = 4,
	G_FLAG3 = 8,
	G_FLAG4 = 16,
	G_FLAG5 = 32,
	G_FLAG6 = 64,
	G_FLAG7 = 128
};

#define	GFX_ITEM_TEXT_LEN 32

typedef struct {
const int 			type;
const Point_t 		pos;
const Point_t 		size;
const int			screen;
int 		parentItem;
bool 		isShown;
uint16_t 	color;
uint16_t 	backColor;
bool 		pendUpd;
bool		highlighted;
bool		highlightable;
float		val;
float		min;
float		max;
float		oldVal;
char		text[GFX_ITEM_TEXT_LEN];
int 		flags;
} gfxItemCommon_t;


extern gfxItemCommon_t gfxItems[GFX_ITEM_NR];

void gfxItemsInit(void);
void gfxItemsRedraw(void);
void gfxLabelSet(int itemID, const char *fmt, ...);
void gfxBarSet(int itemID, float value);

Point_t Point(int X, int Y);

#define COLOR_BLACK         0x0000
#define COLOR_NAVY          0x000F
#define COLOR_DARKGREEN     0x03E0
#define COLOR_DARKCYAN      0x03EF
#define COLOR_MAROON        0x7800
#define COLOR_PURPLE        0x780F
#define COLOR_OLIVE         0x7BE0
#define COLOR_LIGHTGREY     0xC618
#define COLOR_DARKGREY      0x7BEF
#define COLOR_BLUE          0x001F
#define COLOR_GREEN         0x07E0
#define COLOR_CYAN          0x07FF
#define COLOR_RED           0xF800
#define COLOR_MAGENTA       0xF81F
#define COLOR_YELLOW        0xFFE0
#define COLOR_WHITE         0xFFFF
#define COLOR_ORANGE        0xFD20
#define COLOR_GREENYELLOW   0xAFE5
#define COLOR_PINK        	0xF81F


