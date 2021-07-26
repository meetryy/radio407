#pragma once
#include <stdint.h>
#include <stdbool.h>

#define	LONGPRESS_MS			500

enum	ButtonStateAlias 	{RELEASED, PRESSED, PRESSED_LONG};
enum	ButtonAlias 		{B_ENC1, B_RIGHT, B_MID, B_LEFT, B_UPPER_RIGHT, B_UPPER_LEFT, B_ENC2, BUTTON_NR};
extern const uint16_t btnADCvalues[BUTTON_NR];

void ScanButtons (void);
void ProcessButtons(void);
void ProcessEncoder(uint8_t EncNum, int delta);
void btnUpdateFromADC(void);
void btnScan (void);
void btnTest1(void);
void btnTest2(void);

extern short Matrix_Scan_Allowed;

typedef struct {
uint8_t		State;
uint8_t 	OldState;
uint8_t		Locked;
uint8_t		HasLongPress;
uint8_t		ScreenDependent;
uint8_t		LongPress;
uint8_t		ProcessingPending;
uint16_t	StartTimer;
uint16_t	EndTimer;
void 		(*funcPtrLong)();
void 		(*funcPtrShort)();
bool 		waitForRelease;
int			test1;
int			test2;
} ButtonStruct_t;


extern ButtonStruct_t Button[BUTTON_NR];



