#include "Comms.h"

void enumerate_ports(){	
	std::vector<PortInfo> devices_found = list_ports();
	for (std::vector<PortInfo>::iterator it = devices_found.begin(); it != devices_found.end(); ++it){
		printf("(%s, %s, %s)\n", it->port.c_str(), it->description.c_str(), it->hardware_id.c_str());
	}
}

Comms::Comms(){
	enumerate_ports();
}

void Comms::read(){

}

void Comms::write(){

}