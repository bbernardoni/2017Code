#include "Comms.h"

void enumerate_ports(){	
	std::vector<PortInfo> devices_found = list_ports();
	for (std::vector<PortInfo>::iterator it = devices_found.begin(); it != devices_found.end(); ++it){
		std::cout << it->port << ", " << it->description << ", " << it->hardware_id << std::endl;
	}
}

Comms::Comms(){
	enumerate_ports();
}

void Comms::read(){

}

void Comms::write(){

}