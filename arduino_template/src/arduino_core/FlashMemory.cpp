/*
 * FlashMemory.cpp
 *
 * Created: 7/27/2016 8:57:56 PM
 *  Author: Nate
 */ 

#include "FlashMemory.h"

int FlashMemory::init(void)
{
    uint32_t res = flash_init(FLASH_ACCESS_MODE_128, 6);
    if (res != FLASH_RC_OK) 
    {
        Serial.println("Error initializing flash!");
        return -1;
    }
    return 0;
}

int FlashMemory::eraseSector(uint32_t address, uint32_t numBytes)
{
	//offset the address to the end space so that writes to 0x00 go to the correct place in address space
	address += FLASH_START_ADDRESS;
	if(address > FLASH_END_ADDRESS)
	{
		return -1; //write was out of bounds
	}
	uint32_t res = 0;
	uint32_t tempAddress = address;
	res = flash_unlock(address, address + numBytes - 1, 0, 0);
	if (res != FLASH_RC_OK) 
	{
		Serial.println("Error erasing flash");
		return -1;
	}
	
	int numPages = (numBytes/(IFLASH0_PAGE_SIZE*32));// + 1;
	int pageCounter = 0;
	for(pageCounter = 0; pageCounter <= numPages; pageCounter++)
	{
		res = flash_erase_page(tempAddress, IFLASH_ERASE_PAGES_32);
		if (res != FLASH_RC_OK)
		{
			Serial.println("Error erasing flash");
			return -1;
		}
		tempAddress += IFLASH0_PAGE_SIZE * 32;
	}
	return 0;
}

int FlashMemory::read(uint32_t address, void* buffer, uint32_t numBytes)
{
	address += FLASH_START_ADDRESS;
	//figure out how many whole words there are to read
	uint32_t numWords = numBytes / 4;
	uint32_t remainderBytes = numBytes % 4;
	unsigned int i = 0;
	//read words
	for(; i < numWords; i++)//i+=4)
	{
		*(((uint32_t*)buffer) + i) = *(((uint32_t*)address) + i);
	}
	
	//read the remaining bytes
	uint32_t remainderByte = *(((uint32_t*)address) + i);
	for(unsigned int j = 0; j < remainderBytes; j++)
	{
		*(((uint8_t*)buffer) + (4*i) + j) = remainderByte & 0xff;
		remainderByte = remainderByte >> 8;
	}
	return 0;
}

int FlashMemory::write(uint32_t address, void* dataBuffer, uint32_t numBytes)
{
	//first handle the erase
	if(eraseSector(address, numBytes) < 0)
	{
		return -1; //error erasing, can't write
	}
    //unlock
	address += FLASH_START_ADDRESS;
    uint32_t res = 0;
    res = flash_unlock(address, address + numBytes, 0, 0);
    if (res != FLASH_RC_OK) 
	{
        return -1;
    }
    
    res = flash_write(address, dataBuffer, numBytes, 0);
    if(res != FLASH_RC_OK)
    {
        return -1;
    }
    
    //lock
    /*
    res = flash_lock(address, address + len - 1, 0, 0);
    if (res != FLASH_RC_OK)
    {
        printf("-F- Flash locking error %lu\n\r", res);
        return 0;
    }
    */
    return 0;
}

FlashMemory Flash = FlashMemory();