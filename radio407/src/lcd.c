#include "lcd.h"
#include "fft.h"

#include "tools.h"
#include "soft_sched.h"
//#include "gfx.h"

ili9341_t *_screen;
ili9341_t *screen(void) {return _screen;}

void LCDinit(void){
  _screen = ili9341_new(
	  HSPI_INSTANCE,
	  LCD_RST_PORT,   LCD_RST_PIN,
	  LCD_CS_PORT,    LCD_CS_PIN,
	  LCD_DC_PORT,    LCD_DC_PIN,
	  isoLandscape,
	  0,  	0,
	  0, 	0,
	  itsNotSupported,
	  itnNormalized);

  ili9341_fill_screen(_screen, ILI9341_BLACK);
}

void LCDtestDraw(void){
	//ili9341_draw_line(_screen, rand()%((2<<16)-1), rand()%320, rand()%240, rand()%320, rand()%240);
	int w=128*2;
	int h=60;

	uint16_t d[h*w];
	for (int i=0; i<(h*w);i+=4){
		d[i]=ILI9341_BLUE;
		d[i+1]=ILI9341_BLUE;
		d[i+2]=ILI9341_GREEN;
		d[i+3]=ILI9341_GREEN;
	}
	ili9341_fill_data(_screen, ILI9341_WHITE, 120, 180, w, h, d);
}

void LCDdrawIndicator(int isOn){
	ili9341_fill_rect(_screen, ILI9341_GREEN*isOn + ILI9341_BLACK*!isOn , 10, 240-20, 10, 10);
}

#include "fir.h"

/*
void LCDdrawFFT(void){
	int number = FFT_LEN;

	int FFTy0= 100;

	int	lineH = 100;
	int lineW = 320 / number;

	for (int i=0; i<number; i++){
		int thisLineH = (int)((float)lineH * mags[i]);
		//ili9341_draw_rect(_screen, ILI9341_WHITE, number*lineW, fftH, lineW, lineH);
		//ili9341_draw_rect(_screen, ILI9341_WHITE, number*lineW, fftH, lineW, thisLineH);
		ili9341_draw_line(_screen, ILI9341_BLACK, i, FFTy0, i, FFTy0+lineH);
		ili9341_draw_line(_screen, ILI9341_WHITE, i, FFTy0+thisLineH, i, FFTy0);
	}

	ili9341_draw_rect(_screen, ILI9341_WHITE, 1, 10, 300, 150);

}
*/

void LCDdebugText(char* text){
/*
	uint32_t timeNow = HAL_GetTick();

	char timBuf[32];
	sprintf(timBuf, "+%u ms: ", timeNow - 0);

	char txtBuf[128];
    va_list args;
    va_start(args, fmt);
    int rc = vsnprintf(txtBuf, sizeof(txtBuf), fmt, args);
    va_end(args);

	char nlBuf[] = {"\r\n"};

	char* output;
	output = malloc(strlen(timBuf) + strlen(txtBuf) + strlen(nlBuf) + 1);
	strcpy(output, timBuf);
	strcat(output, txtBuf);
	strcat(output, nlBuf);


	0 = timeNow;



	free(output);

*/



}

/*


typedef struct
{
  ili9341_font_t const *font;
  ili9341_color_t fg_color;
  ili9341_color_t bg_color;
  uint16_t origin_x;
  uint16_t origin_y;
}
ili9341_text_attr_t;

void ili9341_draw_string(ili9341_t *lcd, ili9341_text_attr_t attr, char str[]);
 */
