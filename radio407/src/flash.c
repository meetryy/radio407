#include "flash.h"
#include "global.h"
#include "main.h"
#include "spi.h"

SPI_HandleTypeDef				hspi1;
#define FLASH_SPI_HANDLE		&hspi1

#define	FLASH_CS_PORT	GPIOB
#define	FLASH_CS_PIN	GPIO_PIN_0

#define DUMMY 				0
#define MANUFACTURER_ID 	0x90
#define RELEASE_POWER_DOWN 	0xAB

flash_t	flash;

uint8_t	flashSPIsingleByte(uint8_t	txData)
{
	uint8_t txHere = txData;
	uint8_t	rxData;
	//while (spiBusy){};
	//if (!spiBusy){
		//spiBusy = 1;
		HAL_SPI_TransmitReceive(FLASH_SPI_HANDLE, &txHere, &rxData, 1, 1);
		//spiBusy = 0;
	//}
	return rxData;
}


uint32_t flashBlockCount = 0;

void flashInit(void){
	HAL_GPIO_WritePin(FLASH_CS_PORT, FLASH_CS_PIN, GPIO_PIN_SET);
	HAL_Delay(50);

	flash.ID = flashReadID();

	//HAL_Delay(100);

	//uint32_t thisID =
	flash.BlockCount = (1 << (flash.ID & 0x0F));
	flash.PageSize = 256;
	flash.SectorSize = 0x1000;
	flash.SectorCount = flash.BlockCount * 16;
	flash.PageCount = (flash.SectorCount * flash.SectorSize) / flash.PageSize;
	flash.BlockSize = flash.SectorSize * 16;
	flash.CapacityInKiloByte = (flash.SectorCount * flash.SectorSize) / 1024;

	flashReadUID();
	flashReadJEDEC();



	//uint32_t chipID = thisID;// & 0x000000FF;
	//flashBlockCount = chipID;//(1 << (chipID - 0x10 - 1));


}

void flashWriteEnable(void) {
	HAL_GPIO_WritePin(FLASH_CS_PORT, FLASH_CS_PIN, GPIO_PIN_RESET);
		flashSPIsingleByte(0x06);
	HAL_GPIO_WritePin(FLASH_CS_PORT, FLASH_CS_PIN, GPIO_PIN_SET);
	HAL_Delay(1);
}

void flashWait(void)
{
	//W25qxx_Delay(1);
	HAL_GPIO_WritePin(FLASH_CS_PORT, FLASH_CS_PIN, GPIO_PIN_RESET);
		flashSPIsingleByte(0x05);
		do {
			flash.StatusRegister1 = flashSPIsingleByte(DUMMY);
			//W25qxx_Delay(1);
		}
		while ((flash.StatusRegister1 & 0x01) == 0x01);
	HAL_GPIO_WritePin(FLASH_CS_PORT, FLASH_CS_PIN, GPIO_PIN_SET);
}

void flashEraseSector(int SectorAddr){
	flashWait();
	SectorAddr = SectorAddr * flash.SectorSize;
	flashWriteEnable();
	HAL_GPIO_WritePin(FLASH_CS_PORT, FLASH_CS_PIN,GPIO_PIN_RESET);
		flashSPIsingleByte(0x20);
		flashSPIsingleByte((SectorAddr & 0xFF0000) >> 16);
		flashSPIsingleByte((SectorAddr & 0xFF00) >> 8);
		flashSPIsingleByte(SectorAddr & 0xFF);
	HAL_GPIO_WritePin(FLASH_CS_PORT, FLASH_CS_PIN,GPIO_PIN_SET);
	flashWait();
}


uint32_t	flashSectorToPage(uint32_t	SectorAddress){
	return (SectorAddress * flash.SectorSize) / flash.PageSize;
}

