#include "udp_server.h"
#include "udp_data.h"

udp_server::udp_server() : fd(0), ip(DEF_IP), port(PORT), data()
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
	addr_server.sin_addr.s_addr = htonl(INADDR_ANY);
	err = bind(fd, (struct sockaddr*)&addr_server, sizeof(addr_server));
	if (err < 0)
	{
		debug_printf("bind error\n");
		return 1;
	}
	return 0;
}

int udp_server::recv_msg(std::string &msg)
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
	buf[n] = 0;
	msg = buf;
	char remote[INET_ADDRSTRLEN];
	std::string client_ip = inet_ntop(AF_INET, &addr_client.sin_addr, remote, INET_ADDRSTRLEN);
	user_online.insert(client_ip, addr_client);
	return n;
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

int udp_server::post_msg_to_pool(std::string& msg)
{
	data.put_data(msg);
	return 0;
}

int udp_server::get_msg_from_pool(std::string& msg)
{
	data.get_data(msg);
	debug_printf(msg);

	udp_data data;
	data.deserialize(msg);
	std::cout << data.nick_name << ": " << data.msg << std::endl;
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
////////////////////////////////////////////////////////////////////////

udp_server us;

void* pro_run(void *arg)
{
	std::string msg;
	while (1)
	{
		if (us.recv_msg(msg) > 0)
		{
			us.post_msg_to_pool(msg);
		}
	}
	return (void*)0;
}

void* con_run(void *arg)
{
	std::string msg;
	while(1)
	{
		us.get_msg_from_pool(msg);
	}
	return (void*)0;
}

int main()
{
	us.init();
	pthread_t consumer, producer;
	pthread_create(&producer, NULL, pro_run, NULL);
	pthread_create(&consumer, NULL, con_run, NULL);
	pthread_join(consumer, NULL);
	pthread_join(producer, NULL);
	return 0;
}

