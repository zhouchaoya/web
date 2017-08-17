#ifndef _SQL_
#define _SQL_

#include <iostream>
#include <string>
#include <mysql.h>
using namespace std;

class sqlApi{
	public:
		sqlApi(const string& _h = "127.0.0.1",\
			int _port = 3306,\
			const string & _u = "root",\
			const string& _p = "123456",\
			const string& _db = "myclass" );
		int connect();
		void select();
		int insert(const string& _name,\
					const string& _sex,\
					const string& _age,\
					const string& _hobby,\
					const string& _school);
		~sqlApi();
	private:
		MYSQL* conn;
		MYSQL_RES* res;
		string host;
		string user;
		string password;
		string db;
		int port;
	
};




#endif 
