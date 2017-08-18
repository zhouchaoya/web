#include "log.h"

static string level[] = {
	"NORMAL",
	"NOTICING",
	"WARNING",
	"FATAL"
};

void printf_log(const string msg, int _level)
{
#ifdef DEBUG
	if(_level >=0 && _level <= 3)
	cout<<""<<level[_level]<<endl;
#endif
}

