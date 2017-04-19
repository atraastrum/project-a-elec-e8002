#include "ArduinoSerial.h"
#include <QDebug>

ArduinoSerial::ArduinoSerial()
{
    SP = nullptr;
}

ArduinoSerial::~ArduinoSerial()
{
    if(SP)
    {
        delete SP;
    }
}

bool ArduinoSerial::setComPort(int comport)
{
    printf("Initializing connection to Arduino..");

    //Convert port number to const char
    std::string portStr = "COM" + std::to_string(comport);
    //std::cout << portStr << std::endl;
    const char *port = portStr.c_str();
    //catch error here
    SP = new Serial(port); //use the comport variable here

    if (SP->IsConnected())
    {
        //printf("We are connected!");
        return true;
    }
    return false;
}

//Requires debugging a lot, homo
std::string ArduinoSerial::connectionCheck()
{
    char incomingData[256] = "";
    int dataLength = 255;
    int readResult = 0;

    if(SP->IsConnected())
    {
        SP->WriteData("i", 1);

        readResult = SP->ReadData(incomingData, dataLength);
        qDebug() << "Readresult:" << readResult;
        incomingData[readResult] = '\0';
        qDebug() << incomingData;
    } 
    qDebug() << "data:";
    std::string retVal(incomingData);
    qDebug() << retVal.c_str();
    return retVal;
}

bool ArduinoSerial::startPump()
{
	if (SP->IsConnected())
	{
		SP->WriteData("s", 1);
		return true;
	}
	return false;
}

bool ArduinoSerial::stopPump()
{
	if (SP->IsConnected())
	{
		SP->WriteData("p", 1);
        //Sleep(500);
		return true;
	}
	return false;
}

bool ArduinoSerial::openLiquid1()
{
	if (SP->IsConnected())
	{
		SP->WriteData("o", 1);
        //Sleep(500);
		return true;
	}
	return false;
}

bool ArduinoSerial::openLiquid2()
{
	if (SP->IsConnected())
	{
		SP->WriteData("c", 1);
        //Sleep(500);
		return true;
	}
	return false;
}
