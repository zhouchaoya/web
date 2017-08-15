#ifndef _HTTP_H__
#define _HTTP_H__

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

#define SIZE 1024


int startup(char* ip, int port);
int get_line(int fd, char buf[], int len);
void  error_response(int fd, int nums);
int echo_www(int fd,  char* path, int size);
void *handler_request(void* arg);
void clear_handler(int fd);


#endif //
