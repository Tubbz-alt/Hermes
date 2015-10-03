#ifndef SQLMANAGER_H_INCLUDED
#define SQLMANAGER_H_INCLUDED

#include <mysql++/mysql++.h>
#include <mysql++/ssqls.h>


using namespace std;


class SQLManager{
	protected :
		mysqlpp::Connection conn;

	public :
		SQLManager(){
			const char* host="localhost";
			const char* login="root";
			const char* password="rj7@kAv;8d7_e(E6:m4-w&";
			const char* dbname="mnemosyne";

			conn =mysqlpp::Connection(false);
				if(!conn.connect(dbname, host, login, password)){
					cerr << "DB connection failed: " << conn.error() << endl;
					throw "";
				}
		}
		
		virtual ~SQLManager(){
			if( conn )
				conn.disconnect();
		}
};

#endif // SQLMANAGER_H_INCLUDED
