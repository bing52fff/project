#ifndef __UDP_SERVER_H
#define __UDP_SERVER_H

#include "util.h"

class udp_server
{
public:
	udp_server();
	~udp_server();
	int init();
	int recv_msg();
	int send_msg(const std::string&, const struct sockaddr_in*);
	int broadcast_msg(const std::string&);
	int post_msg_to_pool();
	int get_msg_from_pool();
protected:
	class user_info
	{
	public:
		typedef std::map<std::string, struct sockaddr_in> container;
	public:
		user_info();
		~user_info();
		bool insert(const std::string&, struct sockaddr_in);
		bool remove(const std::string&);
		bool has_member(const std::string&);
		container::iterator begin();
		container::iterator end();
		void show();
	private:
		std::map<std::string, struct sockaddr_in> user;
	};
private:
	int fd;
	std::string ip;
	int port;
	user_info user_online;
};

#endif	//udp_server.h
