#ifndef SQLMANAGER_H_INCLUDED
#define SQLMANAGER_H_INCLUDED

#include <mysql++/mysql++.h>
#include <mysql++/ssqls.h>


using namespace std;


class Manager{
	protected :
		mysqlpp::Connection conn;

	public :
		Manager();
		virtual ~Manager();
};

#endif // SQLMANAGER_H_INCLUDED
