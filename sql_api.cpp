#include "sql_api.h"
#include <mysql.h>
using namespace std;

sqlApi::sqlApi(const string& _h, \
			int _port, \
			const string & _u,\
			const string & _p,\
			const string& _db)
{
	host = _h;
	user = _u;
	password = _p;
	port = _port;
	db = _db;
	conn = mysql_init(NULL);
}
int sqlApi::connect()
{
	if(mysql_real_connect(conn, host.c_str(), user.c_str(), password.c_str(),\
					db.c_str(), port, NULL, 0)){
		cout << "connect success!" << endl;
	}else{
		cout<<"connect faild!"<<endl;
	}
}

int sqlApi::insert(const string& _name,\
			const string& _sex,\
			const string& _age,\
			const string& _hobby,\
			const string& _school)
{
	string sql = "INSERT INTO data (name, age, sex, hobby, school)\
				  VALUES ('";
	sql += _name;
	sql += "','";
	sql += _age;
	sql += "','";
	sql += _sex;
	sql += "','";
	sql += _hobby;
	sql += "','";
	sql +=_school;
	sql += "');";
	cout<<sql<<endl;
	int ret = mysql_query(conn, sql.c_str());
	cout<<ret<<endl;
	return ret;
}

void sqlApi::select()
{
	string sql = "select* from data";
	if(mysql_query(conn, sql.c_str()) == 0){//xia fa naqushuju
		cout<<"string"<<endl;
	 res = mysql_store_result(conn);//duqujieguo
	 //int nums = 0;
	 //int col = 0;
		if(res){
			int	nums = mysql_num_rows(res);
			int	col = mysql_num_fields(res);
				cout << "nums:"<<nums << "col" << col <<endl;
	//		}
			MYSQL_FIELD *fd;
			for(; fd = mysql_fetch_field(res); ){
				cout<<fd->name<<" ";
			}
			cout<<endl;
			int i = 0;
			int j = 0;
			for(; i < nums; i++){
				MYSQL_ROW row_res = mysql_fetch_row(res);//char** erweishuzu
				int j = 0;
				for(; j < col; j++){
					cout<<row_res[j]<<" ";
				}
				cout<<endl;
			}
			cout<<endl;
		}
	}
	//return 0;
}
sqlApi::~sqlApi()
{
	mysql_close(conn);
}


