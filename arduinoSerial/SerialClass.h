#ifndef SERIALCLASS_H_INCLUDED
#define	SERIALCLASS_H_INCLUDED

#define ARDUINO_WAIT_TIME 2000

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

class Serial
{

private:
	HANDLE hSerial;
	bool connected;
	COMSTAT status;
	DWORD errors;

public:
	Serial(const char *portName);
	~Serial();
	int ReadData(char *buffer, unsigned int nbChar);
	bool WriteData(const char *buffer, unsigned int nbChar);
	bool IsConnected();
};

#endif // !SERIALCLASS_H_INCLUDED
