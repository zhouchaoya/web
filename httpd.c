#include "httpd.h"

int startup(char* ip, int port)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0){
		perror("socket");
		exit(2);
	}
	
	int opt = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip);
	if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0){
		perror("bind");
		exit(3);
	}
	if(listen(sock, 10) < 0){//链接队列
		perror("listen");
		exit(4);
	}
	return sock;
	
}

int get_line(int sock, char* buf, int len) //每次读一行，而且将结尾标志\r\n或 \r或 \n全部转换为‘\n’
{
	int i = 0;
	char c = '\0';
	printf("getline\n");
	while(i<len-1 && c != '\n'){//不是结尾
		ssize_t s = recv(sock, &c, 1, 0);
		if(s > 0){
			if(c == '\r'){
				recv(sock, &c, 1, MSG_PEEK); //仅仅查看后一个是不是\n
				if(c == '\n'){
					recv(sock, &c, 1, 0);//将\r\n 转化为\n
				}else{
					c = '\n';
				}
			}  //全部转换完毕
			buf[i++] = c;
		}
		else{
			return -1;
		}
	}
	buf[i] = 0;
	return i; //返回个数
}

void error_response(int fd, int nums)
{
	
}
void clear_handler(int fd)
{
	char buf[SIZE];
	int ret = 0;
	do{
		ret = get_line(fd, buf, sizeof(buf));
	}while(ret > 0 && strcmp(buf, "\n") != 0);
}

