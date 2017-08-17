#include <iostream>
#include <strings.h>
#include <string.h>
#include "sql_api.h"

using namespace std;

void InsertMysql(char* arg)
{
	char arg_buf[1024];
	strcpy(arg_buf, arg);
	char* argv[8];
	int i = 0;
	char* start = arg_buf;
	while(*start){
		if(*start == '='){
			start++;
			argv[i++] = start;
		}
		if(*start == '&')
		{
			*start = '\0';
		}
		start++;
	}
	sqlApi db;
	db.connect();
	db.insert(argv[0], argv[1], argv[2], argv[3], argv[4]);
	
}
int main()
{
	cout<<"ohhhhhhhhh"<<endl;
	char* method = NULL;
	char* query_string = NULL;
	char* string_arg = NULL;
	int content_len = -1;
	char buf[1024];
	if((method=getenv("METHOD"))){
		if(strcasecmp(method, "GET") == 0){
			if(query_string = getenv("QUERY_STRING")){
				string_arg = query_string;
			}
		}else{
			if(getenv("CONTENT_LENGTH")){
				content_len = atoi(getenv("CONTENT_LENGTH"));
				//printf("content_len: %d\n", content_len);
				int i = 0;
				for(; i<content_len; i++){
					read(0, &buf[i], 1);
				}
				buf[i] = 0;
				//printf("%s\n", buf);
				string_arg = buf;
			}
		}
	}

	InsertMysql(string_arg);
	return 0;
}
