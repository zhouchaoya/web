#include "udpclient.h"


static void usage(char* proc)
{
	cout<<"Usage: "<< proc<<"[remote_ip]"<<"[remote_port]"<<endl;
}
//./client 127.0.0.1 8080
int main(int argc, char*argv[])
{
	if(argc != 3){
		usage(argv[0]);
		exit(1);
	}
	
	int port = atoi(argv[2]);
	udpclient cli(argv[1], port);
	cli.initclient();
	while(1){
	string msg = "hello";
	cout<<"send done..."<<endl;
	cli.sendData(msg);
	sleep(1);
	msg = "";
	cout<<"123456"<<endl;
	cli.recvData(msg);
	cout<<"recv echo:"<<msg<<endl;
	}
	return 0;
}
