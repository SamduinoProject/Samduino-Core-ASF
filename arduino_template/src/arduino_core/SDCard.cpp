/*
 * SDCard.cpp
 *
 * Created: 7/29/2016 7:07:45 PM
 *  Author: Nate
 */ 

#include "SDCard.h"

char filePathBuffer[256];

int SDCardModule::init()
{
	//need to init the sd card stack
	sd_mmc_init();
	
	//look for card detect
	do
	{
		status = sd_mmc_test_unit_ready(0);
		if (CTRL_FAIL == status)
		{
			//printf("Card install FAIL\n\r");
			//printf("Please unplug and re-plug the card.\n\r");
			while (CTRL_NO_PRESENT != sd_mmc_check(0))
			{
				sd_mmc_init();
			}
		}
	} while (CTRL_GOOD != status);
	
	//mount the card on  the fat file system
	memset(&fs, 0, sizeof(FATFS));
	res = f_mount(LUN_ID_SD_MMC_0_MEM, &fs);
	if (FR_INVALID_DRIVE == res) 
	{
		return -1;
	}
	
	
	fileOpen = false;
	
	return 0;
}

int SDCardModule::openFile(String filePath, uint8_t fileMode)
{
	makeSdPath(filePathBuffer, filePath.c_str(), filePath.length());
	res = f_open(&file_object, (char const*)filePathBuffer, fileMode);
	if(res != FR_OK)
	{
		return -1;
	}
	else
	{
		fileOpen = true;
		return 0;
	}
}

int SDCardModule::closeFile()
{
	f_close(&file_object);
	fileOpen = false;
	return 0;
}

int SDCardModule::read(void* buffer, int bufferSizeBytes)
{
	if(!fileOpen)
	{
		return -1; //error no file open
	}
	
	UINT bytesRead = 0;
	f_read(&file_object, buffer, bufferSizeBytes, &bytesRead);
	return bytesRead;
}

int SDCardModule::read(char* buffer, int bufferSize)
{
	return read((uint8_t*)buffer, bufferSize);
}

int SDCardModule::write(void* buffer, int bufferSizeBytes)
{
	if(!fileOpen)
	{
		return -1; //file not open
	}
	UINT bytesRead = 0;
	f_write(&file_object, buffer, bufferSizeBytes, &bytesRead);
	return bytesRead;
}

int SDCardModule::write(char* buffer, int bufferSize)
{
	return write((uint8_t*)buffer, bufferSize);
}

int SDCardModule::makeSdPath(char* targetBuffer, const char* filePath, int filePathLength)
{
	//first two characters need to be "0:"
	targetBuffer[0] = '0';
	targetBuffer[0] = LUN_ID_SD_MMC_0_MEM + '0';
	targetBuffer[1] = ':';
	strncpy(&targetBuffer[2], filePath, filePathLength);
	targetBuffer[filePathLength+2] = '\0';
	
	return 0;
}

int SDCardModule::getFileSize()
{
	if(!fileOpen)
	{
		return -1;
	}
	return f_size(&file_object);
}

SDCardModule SDCard = SDCardModule();