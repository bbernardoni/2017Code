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
    if (serial == NULL)
        return false;
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
	return true;
}

bool Comms::write(){
    if (serial == NULL)
        return false;
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
        return false;
	}
	return true;
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