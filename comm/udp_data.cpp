#include "udp_data.h"

udp_data::udp_data()
{}

udp_data::~udp_data()
{}

udp_data::udp_data(const std::string _nick_name, const std::string _school, const std::string _msg,
		const std::string _type, const std::string _cmd)
	: nick_name(_nick_name), school(_school), msg(_msg), type(_type), cmd(_cmd)
{}

std::string udp_data::serialize()
{
	Json::Value root;
	root["nick_name"] = nick_name;
	root["school"] = school;
	root["msg"] = msg;
	root["type"] = type;
	root["cmd"] = cmd;
	my_json.set_val(root);
	my_json.val_to_str();
	std::string ret;
	my_json.get_str(ret);
	return ret;
}

int udp_data::deserialize(std::string& str)
{
	my_json.set_str(str);
	my_json.str_to_val();
	Json::Value root;
	my_json.get_val(root);

	nick_name = root["nick_name"].asString();
	school = root["school"].asString();
	msg = root["msg"].asString();
	type = root["type"].asString();
	cmd = root["cmd"].asString();
	return 0;
}
