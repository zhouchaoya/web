#include "data_pool.h"

data_pool::data_pool(int _cap)
		:cap(_cap)
		 ,size(0)
		 ,pool(_cap)
{
	product_step = 0;
	consumer_step = 0;
	sem_init(&blank, 0, cap);  //init blank, data
	sem_init(&data, 0, 0);
}
void data_pool::getData(string &outstring)
{
	sem_wait(&data);   //shen qing shuju 
	outstring = pool[consumer_step];
	consumer_step++;
	consumer_step %= cap;
	size--;
	//size %= cap;  //dai biao shu ju duo shao
	sem_post(&blank);

}
void data_pool::putData(string &instring)
{
	//int index = 0;
	sem_wait(&blank);   //shen qing ge zi
	pool[product_step] = instring;
	product_step++;
	product_step %= cap;

	size++;
	//product_step %= cap;
	sem_post(&data);
}

data_pool::~data_pool()
{
	cap = 0;
	size = 0;
	product_step = 0;
	consumer_step = 0;
	sem_destroy(&blank);
	sem_destroy(&data);
}
