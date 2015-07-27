#ifndef __UTIL_H
#define __UTIL_H

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <assert.h>
#include <semaphore.h>

#include <json/json.h>
#include <ncurses.h>

#define PORT	8888
#define	_SIZE_	1024
#define DEF_IP	"127.0.0.1"
#define DEF_POOL_SIZE	100

void debug_printf(const std::string& err_buf);

#endif	//util.h
