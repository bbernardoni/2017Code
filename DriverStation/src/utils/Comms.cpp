#include "Comms.h"

Comms::Comms(){
	enumerate_ports();

	serial = NULL;
	if(!maintainConnection()){
		std::cout << "Could not connect to serial device\n";
	}
}

bool Comms::read(){
	size_t bytesRead = serial->read((uint8_t*)&in, sizeof(RobotIn));
	if(bytesRead != sizeof(RobotIn)){
		serial->close();
		serial = NULL;
		std::cout << "Connection lost during read\n";
		return maintainConnection();
	}
	return true;
}

bool Comms::write(){
	size_t bytesRead = serial->write((uint8_t*)&out, sizeof(RobotOut));
	if(bytesRead != sizeof(RobotOut)){
		serial->close();
		serial = NULL;
		std::cout << "Connection lost during write\n";
		return maintainConnection();
	}
	return true;
}

bool Comms::maintainConnection(){
	if(serial == NULL){
		std::vector<PortInfo> devices_found = list_ports();
		for(std::vector<PortInfo>::iterator it = devices_found.begin(); it != devices_found.end(); ++it){
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