#ifndef _UDP_CLIENT_
#define _UDP_CLIENT_


#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include "log.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <map>
#include <stdlib.h>


#define SIZE 1024
using namespace std;

class udpclient
{
	public:
		udpclient(const string _srv_ip, const int& _srv_port);
		 int recvData(string &outstring);  //recv and send zifuchuan
		 int sendData(string &instring);
		bool initclient();
		~udpclient();
	private:
		udpclient(const udpclient&u);
	private:
		int sock;
		string server_ip;
		int server_port;
	//	struct sockaddr_in server;
//		map<in_addr_t, struct sockaddr_in> user_list;  //rong qi
};



#endif