void 	flash_WritePage(uint8_t *pBuffer,
						uint32_t Page_Address,
						uint32_t OffsetInByte,
						uint32_t NumByteToWrite_up_to_PageSize){

	if(((NumByteToWrite_up_to_PageSize+OffsetInByte)>flash.PageSize)||(NumByteToWrite_up_to_PageSize==0))
		NumByteToWrite_up_to_PageSize=flash.PageSize-OffsetInByte;

	if((OffsetInByte+NumByteToWrite_up_to_PageSize) > flash.PageSize)
		NumByteToWrite_up_to_PageSize = flash.PageSize-OffsetInByte;

	flashWait();
	flashWriteEnable();

	HAL_GPIO_WritePin(FLASH_CS_PORT,FLASH_CS_PIN,GPIO_PIN_RESET);
		flashSPIsingleByte(0x02);
		Page_Address = (Page_Address*flash.PageSize)+OffsetInByte;

		flashSPIsingleByte((Page_Address & 0xFF0000) >> 16);
		flashSPIsingleByte((Page_Address & 0xFF00) >> 8);
		flashSPIsingleByte(Page_Address&0xFF);
		HAL_SPI_Transmit(FLASH_SPI_HANDLE, pBuffer, NumByteToWrite_up_to_PageSize, 1);
	HAL_GPIO_WritePin(FLASH_CS_PORT,FLASH_CS_PIN,GPIO_PIN_SET);
	flashWait();
	//flash_Delay(1);

}

uint32_t	flsahSectorToPage(uint32_t	SectorAddress)
{
	return (SectorAddress*flash.SectorSize)/flash.PageSize;
}


void flashWriteSector(	uint8_t *pBuffer,
						uint32_t Sector_Address,
						uint32_t OffsetInByte,
						uint32_t NumByteToWrite_up_to_SectorSize){
	if((NumByteToWrite_up_to_SectorSize>flash.SectorSize)||(NumByteToWrite_up_to_SectorSize==0))
		NumByteToWrite_up_to_SectorSize=flash.SectorSize;

	if(OffsetInByte>=flash.SectorSize){
		return;
	}

	uint32_t	StartPage;
	int32_t		BytesToWrite;
	uint32_t	LocalOffset;
	if((OffsetInByte+NumByteToWrite_up_to_SectorSize) > flash.SectorSize)
		BytesToWrite = flash.SectorSize - OffsetInByte;
	else
		BytesToWrite = NumByteToWrite_up_to_SectorSize;

	StartPage = flsahSectorToPage(Sector_Address) + (OffsetInByte / flash.PageSize);
	LocalOffset = OffsetInByte % flash.PageSize;

	do
	{
		flash_WritePage(pBuffer,StartPage,LocalOffset,BytesToWrite);
		StartPage++;
		BytesToWrite-=flash.PageSize-LocalOffset;
		pBuffer += flash.PageSize - LocalOffset;
		LocalOffset=0;
	} while (BytesToWrite > 0);
}

void 	flash_ReadPage(uint8_t *pBuffer,
						uint32_t Page_Address,
						uint32_t OffsetInByte,
						uint32_t NumByteToRead_up_to_PageSize){

	if((NumByteToRead_up_to_PageSize>flash.PageSize)||(NumByteToRead_up_to_PageSize==0))
		NumByteToRead_up_to_PageSize=flash.PageSize;

	if((OffsetInByte+NumByteToRead_up_to_PageSize) > flash.PageSize)
		NumByteToRead_up_to_PageSize = flash.PageSize-OffsetInByte;

	Page_Address = Page_Address * flash.PageSize + OffsetInByte;
	HAL_GPIO_WritePin(FLASH_CS_PORT, FLASH_CS_PIN, GPIO_PIN_RESET);
		flashSPIsingleByte(0x0B);
		flashSPIsingleByte((Page_Address & 0xFF0000) >> 16);
		flashSPIsingleByte((Page_Address & 0xFF00) >> 8);
		flashSPIsingleByte(Page_Address & 0xFF);
		flashSPIsingleByte(0);
		HAL_SPI_Receive(FLASH_SPI_HANDLE, pBuffer, NumByteToRead_up_to_PageSize, 1);
	HAL_GPIO_WritePin(FLASH_CS_PORT, FLASH_CS_PIN, GPIO_PIN_SET);
}



