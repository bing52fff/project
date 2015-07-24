#ifndef __UTIL_H
#define __UTIL_H

#include <iostream>
#include <string>
#include <map>

#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <assert.h>

#define PORT	8888
#define	_SIZE_	1024
#define DEF_IP	"127.0.0.1"

void debug_printf(const std::string& err_buf);

#endif	//util.h
