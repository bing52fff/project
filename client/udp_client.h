#ifndef __UDP_CLIENT_H
#define __UDP_CLIENT_H

#include "util.h"

class udp_client
{
public:
	udp_client();
	~udp_client();
	int init();
	int send_msg(const std::string&);
	int get_msg(std::string &msg);

	std::vector<std::string> get_friends();
	void add_friend(std::string &friends);
	void del_friend(std::string &friends);
private:
	int fd;
	int port;
	std::string ip;
	std::vector<std::string> friends_list;
};

#endif	//udp_client.h
