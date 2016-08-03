/*
 * SDCard.h
 *
 * Created: 7/29/2016 7:07:08 PM
 *  Author: Nate
 */ 


#ifndef SDCARD_H_
#define SDCARD_H_

class SDCardModule
{
	public:
		int init();
		
		int openFile(String filePath, uint8_t fileMode);
		int closeFile();
		int read(void* buffer, int bufferSizeBytes);
		int read(char* buffer, int bufferSize);
		int write(void* buffer, int bufferSizeBytes);
		int write(char* buffer, int bufferSize);
		int getFileSize();
		
	private:
	
		int makeSdPath(char* targetBuffer, const char* filePath, int filePathLength);
	
		//Fat file system vars
		Ctrl_status status;
		FRESULT res;
		FATFS fs;
		FIL file_object;
		bool fileOpen;
};


extern SDCardModule SDCard;


#endif /* SDCARD_H_ */