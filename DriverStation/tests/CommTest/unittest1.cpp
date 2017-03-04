#include "stdafx.h"
#include "CppUnitTest.h"
#include <utils/Comms.h>
#include <utils/Comms.cpp>
#include <utils/crc8.cpp>
#include <robot/RobotIO.h>
#include <string>
#include <random> 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CommTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: Your test code here
            char messageBuf[200];
            Comms comms;
            comms.read();
            comms.write();
            comms.begin();
            int counter = 0;
            for (int i = 0; i < 100; i++) {
                float test = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                unsigned char buf[10];
                float * tmp = (float *)buf;
                *tmp = test;
                RobotOut out = comms.getRobotOut();
                out.driveFL = buf[0];
                out.driveBL = buf[1];
                out.driveFR = buf[2];
                out.driveBR = buf[3];
                comms.setRobotOut(out);
                Sleep(100);
                RobotIn in = comms.getRobotIn();
                sprintf(messageBuf, "\t\t\t%0.2f, test: %0.2f", in.gyroAngle, test);
                Logger::WriteMessage(messageBuf);
                if (in.gyroAngle == test)
                    counter++;
            }
            sprintf(messageBuf, "Accuracy: %0.2f", counter / 100.0f);
            Logger::WriteMessage(messageBuf);
		}

	};
}