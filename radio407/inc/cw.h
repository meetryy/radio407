#pragma once 
#include <stdint.h>
#include <stdbool.h>

extern struct CW_t{
	int			speedWPM; // speed in WPM
	int			paddleState;
	int			paddleOldState;
	int			paddleInput;
	int			paddleOldInput;
	uint16_t	timerHz; // timer frequency
	uint32_t	timerTicksPerDot;
	uint32_t	timerCounter;
	bool		txState;
	uint8_t		sendQueue;
	bool 		paddlesReversed;
	int 		msgLenLeftInBuf;

} CW;

void cwChangeSpeed(int newWPM);
void cwInit(void);
void cwReadPaddles(void);
void cwTimerRoutine(void);
void cwInputCallback(uint16_t GPIO_Pin);


