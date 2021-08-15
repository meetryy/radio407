#pragma once
#include <stdbool.h>
#include "global.h"

extern long done;
extern bool uartTxDone;
extern uint32_t testInt[5];

enum {COLOR_RED, COLOR_GREEN, COLOR_BLUE};

extern int upperHalf;
extern int lowerHalf;
extern uint32_t preciseTimerCounter;

extern float audioLoad;
extern float everythingElseLoad;


UART_HandleTypeDef* dbgUartPtr;

void dbgTx(char* text, int len);

void debugPrintColor(int color, const char *fmt, ...);
void debugPrint(const char *fmt, ...);
void debugClearTerminal(void);
void debugPrintFast(const char *fmt, ...);

void testMethod(void);
float msPerOperation(int times);

void debugPinInit(void);
void debugPinSet(bool i);
void debugInit(void);


