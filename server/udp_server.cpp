#include "udp_server.h"

udp_server::udp_server() : fd(0), ip(DEF_IP), port(PORT)
{}

udp_server::~udp_server()
{
	close(fd);
}

int udp_server::init()
{
	int err = 0;
	fd = socket(PF_INET, SOCK_DGRAM, 0);
	if (fd < 0)
	{
		debug_printf("socket error\n");
		return 1;
	}
	struct sockaddr_in addr_server;
	bzero(&addr_server, sizeof(struct sockaddr_in));
	addr_server.sin_family = AF_INET;
	addr_server.sin_port = htons(port);
	if (0 == inet_pton(AF_INET, ip.c_str(), &addr_server.sin_addr))
	{
		debug_printf("invalid ip\n");
		return 1;
	}
	err = bind(fd, (struct sockaddr*)&addr_server, sizeof(addr_server));
	if (err < 0)
	{
		debug_printf("bind error\n");
		return 1;
	}
	return 0;
}

int udp_server::recv_msg()
{
	char buf[_SIZE_];
	memset(buf, 0, sizeof(buf));
	struct sockaddr_in addr_client;
	bzero(&addr_client, 0);
	socklen_t len = sizeof(struct sockaddr_in);
	int n = recvfrom(fd, buf, _SIZE_ - 1, 0, (struct sockaddr*)&addr_client, &len);
	if (n < 0)
	{
		debug_printf("recv msg error\n");
		return -1;
	}
	char remote[INET_ADDRSTRLEN];
	std::string client_ip = inet_ntop(AF_INET, &addr_client.sin_addr, remote, INET_ADDRSTRLEN);
	std::cout << user_online.insert(client_ip, addr_client) << std::endl;
	std::cout << ip << " : " <<  buf << std::endl;
	user_online.show();
	return 0;
}

int udp_server::send_msg(const std::string& msg, const struct sockaddr_in* addr_client)
{
	assert(addr_client);
	int n = sendto(fd, msg.c_str(), msg.size(), 0, (struct sockaddr*)addr_client, sizeof(struct sockaddr));
	return n;
}

int udp_server::broadcast_msg(const std::string& msg)
{
	user_info::container::iterator it;
	for (it = user_online.begin(); it != user_online.end(); ++ it)
		send_msg(msg, &(it->second));
	return 0;
}

int post_msg_to_pool()
{
	return 0;
}

int get_msg_from_pool()
{
	return 0;
}

udp_server::user_info::user_info()
{}
udp_server::user_info::~user_info()
{}

bool udp_server::user_info::insert(const std::string& ip, struct sockaddr_in client)
{
	if (!has_member(ip))
	{
		user[ip] = client;
		return true;
	}
	else
		return false;
}
bool udp_server::user_info::remove(const std::string& ip)
{
	std::map<std::string, struct sockaddr_in>::iterator it;
	it = user.find(ip);
	if (it != user.end())
	{
		user.erase(it);
		return true;
	}
	else
		return false;
}
bool udp_server::user_info::has_member(const std::string& ip)
{
	std::map<std::string, struct sockaddr_in>::iterator it;
	it = user.find(ip);
	return it == user.end() ? false : true;
}
void udp_server::user_info::show()
{
	std::map<std::string, struct sockaddr_in>::iterator it;
	for (it = user.begin(); it != user.end(); ++ it)
	{
		std::cout << it->first << " ";
	}
	std::cout << std::endl;
}
udp_server::user_info::container::iterator udp_server::user_info::begin()
{
	return user.begin();
}
udp_server::user_info::container::iterator udp_server::user_info::end()
{
	return user.end();
}

int main()
{
	udp_server us;
	us.init();
	while (1)
	{
		us.recv_msg();
		us.broadcast_msg("welcome");
	}
	return 0;
}

