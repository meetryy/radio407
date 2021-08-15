#include "global.h"
#include "encoder.h"
#include "cw.h"
#include "ext_int.h"
#include <stdbool.h>

bool extIntAllowed = 0;

void extIntSet(bool in){
	extIntAllowed = in;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if (extIntAllowed){
	// external interrupt routine
		encInputCallback(GPIO_Pin);
		cwInputCallback(GPIO_Pin);
	}

}
