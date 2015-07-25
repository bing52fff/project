#ifndef __UDP_JSON_H
#define __UDP_JSON_H

#include "util.h"

class udp_json
{
public:
	udp_json();
	~udp_json();
	void set_val(Json::Value &);
	void get_val(Json::Value &);
	void set_str(std::string &);
	void get_str(std::string &);

	int val_to_str();
	int str_to_val();
private:
	Json::Value val;
	std::string str;
};

#endif	//udp_json.h
