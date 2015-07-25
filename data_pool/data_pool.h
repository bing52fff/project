#ifndef __DATA_POOL_H
#define __DATA_POOL_H
	
#include "util.h"

class data_pool
{
public:
	data_pool(size_t sz = DEF_POOL_SIZE);
	~data_pool();
	int get_data(std::string&);
	int put_data(std::string&);
private:
	sem_t current_num;
	sem_t empty_num;
	std::vector<std::string> pool;
	int start;
	int end;
	size_t pool_size;
};

#endif	//data_pool.h
