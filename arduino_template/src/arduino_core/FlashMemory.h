/*
 * FlashMemory.h
 *
 * Created: 7/27/2016 8:57:45 PM
 *  Author: Nate
 */ 


#ifndef FLASHMEMORY_H_
#define FLASHMEMORY_H_

//size of the flash area that can be accessed by the Flash module in bytes
#define FLASH_SIZE						8192

//using the upper end of the flash address range
#define FLASH_START_ADDRESS				(IFLASH0_ADDR + IFLASH0_SIZE - FLASH_SIZE)
#define FLASH_END_ADDRESS				(FLASH_START_ADDRESS + FLASH_SIZE)

#ifdef __cplusplus

class FlashMemory
{
	public:
		int init();

		//erase a sector starting at address and extending len bytes.
		int eraseSector(uint32_t address, uint32_t numBytes);
		
		//read from flash the number of bytes specified at the address and into buffer
		int read(uint32_t address, void* buffer, uint32_t numBytes);

		//write to flash.
		int write(uint32_t address, void* dataBuffer, uint32_t numBytes);
	
	private:	
};

extern FlashMemory Flash;

#endif //__cplusplus
#endif /* FLASHMEMORY_H_ */