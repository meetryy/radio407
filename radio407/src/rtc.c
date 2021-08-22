#include "rtc.h"
#include "global.h"

#include <stdbool.h>
#include <stdint.h>


void rtcInit(void){
	TM_RTC_t RTCD;

	// if RTC isnt running
	if (!TM_RTC_Init(TM_RTC_ClockSource_External)) {
		RTCD.Day = 01;
		RTCD.Month = 01;
		RTCD.Year = 21;
		RTCD.WeekDay = 5;
		RTCD.Hours = 12;
		RTCD.Minutes = 00;
		RTCD.Seconds = 00;

		/* Save new date and time */
		TM_RTC_SetDateTime(&RTCD, TM_RTC_Format_BIN);
	}


	TM_RTC_Interrupts(TM_RTC_Int_1s);
}

/* Private macros */
/* Internal status registers for RTC */

#define RTC_STATUS_REG      			RTC_BKP_DR19 /* Status Register */
#define RTC_STATUS_INIT_OK              0x1234       /* RTC initialised */
#define RTC_STATUS_TIME_OK              0x4321       /* RTC time OK */
#define	RTC_STATUS_ZERO                 0x0000

/* Internal RTC defines */
#define RTC_LEAP_YEAR(year)             ((((year) % 4 == 0) && ((year) % 100 != 0)) || ((year) % 400 == 0))
#define RTC_DAYS_IN_YEAR(x)             RTC_LEAP_YEAR(x) ? 366 : 365
#define RTC_OFFSET_YEAR                 1970
#define RTC_SECONDS_PER_DAY             86400
#define RTC_SECONDS_PER_HOUR            3600
#define RTC_SECONDS_PER_MINUTE          60

/* Internal functions */
//static void TM_RTC_Config(TM_RTC_ClockSource_t source);

/* RTC Handle */
static RTC_HandleTypeDef 	hRTC;
static RTC_DateTypeDef 		RTC_DateStruct;
static RTC_TimeTypeDef 		RTC_TimeStruct;

/* Days in a month */
static uint8_t RTC_Months[2][12] = {
	{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},	/* Not leap year */
	{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}	/* Leap year */
};

RTC_TimeTypeDef rtcGettime(void){
	HAL_RTC_GetTime(&hRTC, &RTC_TimeStruct, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hRTC, &RTC_DateStruct, RTC_FORMAT_BIN);
	return RTC_TimeStruct;
}

uint32_t TM_RTC_Init(TM_RTC_ClockSource_t source) {
	uint32_t status;
	TM_RTC_t datatime;

	/* Set instance */
	hRTC.Instance = RTC;
	hRTC.Init.AsynchPrediv = RTC_ASYNC_PREDIV;
	hRTC.Init.SynchPrediv = RTC_SYNC_PREDIV;
	hRTC.Init.HourFormat = RTC_HOURFORMAT_24;
	hRTC.Init.OutPut = RTC_OUTPUT_DISABLE;
	hRTC.Init.OutPutType = RTC_OUTPUT_TYPE_PUSHPULL;
	hRTC.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;

	/* Enable PWR peripheral clock */
	__HAL_RCC_PWR_CLK_ENABLE();

	/* Allow access to BKP Domain */
	HAL_PWR_EnableBkUpAccess();

	/* Get RTC status */
	status = HAL_RTCEx_BKUPRead(&hRTC, RTC_STATUS_REG);

	/* Check if RTC already initialized */
	if (status == RTC_STATUS_TIME_OK) {

		/* Wait for RTC APB registers synchronisation (needed after start-up from Reset) */
		HAL_RTC_WaitForSynchro(&hRTC);

		/* Get date and time */
		TM_RTC_GetDateTime(&datatime, TM_RTC_Format_BIN);

		/* Clear reset flags */
		__HAL_RCC_CLEAR_RESET_FLAGS();

		/* Return OK */
		return 1;
	} else {
		/* Start RTC clock */
		//TM_RTC_Config(source);

		/* Set date */
		RTC_DateStruct.Year = 0;
		RTC_DateStruct.Month = 1;
		RTC_DateStruct.Date = 1;
		RTC_DateStruct.WeekDay = RTC_WEEKDAY_TUESDAY;

		/* Set date */
		HAL_RTC_SetDate(&hRTC, &RTC_DateStruct, RTC_FORMAT_BIN);

		/* Set time */
		RTC_TimeStruct.Hours = 0x00;
		RTC_TimeStruct.Minutes = 0x00;
		RTC_TimeStruct.Seconds = 0x00;
		RTC_TimeStruct.TimeFormat = RTC_HOURFORMAT_24;
		RTC_TimeStruct.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
		RTC_TimeStruct.StoreOperation = RTC_STOREOPERATION_RESET;

		/* Set time */
		HAL_RTC_SetTime(&hRTC, &RTC_TimeStruct, RTC_FORMAT_BCD);

		/* Init RTC */
		HAL_RTC_Init(&hRTC);

		/* Save data to backup regiser */
		HAL_RTCEx_BKUPWrite(&hRTC, RTC_STATUS_REG, RTC_STATUS_TIME_OK);

		/* RTC was initialized now */
		return 0;
	}
}