void exe_cgi(int fd, char* path,\
			const char*method, const char* query_string)
{
	int content_length = -1;
	char method_env[SIZE/10];
	char query_string_env[SIZE];
	char content_len_env[SIZE/10];

	if(strcasecmp(method, "GET") == 0){//如果是get方法，清除头部信息
			clear_handler(fd);
	}else{//POST 方法清除请求正文前信息，空行作为分隔符
		char buf[SIZE];
		int ret = 0;
		do{
			ret = get_line(fd, buf, sizeof(buf));
			if(strncasecmp(buf, "Content-Length: ", 16) == 0){
				printf("ret: %d\n", ret);
				content_length = atoi(&buf[16]); //从16号下标开始
			}
		}while(ret > 0 && strcmp(buf, "\n") != 0);
		if(content_length == -1){
			printf("1234567\n");
			//return;
		}
	}

	const char *status_line = "HTTP/1.0 200 OK\r\n";
	send(fd, status_line, strlen(status_line), 0);
	const char* type_line = "Content-Type:text/html;charset=ISO_8859-1\r\n";

	send(fd, type_line, strlen(type_line), 0);
	const char *blank_line = "\r\n";
	send(fd, blank_line, strlen(blank_line), 0);

	int input[2];
	int output[2];
	if(pipe(input) < 0 || pipe(output) < 0){
		return;
	}

	pid_t id = fork();//创建子进程执行execl
	if(id < 0){
		return;
	}else if(id == 0){//child
		close(input[1]);
		close(output[0]);

		dup2(input[0], 0);
		dup2(output[1], 1);

		sprintf(method_env, "METHOD=%s", method);
		putenv(method_env);//导出环境变量

		if(strcasecmp(method, "GET") == 0){
			sprintf(query_string_env, "QUERY_STRING=%s", query_string);
			putenv(query_string_env);
		}else{
			sprintf(content_len_env,"CONTENT_LENGTH=%d", content_length);
			putenv(content_len_env);
		}
	execl(path, path, NULL);
	exit(1);
	}else{//father
		close(input[0]);
		close(output[1]);

		int i = 0;
		char c;
		if(strcasecmp(method, "POST") == 0){
			for(; i < content_length; i++){
				recv(fd, &c, 1, 0);
				write(input[1], &c, 1);
			}
		}
		while(read(output[0], &c, 1) > 0){
			send(fd, &c, 1, 0);
		}
		
		waitpid(id, NULL, 0);
		close(input[1]);
		close(output[0]);
	}
}
int echo_www(int fd, char*path, int size)
{
	int new_fd = open(path, O_RDONLY);//先打开文件
	if(new_fd < 0){
		return 404;
	}

	const char* status_line = "HTTP/1.0 200 OK\r\n";
	const char* blank_line = "\r\n";
	send(fd, status_line, strlen(status_line), 0);//响应状态行
	send(fd, blank_line, strlen(blank_line), 0);//响应空行
	sendfile(fd, new_fd, NULL, size);//响应正文

	close(new_fd);
	return 200;
}
void *handler_request(void* arg)
{
	int fd = (int)arg;
	char buf[SIZE];
	char method[SIZE/10];
	char url[SIZE];
	char path[SIZE];
	int ret = 0;
	int cgi = 0;
	int nums = 0; //错误码
	char* query_string = NULL;
	
#ifdef _DEBUG_
	do{
		printf("jinlai\n");
		ret = get_line(fd, buf, sizeof(buf));
		printf("%s", buf);
	}while(ret > 0 && strcmp(buf, "\n") != 0)
	return (void*)0;
#else
	//printf("jinlai\n");
	if(get_line(fd, buf, sizeof(buf)) <= 0){
		ret = -1;
		nums = 404;
		goto end;
	}
	//GET / a/b/cindex.html http/1.0
	
	int i = 0;
	int j = 0;

	//获取请求方法
	while(i < sizeof(method) && j < sizeof(buf) &&\
				!isspace(buf[j])){
		method[i] = buf[j];
		i++;
		j++;
	}
	method[i] = 0;

	//获取url

//	url[i] = 0;
//	printf("%s\n", method);
	if(strcasecmp(method, "GET")  && strcasecmp(method, "POST")){
		ret = -1;
		nums = 404;
		goto end;
	}
	if(strcasecmp(method, "POST") == 0){//POST cgi = 1
		cgi = 1;
	}
	while(j < sizeof(buf) && isspace(buf[j])){
		j++;
	}
	i = 0;
	while(i < sizeof(url) && j < sizeof(buf) &&\
				!isspace(buf[j])){
		url[i] = buf[j];
		i++;
		j++;
	}
	url[i] = 0;
	printf("method:%s url:%s\n", method, url);
	if(strcasecmp(method, "GET") == 0){//GET方法
	
		query_string = url;
		while(*query_string != '\0'){
			if(*query_string == '?'){
				*query_string = '\0';
				query_string++;
				cgi = 1;
				break;
			}
			query_string++;
		}
	}
	sprintf(path, "wwwroot/%s", url);//将预输出字符串输入缓冲区
	//wwwroot/a/b/c/s.html
	if(path[strlen(path)-1] == '/'){//r如果是根目录/结尾，然后字符串拼接
		strcat(path, "index.html");//一般首页.html结尾
	}

	//wwwroot/a/b/c/index.html
	//stat用来判定文件是否存在，并拿出文件源信息，inode保存文件信息
	struct stat st;//判断文件是否存在，是一个结构体
	if(stat(path, &st) < 0){
		nums = 404;
		goto end;
	}else{
		if(S_ISDIR(st.st_mode)){// 判断文件是否合法，S_ISDIR宏函数
			strcat(path, "/index.html");//带上/
		}else if((st.st_mode & S_IXUSR) ||\
					(st.st_mode & S_IXGRP) || \
					(st.st_mode & S_IXOTH)){
			cgi = 1;
		}else{
		
		}
		if(cgi){
			exe_cgi(fd, path, method, query_string);
		}
		else{
			//path not cgi 
			clear_handler(fd);//处理头部信息
		//	printf("www\n");
			nums = echo_www(fd, path, st.st_size);//path文件存在，并且是普通文件
		}
	}

#endif
end:
	if(nums != 200){
		error_response(fd, nums);
	}
	close(fd);
	return (void*)ret;

}
