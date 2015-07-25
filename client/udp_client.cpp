#include "udp_client.h"
#include "udp_data.h"

udp_client::udp_client() : fd(0), port(PORT), ip(DEF_IP)
{}

udp_client::~udp_client()
{
	close(fd);
}

int udp_client::init()
{
	fd = socket(PF_INET, SOCK_DGRAM, 0);
	if (fd < 0)
	{
		debug_printf("socket error\n");
		return -1;
	}
	return 0;
}

int udp_client::send_msg(const std::string& msg)
{
	struct sockaddr_in addr_server;
	addr_server.sin_family = AF_INET;
	addr_server.sin_port = htons(port);
	if (0 == inet_pton(AF_INET, ip.c_str(), &addr_server.sin_addr))
	{
		debug_printf("invalid ip\n");
		return -1;
	}
	int n = sendto(fd, msg.c_str(), msg.size(), 0, (struct sockaddr*)&addr_server, sizeof(struct sockaddr));
	if (n < 0)
	{
		debug_printf("send error\n");
		return -1;
	}
	return 0;
}
int udp_client::recv_msg()
{
	struct sockaddr_in addr_server;
	socklen_t len = sizeof(struct sockaddr);
	char buf[_SIZE_];
	int n = recvfrom(fd, buf, _SIZE_-1, 0, (struct sockaddr*)&addr_server, &len);
	if (n <= 0)
		return n;
	buf[n] = 0;
	char remote[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &addr_server.sin_addr, remote, INET_ADDRSTRLEN);	
	std::cout << remote << " : " << buf << std::endl;
	return n;
}

int main()
{
	std::cout << "I am client" << std::endl;
	udp_client uc;
	uc.init();
	udp_data data("shouji", "sust", "working...", "message", "none");
	std::string msg = data.serialize();
	while (1)
	{
		sleep(1);
		uc.send_msg(msg);
//		uc.recv_msg();
	}
	return 0;
}
