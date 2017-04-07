#include "SerialClass.h"

Serial::Serial(const char *portName)
{
	//Not yet connected
	this->connected = false;

	//Try connecting with CreateFile
    this->hSerial = CreateFileA(portName,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	//Check if connection was successfull
	if (this->hSerial == INVALID_HANDLE_VALUE)
	{
		//Connection failed, show errors
		if (GetLastError() == ERROR_FILE_NOT_FOUND)
		{
			printf("ERROR: Handle was not attached. Reason %s not available.\n", portName);
		}
		else
		{
			printf("ERROR");
		}
	}
	else
	{
		//Connection was ok, set the comm params
		DCB dcbSerialParams = { 0 };

		if (!GetCommState(this->hSerial, &dcbSerialParams))
		{
			printf("Failed to get current serial parameters");
		}
		else
		{
			//Define serial connection parameters for arduino board
			dcbSerialParams.BaudRate = CBR_9600;
			dcbSerialParams.ByteSize = 8;
			dcbSerialParams.StopBits = ONESTOPBIT;
			dcbSerialParams.Parity = NOPARITY;

			//Setting the DTR to Control_Enable ensures that Arduino is properly
			//reset upon establishing connection
			dcbSerialParams.fDtrControl = DTR_CONTROL_ENABLE;

			//Set the parameters and check them
			if (!SetCommState(hSerial, &dcbSerialParams))
			{
				printf("ALERT: Could not set Serial Port parameters");
			}
			else
			{
				//All ok
				this->connected = true;
				//Flush any remaining characters in the buffers
				PurgeComm(this->hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR);
				//Wait 2s as the arduino board will be resetting
				Sleep(ARDUINO_WAIT_TIME);
			}
		}
	}
}
Serial::~Serial()
{
	//If connected, close handle
	if (this->connected)
	{
		this->connected = false;
		CloseHandle(this->hSerial);
	}
}

int Serial::ReadData(char *buffer, unsigned int nbChar)
{
	//Num of bytes read
	DWORD bytesRead;
	//Num of bytes need to be read
	unsigned int toRead;

	//ClearCommError function used for getting status info of serial port
	ClearCommError(this->hSerial, &this->errors, &this->status);

	//Check if there is anything to read
	if (this->status.cbInQue > 0)
	{
		//Check if there is required amount of data
		if (this->status.cbInQue > nbChar)
		{
			toRead = nbChar;
		}
		else
		{
			//read the amount of data available
			toRead = this->status.cbInQue;
		}

		//Read the data and return number of bytes read
		if (ReadFile(this->hSerial, buffer, toRead, &bytesRead, NULL) )
		{
			return bytesRead;
		}
	}
	//nothing was read
	return 0;
}

bool Serial::WriteData(const char *buffer, unsigned int nbChar)
{
	DWORD bytesSend;

	//Try to write the buffer on the serial port
	if (!WriteFile(this->hSerial, (void *)buffer, nbChar, &bytesSend, 0))
	{
		//write failed, return false
		ClearCommError(this->hSerial, &this->errors, &this->status);

		return false;
	}
	else
	{
		return true;
	}
}

bool Serial::IsConnected()
{
	return this->connected;
}