TM_RTC_Result_t TM_RTC_SetDateTime(TM_RTC_t* data, TM_RTC_Format_t format) {
	TM_RTC_t tmp;

	// Check date and time validation
		tmp.Day = data->Day;
		tmp.Month = data->Month;
		tmp.Year = data->Year;
		tmp.Hours = data->Hours;
		tmp.Minutes = data->Minutes;
		tmp.Seconds = data->Seconds;
		tmp.WeekDay = data->WeekDay;

	// Check year and month
	if (
		tmp.Year > 99 ||
		tmp.Month == 0 ||
		tmp.Month > 12 ||
		tmp.Day == 0 ||
		tmp.Day > RTC_Months[RTC_LEAP_YEAR(2000 + tmp.Year) ? 1 : 0][tmp.Month - 1] ||
		tmp.Hours > 23 ||
		tmp.Minutes > 59 ||
		tmp.Seconds > 59
		//tmp.WeekDay == 0 ||
		//tmp.WeekDay > 7
	) {
		//return TM_RTC_Result_Error;
	}

	// Fill time
	RTC_TimeStruct.Hours = data->Hours;
	RTC_TimeStruct.Minutes = data->Minutes;
	RTC_TimeStruct.Seconds = data->Seconds;

	// Fill date
	RTC_DateStruct.Date = data->Day;
	RTC_DateStruct.Month = data->Month;
	RTC_DateStruct.Year = data->Year;
	RTC_DateStruct.WeekDay = data->WeekDay;

	//Set time
		HAL_RTC_SetTime(&hRTC, &RTC_TimeStruct, RTC_FORMAT_BIN);

	// Set date
		HAL_RTC_SetDate(&hRTC, &RTC_DateStruct, RTC_FORMAT_BIN);

	// Init RTC
	HAL_RTC_Init(&hRTC);

	/* Return OK */
	return TM_RTC_Result_Ok;
}

TM_RTC_Result_t TM_RTC_GetDateTime(TM_RTC_t* data, TM_RTC_Format_t format) {
	HAL_RTC_GetTime(&hRTC, &RTC_TimeStruct, RTC_FORMAT_BCD);

	//Format hours
	data->Hours = RTC_TimeStruct.Hours;
	data->Minutes = RTC_TimeStruct.Minutes;
	data->Seconds = RTC_TimeStruct.Seconds;

	//Get subseconds
	data->Subseconds = RTC->SSR;

	HAL_RTC_GetDate(&hRTC, &RTC_DateStruct, RTC_FORMAT_BCD);

	// Format date
	data->Year = RTC_DateStruct.Year;
	data->Month = RTC_DateStruct.Month;
	data->Day = RTC_DateStruct.Date;
	data->WeekDay = RTC_DateStruct.WeekDay;

	return TM_RTC_Result_Ok;
}

