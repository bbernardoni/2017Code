#include "Comms.h"

#define BUF_SIZE 2048

Comms::Comms(){
	enumerate_ports();

	serial = NULL;
	
    in.gyroAngle = 0.0f;
}

void Comms::begin() {
	if(!maintainConnection()){
		std::cout << "Could not connect to serial device\n";
	}
}

void Comms::end() {
	serial = NULL;
}

bool Comms::isEnded() {
    return serial == NULL;
}

const RobotIn& Comms::getRobotIn() {
    return in;
}

RobotOut& Comms::getRobotOut() {
    return out;
}

void Comms::setRobotOut(const RobotOut &newStruct) {
    out = newStruct;
}


bool Comms::read(){
	if(serial == NULL){
        return false;
	}
    uint8_t buffer[BUF_SIZE];
    size_t size = serial->available();
	size = size > BUF_SIZE ? BUF_SIZE : size;
	if(size < 30){
		setOutBuf();
		serial->write(outBuf, 15);
		serial->write(outBuf, 15);
		return false;
	}
	//std::cout << "size=" << size << std::endl;
	serial->read(buffer, size);
	for(int i = size - 1; i >= 14; i--) {
        if (buffer[i] == 0xdd && buffer[i - 14] == 0xff) {
            if (crc8.compute(&buffer[i - 13], 12) == buffer[i - 1]) {
                float * temp = (float *)&buffer[i - 13];
                if (*temp < 1000000)
					in.gyroAngle = *temp;
					//std::cout << "gyro angle=" << in.gyroAngle << std::endl;
				in.sonicDistanceF = buffer[i - 9];
				in.sonicDistanceL = buffer[i - 8];
				in.sonicDistanceR = buffer[i - 7];
				in.sonicDistanceB = buffer[i - 6];
				in.shoulder = *((uint16_t*)(buffer+i-5));
				in.wrist = *((uint16_t*)(buffer+i-3));
                break;
            }
        }
    }
	while(size = serial->available()){
		size = size > BUF_SIZE ? BUF_SIZE : size;
		serial->read(buffer, size);
	}
	return true;
}

bool Comms::write(){
    if (serial == NULL)
        return false;
	setOutBuf();
	size_t size;
	uint8_t buffer[BUF_SIZE];
	while(size = serial->available()){
		size = size > BUF_SIZE ? BUF_SIZE : size;
		serial->read(buffer, size);
	}
	size_t bytesWritten = serial->write(outBuf, 15);
	bytesWritten += serial->write(outBuf, 15);           // write twice. just in case
	if(bytesWritten != 30){
		serial->close();
		serial = NULL;
		std::cout << "Connection lost during write\n";
        return false;
	}
	return true;
}

int Comms::read(unsigned char * buf, int bufsize) {
	uint8_t tmpbuf[BUF_SIZE];
	if(serial == NULL)
		return -1;
	size_t size = serial->available();
	size = size > BUF_SIZE ? BUF_SIZE : size;
	if(size < 4) {
		return -1;
	}
	serial->read(tmpbuf, size);
	for(int i = size - 1; i >= 3; i--) {
		if(tmpbuf[i] == 0xdd) {
			uint8_t len = tmpbuf[i - 1];
			if((len + 3) <= i && tmpbuf[i - len - 3] == 0xff && tmpbuf[-2] == crc8.compute(&tmpbuf[i - len - 2], len)) {
				memcpy(buf, tmpbuf, bufsize > 128 ? 128 : bufsize);
				return bufsize > 128 ? 128 : bufsize;
			}
		}
	}
	return -1;
}

int Comms::write(unsigned char * buf, int len) {
	if(serial == NULL)
		return -1;
	return serial->write(buf, len);
}

void Comms::setOutBuf(){
	outBuf[0] = 0xff;
	outBuf[1] = out.driveFL;
	outBuf[2] = out.driveBL;
	outBuf[3] = out.driveFR;
	outBuf[4] = out.driveBR;
	outBuf[5] = out.omni;
	outBuf[6] = out.shoulder;
	outBuf[7] = out.wrist;
	outBuf[8] = out.keyGrabber;
	outBuf[9] = out.intake;
	outBuf[10] = out.score;
	outBuf[11] = out.doorOut;
	outBuf[12] = out.doorUp;
	outBuf[13] = crc8.compute(&outBuf[1], 12);
	outBuf[14] = 0xdd;
}

bool Comms::maintainConnection(){
	if(serial == NULL){
		std::vector<PortInfo> devices_found = list_ports();
		for(std::vector<PortInfo>::iterator it = devices_found.begin(); it != devices_found.end(); ++it){
			// our serial communicator has a vid of 10C4
			if(it->hardware_id.find("10C4") != std::string::npos){ // Vendor ID
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