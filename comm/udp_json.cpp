#include "udp_json.h"

udp_json::udp_json()
{}

udp_json::~udp_json()
{}

void udp_json::set_val(Json::Value &value)
{
	val = value;
}
void udp_json::get_val(Json::Value &value)
{
	value = val;
}
void udp_json::set_str(std::string &_str)
{
	str = _str;
}
void udp_json::get_str(std::string &_str)
{
	_str = str;
}

int udp_json::val_to_str()
{
	Json::FastWriter write;
	str = write.write(val);
	return 0;
}
int udp_json::str_to_val()
{
	Json::Reader reader;
	if (reader.parse(str, val, false))
	{
		return 0;
	}
	else
		return 1;
}
