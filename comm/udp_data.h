#ifndef __UDP_DATA_H
#define __UDP_DATA_H
	
#include "util.h"
#include "udp_json.h"

class udp_data
{
public:
	udp_data();
	udp_data(const std::string, const std::string, const std::string, const std::string, const std::string);
	~udp_data();
	std::string serialize();
	int deserialize(std::string&);	
public:
	udp_json my_json;
	std::string nick_name;
	std::string school;
	std::string msg;
	std::string type;
	std::string cmd;
};

#endif	//udp_data.h
