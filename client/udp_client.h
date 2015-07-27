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
	int recv_msg();
private:
	int fd;
	int port;
	std::string ip;
};

#endif	//udp_client.h
