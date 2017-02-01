#include "Comms.h"

#define BUF_SIZE 2048

DWORD WINAPI MyControllingFunction(LPVOID pParam) {
    Comms * myObject = (Comms *)pParam;
    if (myObject == NULL)
        return -1;
    printf("new thread started");
    while (!myObject->isEnded()) {
        myObject->write();
        Sleep(50);
        myObject->read();
    }
    return 0;
}

Comms::Comms(){
	enumerate_ports();

	serial = NULL;
	if(!maintainConnection()){
		std::cout << "Could not connect to serial device\n";
	}
    ended = false;
    mutex = CreateMutex(
                        NULL,              // default security attributes
                        FALSE,             // initially not owned
                        NULL);
    in.gyroAngle = 0.0f;
}

void Comms::begin() {
    DWORD myThreadID;
    threadHandle = CreateThread(0, 0, MyControllingFunction, this, 0, &myThreadID);
}

void Comms::end() {
    WaitForSingleObject(mutex, INFINITE);
    ended = true;
    ReleaseMutex(mutex);
}

bool Comms::isEnded() {
    WaitForSingleObject(mutex, INFINITE);
    bool end = ended;
    ReleaseMutex(mutex);
    return end;
}

RobotIn Comms::getRobotIn() {
    WaitForSingleObject(mutex, INFINITE);
    RobotIn lin = in;
    ReleaseMutex(mutex);
    return lin;
}

RobotOut Comms::getRobotOut() {
    WaitForSingleObject(mutex, INFINITE);
    RobotOut lout = out;
    ReleaseMutex(mutex);
    return lout;
}

void Comms::setRobotOut(const RobotOut &newStruct) {
    WaitForSingleObject(mutex, INFINITE);
    out = newStruct;
    ReleaseMutex(mutex);
}


bool Comms::read(){
    if (serial == NULL)
        return false;
    WaitForSingleObject(mutex, INFINITE);
    uint8_t buffer[BUF_SIZE];
    size_t size = serial->available();
    size = size > BUF_SIZE ? BUF_SIZE : size;
	serial->read(buffer, size);
    for (int i = size - 1; i >= 7; i--) {
        if (buffer[i] == 0xdd && buffer[i - 1] == 0xee && buffer[i - 7] == 0xff) {
            if (crc8.compute(&buffer[i - 6], 4) == buffer[i - 2]) {
                float * temp = (float *)&buffer[i - 6];
                if (*temp < 1000000)
                    in.gyroAngle = *temp;
                break;
            }
        }
    }
    size = serial->available();
    while (size > 0) {
        size = size > BUF_SIZE ? BUF_SIZE : size;
        serial->read(buffer, size);
        size = serial->available();
    }
    ReleaseMutex(mutex);
	return true;
}

bool Comms::write(){
    WaitForSingleObject(mutex, INFINITE);
    if (serial == NULL) {
        maintainConnection();
        return false;
    }
    unsigned char packet[8] = { 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xdd };
    packet[1] = out.driveFL;
    packet[2] = out.driveBL;
    packet[3] = out.driveFR;
    packet[4] = out.driveBR;
    packet[5] = out.omni;
    packet[6] = crc8.compute(&packet[1], 5);
    size_t bytesWritten = serial->write(packet, 8);
    bytesWritten += serial->write(packet, 8);           // write twice. just in case
	if(bytesWritten != 16){
		serial->close();
		serial = NULL;
		std::cout << "Connection lost during write\n";
        maintainConnection();
        ReleaseMutex(mutex);
        return false;
	}
    ReleaseMutex(mutex);
	return true;
}

bool Comms::checkserial() {
    WaitForSingleObject(mutex, INFINITE);
    if (serial != NULL) {
        bool status = serial->isOpen();
        ReleaseMutex(mutex);
        return status;
    }
    ReleaseMutex(mutex);
    return false;
}

bool Comms::maintainConnection(){
	if(serial == NULL){
		std::vector<PortInfo> devices_found = list_ports();
		for(std::vector<PortInfo>::iterator it = devices_found.begin(); it != devices_found.end(); ++it){
			if(it->hardware_id.find("2341") != std::string::npos){ // Vendor ID
				std::cout << "Trying to connect to port " << it->port << ": " << it->description << std::endl;
				serial = new Serial(it->port, BAUD_RATE, serial::Timeout::simpleTimeout(TIMEOUT));

				if(serial->isOpen()){
					std::cout << "Connection successful\n";
					return true;
				} else{
					std::cout << "Connection unsuccessful\n";
					serial = NULL;
				}
			}
		}
		return false;
	}
	if(serial->isOpen()){
		return true;
	}else{
		serial = NULL;
		std::cout << "Connection lost\n";
		return false;
	}
}

void Comms::enumerate_ports(){
	std::vector<PortInfo> devices_found = list_ports();
	for(std::vector<PortInfo>::iterator it = devices_found.begin(); it != devices_found.end(); ++it){
		std::cout << it->port << ", " << it->description << ", " << it->hardware_id << std::endl;
	}
}