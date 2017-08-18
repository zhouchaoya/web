#include "udpserver.h"


udpserver::udpserver(const string _ip, const int& _port)
		:ip(_ip)
		 ,port(_port)
		 ,pool(SIZE)
{

}

bool udpserver::initServer()
{
	sock=socket(AF_INET, SOCK_DGRAM, 0);
	if(sock < 0){
		printf_log("create socket error", FATAL);
		exit(1);
	}

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip.c_str());
	if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0){
		printf_log("bind error", FATAL);
		exit(2);
	}
}

void udpserver::addUser(struct sockaddr_in& remote)//add uesr
{
	user_list.insert(pair<in_addr_t, struct sockaddr_in>(remote.sin_addr.s_addr, remote));
}

int udpserver::recvData(string &outstring)  //recv and send zifuchuan
{
//need ke kao xing 
	char buf[SIZE]; //SIZE ->1024
	struct sockaddr_in remote;
	socklen_t len = sizeof(remote);
	ssize_t s = recvfrom(sock, buf, sizeof(buf), 0,\
				(struct sockaddr*)&remote, &len);
	if(s > 0){
		addUser(remote);
		outstring = buf;  //ren chu qu
		pool.putData(outstring);
	}
	return s;
}


int udpserver::sendData(string &instring, \
			struct sockaddr_in &remote, socklen_t &len)
{
//send need ke kaoxing
	ssize_t s = sendto(sock, instring.c_str(), instring.size(),0,\
				(struct sockaddr*)&remote, len);
	if(s > 0){
		
	}
}
const int& udpserver::brocast() //broadcast
{
	//bian li map
	string msg ;
	pool.getData(msg);
	socklen_t len = 0;
	map<in_addr_t, struct sockaddr_in>:: iterator iter = user_list.begin();
	for(; iter != user_list.end(); iter++){
		len = sizeof(iter->second);
		sendData(msg, iter->second, len); //
	}

}
udpserver::~udpserver()
{
	close(sock);
}