/*
uint8_t TM_RTC_GetDaysInMonth(uint8_t month, uint8_t year) {
	if (month == 0 || month > 12)
		return 0;

	return RTC_Months[RTC_LEAP_YEAR(2000 + year) ? 1 : 0][month - 1];
}


uint16_t TM_RTC_GetDaysInYear(uint8_t year) {
	// Return days in year
	return RTC_DAYS_IN_YEAR(2000 + year);
}
*/


TM_RTC_Result_t TM_RTC_Interrupts(TM_RTC_Int_t int_value) {
	uint32_t int_val;

	/* Disable wakeup interrupt */
	__HAL_RTC_WAKEUPTIMER_DISABLE(&hRTC);

	/* Disable RTC interrupt flag */
	__HAL_RTC_WAKEUPTIMER_DISABLE_IT(&hRTC, RTC_IT_WUT);

	/* Clear pending bit */
	__HAL_RTC_WAKEUPTIMER_EXTI_CLEAR_FLAG();

	/* Clear flag */
	__HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(&hRTC, RTC_FLAG_WUTF);

	/* If enable again */
	if (int_value != TM_RTC_Int_Disable) {
		if (int_value == TM_RTC_Int_60s) {
			int_val = 0x3BFFF; 		/* 60 seconds = 60 * 4096 / 1 = 245760 */
		} else if (int_value == TM_RTC_Int_30s) {
			int_val = 0x1DFFF;		/* 30 seconds */
		} else if (int_value == TM_RTC_Int_15s) {
			int_val = 0xEFFF;		/* 15 seconds */
		} else if (int_value == TM_RTC_Int_10s) {
			int_val = 0x9FFF;		/* 10 seconds */
		} else if (int_value == TM_RTC_Int_5s) {
			int_val = 0x4FFF;		/* 5 seconds */
		} else if (int_value == TM_RTC_Int_2s) {
			int_val = 0x1FFF;		/* 2 seconds */
		} else if (int_value == TM_RTC_Int_1s) {
			int_val = 0x0FFF;		/* 1 second */
		} else if (int_value == TM_RTC_Int_500ms) {
			int_val = 0x7FF;		/* 500 ms */
		} else if (int_value == TM_RTC_Int_250ms) {
			int_val = 0x3FF;		/* 250 ms */
		} else if (int_value == TM_RTC_Int_125ms) {
			int_val = 0x1FF;		/* 125 ms */
		}

		/* Clock divided by 8, 32768 / 8 = 4096 */
		/* 4096 ticks for 1second interrupt */
		HAL_RTCEx_SetWakeUpTimer_IT(&hRTC, int_val, RTC_WAKEUPCLOCK_RTCCLK_DIV8);

		/* Set NVIC */
		HAL_NVIC_SetPriority(RTC_WKUP_IRQn, RTC_NVIC_PRIORITY, RTC_NVIC_WAKEUP_SUBPRIORITY);
		HAL_NVIC_EnableIRQ(RTC_WKUP_IRQn);
	}

	/* Return OK */
	return TM_RTC_Result_Ok;
}


/* Private RTC IRQ handlers */
void RTC_WKUP_IRQHandler(void) {
	/* Check for RTC interrupt */
	if (__HAL_RTC_WAKEUPTIMER_GET_IT(&hRTC, RTC_IT_WUT) != RESET) {
		/* Call user function */
		TM_RTC_WakeupHandler();

		/* Clear interrupt flags */
		__HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(&hRTC, RTC_FLAG_WUTF);
	}

	/* Clear EXTI line 22 bit */
	__HAL_RTC_WAKEUPTIMER_EXTI_CLEAR_FLAG();
};

RTC_TimeTypeDef rtcTime;

__weak void TM_RTC_WakeupHandler(void) {
	/* If user needs this function, then they should be defined separatelly in your project */
	rtcTime = rtcGettime();
}
