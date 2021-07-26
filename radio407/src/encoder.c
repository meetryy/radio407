#include "encoder.h"
#include "global.h"

static const int8_t graydecoder [4][4] =
{
	{
		+0,		/* 00 -> 00 stopped				*/
		-1,		/* 00 -> 01 rotate left			*/
		+1,		/* 00 -> 10 rotate right		*/
		+0,		/* 00 -> 11 invalid combination */
	},
	{
		+1,		/* 01 -> 00 rotate right		*/
		+0,		/* 01 -> 01 stopped				*/
		+0,		/* 01 -> 10 invalid combination */
		-1,		/* 01 -> 11 rotate left			*/
	},
	{
		-1,		/* 10 -> 00 rotate left			*/
		+0,		/* 10 -> 01 invalid combination */
		+0,		/* 10 -> 10 stopped				*/
		+1,		/* 10 -> 11 rotate right		*/
	},
	{
		+0,		/* 11 -> 00 invalid combination */
		+1,		/* 11 -> 01 rotate right		*/
		-1,		/* 11 -> 10 rotate left			*/
		+0,		/* 11 -> 11 stopped				*/
	},
};

encoder_t encoder[ENC_NR] = {
		[ENC_UPPER].isReversed = 0,
		[ENC_UPPER].pins[0] = GPIO_PIN_10,
		[ENC_UPPER].pins[1] = GPIO_PIN_11,
		[ENC_UPPER].port = GPIOE,
		[ENC_UPPER].divider = 2,

		[ENC_LOWER].isReversed = 0,
		[ENC_LOWER].pins[0] = GPIO_PIN_12,
		[ENC_LOWER].pins[1] = GPIO_PIN_13,
		[ENC_LOWER].port = GPIOE,
		[ENC_UPPER].divider = 2,
};


void encInputRoutine(void){

	//bool result = GPIOA->regs->IDR & 0x0004;

	encoder_t* e;
	for (int i=0; i<ENC_NR; i++){
		e = &encoder[i];
		bool a = HAL_GPIO_ReadPin(e->port, e->pins[0]);
		bool b = HAL_GPIO_ReadPin(e->port, e->pins[1]);

		e->phaseState = (a << 1) | (b);
		if (e->isReversed) 	e->deltaRaw -= graydecoder[e->phaseOldState][e->phaseState];
		else 				e->deltaRaw += graydecoder[e->phaseOldState][e->phaseState];
		e->delta = e->deltaRaw / e->divider;
		e->phaseOldState = e->phaseState;
	}
}
