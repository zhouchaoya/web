#ifndef _DATA_POOL_H_
#define _DATA_POOL_H

#include <iostream>
#include <vector>
#include <string>
#include <semaphore.h>


using namespace std;

class data_pool
{
	public:
		data_pool(int _cap);
		void getData(string &outstring);
		void putData(string &instring);
		~data_pool();
	private:
		data_pool(const data_pool&d);
	private:
		int cap;
		int size;
		int product_step;
		int consumer_step;
		sem_t blank;
		sem_t data;
		vector<string> pool;
};



#endif 
