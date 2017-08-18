#ifndef _UDP_SERVER_
#define _UDP_SERVER_


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
#include "data_pool.h"
#include <stdlib.h>


#define SIZE 1024
using namespace std;

class udpserver
{
	public:
		udpserver(const string _ip, const int& _port);
		
		 int recvData(string &outstring);  //recv and send zifuchuan
		 int sendData(string &instring,struct sockaddr_in& remote, socklen_t &len);
		bool initServer();
		const int& brocast();
		~udpserver();
	private:
		udpserver(const udpserver&u);
		void addUser(struct sockaddr_in& remote);//add uesr
	private:
		int sock;
		string ip;
		int port;
		data_pool pool;
		map<in_addr_t, struct sockaddr_in> user_list;  //rong qi
};



#endif
