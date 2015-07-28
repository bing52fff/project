#include "udp_client.h"
#include "window.h"
#include "udp_data.h"

udp_client::udp_client() : fd(0), port(PORT), ip(DEF_IP)
{}

udp_client::~udp_client()
{
	close(fd);
}

std::vector<std::string> udp_client::get_friends()
{
	return friends_list;
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
int udp_client::get_msg(std::string &msg)
{
	struct sockaddr_in addr_server;
	socklen_t len = sizeof(struct sockaddr);
	char buf[_SIZE_];
	int n = recvfrom(fd, buf, _SIZE_-1, 0, (struct sockaddr*)&addr_server, &len);
	if (n <= 0)
		return n;
	buf[n] = 0;
	msg = buf;
	char remote[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &addr_server.sin_addr, remote, INET_ADDRSTRLEN);	
	std::cout << remote << " : " << buf << std::endl;
	return n;
}
void udp_client::add_friend(std::string &friends)
{
	std::vector<std::string>::iterator it = friends_list.begin();
	for(; it != friends_list.end(); it ++)
		if (*it == friends)
			return ;
	friends_list.push_back(friends);
}
void udp_client::del_friend(std::string &friends)
{
	std::vector<std::string>::iterator it = friends_list.begin();
	for (; it != friends_list.end(); it ++)
		if (*it == friends)
		{
			it = friends_list.erase(it);
			return ;
		}
}

static window win(100);
static udp_client cli;

void* draw_header(void *arg)
{
	int i = 1;
	win.create_header_win();
	WINDOW *header_win = win.get_header();
	while (1)
	{
		int _y, _x;
		getmaxyx(header_win, _y, _x);
		std::string msg = "BIT_TECH";
		win.add_str_to_win(header_win, _y/2, i, msg);
		win.win_refresh(header_win);
		sleep(1);
		win.clear_win_line(header_win, _y/2, 1);
		win.win_refresh(header_win);
		i = ++i%_x;
	}
}

void* draw_output(void *arg)
{
	udp_data net_in;
	win.create_output_win();
	WINDOW *output_win = win.get_output();
	int i = 1;
	while (1)
	{
		win.win_refresh(output_win);
		int _y, _x;
		getmaxyx(output_win, _y, _x);
		std::string msg;
		cli.get_msg(msg);
		net_in.deserialize(msg);
		std::string info;
		if (net_in.type == "message" && net_in.cmd == "None")
		{
			info = net_in.nick_name;
			info += "-";
			info += net_in.school;
			cli.add_friend(info);
			info += "$ ";
			info += net_in.msg;
			win.add_str_to_win(output_win, i, 1, info);
		}
		else if (net_in.type == "command" && net_in.cmd == "quit")
		{
			info = net_in.nick_name;
			info += "-";
			info += net_in.school;
			cli.del_friend(info);
		}
		sleep(1);
		i = ++i % _y;
		if (i >= _y-1)
		{
			i = 1;
			win.clear_win_line(output_win, 1, _y);
		}
	}
}
void* draw_friends(void *arg)
{
	win.create_friends_list_win();
	WINDOW *friends_win = win.get_friends_list();
	int index = 1;
	while (1)
	{
		win.win_refresh(win.get_friends_list());
		int _y, _x;
		getmaxyx(friends_win, _y, _x);
		std::vector<std::string> friends_list = cli.get_friends();
		int size = friends_list.size();
		int page = size / _y;
		int last = size  % _y;
		for (int i = 0; i < page; i++)
		{
			for (int j = 0; j < _y; j++)
			{
				std::string fri = friends_list[i*_y+j];
				win.add_str_to_win(friends_win, 1+j, 1, fri);
			}
			sleep(1);
			win.clear_win_line(friends_win, 1, _y);
		}
		for (int i = 0; i < last; i++)
		{
			std::string fri = friends_list[i];
			win.add_str_to_win(friends_win, 1+i, 1, fri);
		}
	}
}
void* draw_input(void *arg)
{
	udp_data scr_in;
	while (1)
	{
		win.create_input_win();
		WINDOW *input_win = win.get_input();
		win.win_refresh(input_win);
		std::string msg = win.get_str_from_win(input_win);
		if (strncasecmp("quit", msg.c_str(), 4) == 0)
		{
			exit(0);
		}
		scr_in.nick_name = "flypig";
		scr_in.school = "sust";
		scr_in.msg = msg;
		scr_in.type = "message";
		scr_in.cmd = "None";
		std::string str = scr_in.serialize();
		cli.send_msg(str);
	}	
}

int main()
{
	cli.init();
	pthread_t header, output, friends, input;
	pthread_create(&header, NULL, draw_header, NULL);
	pthread_create(&output, NULL, draw_output, NULL);
	pthread_create(&friends, NULL, draw_friends, NULL);
	pthread_create(&input, NULL, draw_input, NULL);
	pthread_join(header, NULL);
	pthread_join(output, NULL);
	pthread_join(friends, NULL);
	pthread_join(input, NULL);
	return 0;
}
/*
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
*/
