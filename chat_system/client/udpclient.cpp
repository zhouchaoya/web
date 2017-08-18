#include "udpclient.h"


udpclient::udpclient(const string _srv_ip, const int& _srv_port)
		:server_ip(_srv_ip)
		 ,server_port(_srv_port)
	{
	}

bool udpclient::initclient()
{
	sock=socket(AF_INET, SOCK_DGRAM, 0);
	if(sock < 0){
		printf_log("create socket error", FATAL);
		exit(1);
	}

//	server.sin_family = AF_INET;
//	server.sin_port = htons(server_port);
//	server.sin_addr.s_addr = inet_addr(server_ip.c_str());
	
}



int udpclient::recvData(string &outstring)  //recv and send zifuchuan
{
//need ke kao xing 
	char buf[SIZE]; //SIZE ->1024
	struct sockaddr_in remote;
	socklen_t len = sizeof(remote);
	ssize_t s = recvfrom(sock, buf, sizeof(buf), 0,\
				(struct sockaddr*)&remote, &len);
	if(s > 0){
	
		outstring = buf;  //ren chu qu
		//pool.putData(outstring);
	}
	return s;
}


int udpclient::sendData(string &instring)
{
//send need ke kaoxing
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(server_port);
	server.sin_addr.s_addr = inet_addr(server_ip.c_str());
	socklen_t len = sizeof(server);
	ssize_t s = sendto(sock, instring.c_str(), instring.size(),0,\
				(struct sockaddr*)&server, len);
	if(s > 0){
		
	}
}

udpclient::~udpclient()
{
	close(sock);
}



