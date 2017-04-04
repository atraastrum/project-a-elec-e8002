#include <stdio.h>
#include <tchar.h>
#include "SerialClass.h"
#include <string>

#include "ArduinoSerial.h"

//Simple main function for sending commands to arduino
void main()
{
	ArduinoSerial* serial = new ArduinoSerial(7);
	for (int i = 0; i < 6; i++)
	{
		if (serial->startPump())
		{
			std::cout << "Pump" << std::endl;
		}
		else
		{
			std::cout << "Pump failure" << std::endl;
		}
		if (serial->openLiquid1())
		{
			std::cout << "Liquid 1" << std::endl;
		}
		else
		{
			std::cout << "Liquid 1 failure" << std::endl;
		}
		if (serial->openLiquid2())
		{
			std::cout << "Liquid 2" << std::endl;
		}
		else
		{
			std::cout << "Liquid 2 failure" << std::endl;
		}
		if (serial->stopPump())
		{
			std::cout << "Pump stopping" << std::endl;
		}
		else
		{
			std::cout << "Pump stopping failure" << std::endl;
		}
		Sleep(5000);
	}
}

//int _tmain(int argc, _TCHAR* argv[])
//{
//	printf("Welcome to serial test app!\n\n");
//
//	Serial* SP = new Serial("COM7");
//
//	if (SP->IsConnected())
//	{
//		printf("We're connected!");
//	}
//	char incomingData[256] = "";
//	//printf("%s\n", incomingData);
//	int dataLength = 255;
//	int readResult = 0;
//
//	while (SP->IsConnected())
//	{
//		readResult = SP->ReadData(incomingData, dataLength);
//		printf("Bytes read: (0 means no data available) %i\n", readResult);
//		incomingData[readResult] = 0;
//		printf("%s", incomingData);
//
//		SP->WriteData("s", 1);
//		Sleep(500);
//	}
//	return 0;
//}