void 	flashReadSector(uint8_t *pBuffer,
						uint32_t Sector_Address,
						uint32_t OffsetInByte,
						uint32_t NumByteToRead_up_to_SectorSize){

	if((NumByteToRead_up_to_SectorSize>flash.SectorSize)||(NumByteToRead_up_to_SectorSize == 0))
		NumByteToRead_up_to_SectorSize=flash.SectorSize;
	if(OffsetInByte>=flash.SectorSize) {return;}

	uint32_t	StartPage;
	int32_t		BytesToRead;
	uint32_t	LocalOffset;
	if((OffsetInByte+NumByteToRead_up_to_SectorSize) > flash.SectorSize)
		BytesToRead = flash.SectorSize-OffsetInByte;
	else
		BytesToRead = NumByteToRead_up_to_SectorSize;
	StartPage = flashSectorToPage(Sector_Address)+(OffsetInByte/flash.PageSize);
	LocalOffset = OffsetInByte%flash.PageSize;
	do
	{
		flash_ReadPage(pBuffer,StartPage,LocalOffset,BytesToRead);
		StartPage++;
		BytesToRead-=flash.PageSize-LocalOffset;
		pBuffer += flash.PageSize - LocalOffset;
		LocalOffset=0;
	} while (BytesToRead > 0);
}

void flashWriteFloatToAddr(float input, int offsetInFloats){
	uint8_t rxSector[flash.SectorSize];
	int addrInArray = offsetInFloats * 4;

	int floatIsinSector = addrInArray / flash.SectorSize;
	flashReadSector(rxSector, floatIsinSector, 0, flash.SectorSize);

	uint32_t inInt = (uint32_t)input;
	rxSector[addrInArray] = 	(inInt && 0xFF);
	rxSector[addrInArray + 1] = ((inInt >> 8)  && 0xFF);
	rxSector[addrInArray + 2] = ((inInt >> 16) && 0xFF);
	rxSector[addrInArray * 3] = ((inInt >> 24) && 0xFF);
}

uint32_t flashBlockSize(void){
	return ((uint32_t)flashBlockCount);
}

uint32_t flashReadID(void) {
	  uint32_t Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;
	  HAL_GPIO_WritePin(FLASH_CS_PORT, FLASH_CS_PIN, GPIO_PIN_RESET);

	  flashSPIsingleByte(0x9F);
	  Temp0 = flashSPIsingleByte(DUMMY);
	  Temp1 = flashSPIsingleByte(DUMMY);
	  Temp2 = flashSPIsingleByte(DUMMY);

	  HAL_GPIO_WritePin(FLASH_CS_PORT,FLASH_CS_PIN, GPIO_PIN_SET);
	  Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;

	  return Temp;
}

void flashReadUID(void) {

  HAL_GPIO_WritePin(FLASH_CS_PORT,FLASH_CS_PIN,GPIO_PIN_RESET);
  flashSPIsingleByte(0x4B);

	for(uint8_t	i=0;i<4;i++)
	flashSPIsingleByte(DUMMY);

	for(uint8_t	i=0;i<8;i++)
	flash.UniqID[i] = flashSPIsingleByte(DUMMY);


  HAL_GPIO_WritePin(FLASH_CS_PORT,FLASH_CS_PIN,GPIO_PIN_SET);


 //debugPrintFast("%02X %02X %02X %02X %02X %02X %02X %02X", 	flash.UniqID[0], flash.UniqID[1], flash.UniqID[2], flash.UniqID[3],
  //																flash.UniqID[4], flash.UniqID[5], flash.UniqID[6], flash.UniqID[7]);

}


void flashReadJEDEC(void){
  HAL_GPIO_WritePin(FLASH_CS_PORT, FLASH_CS_PIN, GPIO_PIN_RESET);
	  flashSPIsingleByte(0x9F);
	  flash.jM = flashSPIsingleByte(DUMMY);
	  flash.jID = flashSPIsingleByte(DUMMY);
	  flash.jC = flashSPIsingleByte(DUMMY);
  HAL_GPIO_WritePin(FLASH_CS_PORT, FLASH_CS_PIN, GPIO_PIN_SET);

}
