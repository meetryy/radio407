#include "ui.h"
#include "global.h"
#include "main.h"
#include "gfx.h"
#include "fft.h"


void updateUiGfx(void){
	gfxItems[G_SMETER].val = (float)fftMagnitudesdB[1]/2;
	gfxItems[G_SMETER].pendUpd=1;

}
