#ifndef _LOG_H_
#define _LOG_H_

#include <iostream>
#include <string>
using namespace std;

#define NORMAL 0
#define NOTICING 1
#define  WARNING 2
#define  FATAL 3


void printf_log(const string msg, int _level);




#endif 
