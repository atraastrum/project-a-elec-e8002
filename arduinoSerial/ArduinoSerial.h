#include "SerialClass.h"
#include <stdio.h>
#include <string>
#include <tchar.h>
#include <iostream>

class ArduinoSerial
{
public:
	//Constructor sets up the connection and com port
    ArduinoSerial(int comport=4);
	//Destructor closes the connection
	~ArduinoSerial();
    //Set com port

	//Function for sending the start command to pump
	bool startPump();
	//Function for sending opening command to liquid 1 valve
	bool openLiquid1();
	//Function for sending opening command to liquid 2 valve
	bool openLiquid2();
	//Function for sending stop command to pump
	bool stopPump();

private:
	Serial* SP;
	char incomingData[256] = "";
	int dataLength = 255;
	int readResult = 0;
};

