#include <iostream>
#include <strings.h>
#include "sql_api.h"

using namespace std;

void SelectMysql(char* arg)
{
	sqlApi db;
	db.connect();
	db.select();
}
int main()
{
	
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

	SelectMysql(string_arg);
		return 0;
}
