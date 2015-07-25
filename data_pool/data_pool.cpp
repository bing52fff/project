#include "data_pool.h"

data_pool::data_pool(size_t pool_sz) : pool(pool_sz), start(0), end(0), pool_size(pool_sz)
{
	sem_init(&current_num, 0, 0);
	sem_init(&empty_num, 0, pool_sz);
}

data_pool::~data_pool()
{
	sem_destroy(&current_num);
	sem_destroy(&empty_num);
}

int data_pool::get_data(std::string &data)
{
	sem_wait(&current_num);
	data = pool[start];
	start ++;
	start %= pool_size;
	sem_wait(&empty_num);
}

int data_pool::put_data(std::string &data)
{
	sem_wait(&empty_num);
	pool[end] = data;
	end ++;
	end %= pool_size;
	sem_post(&current_num);
}
