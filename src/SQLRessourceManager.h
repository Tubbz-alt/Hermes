#ifndef SQLRESSOURCEMANAGER_H_INCLUDED
#define SQLRESSOURCEMANAGER_H_INCLUDED

#include <stdint.h>
#include <map>



#include "SQLManager.h"
#include "Ressource.h"
#include "Document.h"
#include "Directory.h"
#include "Text.h"
#include "Image.h"
#include "Audio.h"
#include "Video.h"

using namespace std;
namespace fs=boost::filesystem;

class SQLRessourceManager :public SQLManager {
	protected:
		vector<Ressource *> acc;  ///for python, mainly
	public :
		SQLRessourceManager(){}
		~SQLRessourceManager(){}

		string getTable(uint64_t class_type){
			map<int, string> m ={ {t_Directory,"directory"}, 
							{t_Document,"document"}, 
							{t_Text,"text"},
							{t_Video,"video"}, 
							{t_Image,"image"}, 
							{t_Audio,"audio"}
						};
			return m[ class_type ];
		}
		
		uint16_t getClass_type( string table){
			map<string, int> m = { {"directory",t_Directory}, 
				{"document",t_Document}, 
				{"text",t_Text}, 
				{"video",t_Video}, 
				{"image",t_Image}, 
				{"audio",t_Audio}
						};
			return m[ table ];
		}

		void insert( Ressource* ressource){
			mysqlpp::Query query = conn.query();
			query<<"INSERT INTO "<<getTable( ressource->getClass_type() )<<" VALUES ()";

			if (mysqlpp::SimpleResult res = query.execute())
				ressource->setId( (uint64_t)res.insert_id() );
			else{
				cerr << "Failed to get item list: " << query.error() << endl;
				throw "";
			}
		}

		/**
		 * @brief assuming that all ressources have the same class_type => the argument, for python only
		 */
		 
		 template<typename T>
		 void add_acc(T* r){ acc.push_back(r); }
		 
		 uint64_t insert_with_acc(uint16_t class_type){
			if( acc.empty() )
				return 0;
			mysqlpp::Query query = conn.query();
			mysqlpp::Query id_query = conn.query();

			query<<"INSERT INTO "<<getTable( class_type )<<" VALUES ";

			for(uint64_t k=0; k<acc.size(); k++){
				if( k!=0 )
					query<<", ";
				query<<"()";
			}
			acc = vector<Ressource* >();

			if (mysqlpp::SimpleResult res = query.execute()){
				id_query<<"SELECT LAST_INSERT_ID() as id FROM "<<getTable( class_type );
				mysqlpp::StoreQueryResult id_res = id_query.store();

				return (uint64_t)id_res[0]["id"];
			}else{
				cerr << "Failed to get item list: " << query.error() << endl;
				throw "";
			}
			
			return 0;
		 }
		//template<typename T>
		//uint64_t insert(uint16_t class_type, vector< T >& ressources ){
			//cout<<"coucou"<<endl;
			////if( ressources.empty() )
				////return 0;
			////mysqlpp::Query query = conn.query();
			////mysqlpp::Query id_query = conn.query();

			////query<<"INSERT INTO "<<getTable( class_type )<<" VALUES ";

			////for(uint64_t k=0; k<ressources.size(); k++){
				////if( k!=0 )
					////query<<", ";
				////query<<"()";
			////}

			////if (mysqlpp::SimpleResult res = query.execute()){
				////id_query<<"SELECT LAST_INSERT_ID() as id FROM "<<getTable( class_type );
				////mysqlpp::StoreQueryResult id_res = id_query.store();

				////uint64_t  I = (uint64_t)id_res[0]["id"];

				////return I;
			////}else{
				////cerr << "Failed to get item list: " << query.error() << endl;
				////throw "";
			////}
			//return 0;
		//}
		
		
		void insert(uint16_t class_type, vector< Ressource* >& ressources ){
			if( ressources.empty() )
				return;
			mysqlpp::Query query = conn.query();
			mysqlpp::Query id_query = conn.query();

			query<<"INSERT INTO "<<getTable( class_type )<<" VALUES ";

			for(vector<Ressource* >::iterator it=ressources.begin(); it!=ressources.end(); it++){
				if( it != ressources.begin() )
					query<<", ";
				query<<"()";
			}

			if (mysqlpp::SimpleResult res = query.execute()){
				id_query<<"SELECT LAST_INSERT_ID() as id FROM "<<getTable( class_type );
				mysqlpp::StoreQueryResult id_res = id_query.store();

				uint64_t  I = (uint64_t)id_res[0]["id"];

				for( uint64_t i =ressources.size()-1; i>=0 ; i++){
					ressources[ i ]->setId( I-i );
				}
			}else{
				cerr << "Failed to get item list: " << query.error() << endl;
				throw "";
			}
		}
		////void insert( vector< Ressource& >& ressources );



		Ressource get(uint16_t class_type, uint64_t id){
			return get( getTable( class_type ), id );
		}

		Ressource get(string table, uint64_t id){
			stringstream idStr;
			idStr<<id;

			vector<Ressource> vect = get(table, "*", "id = "+idStr.str(), "id", "");
			if( vect.size() == 1 )
				return vect[0];
			else
				throw runtime_error("ressource not found");
		}

		vector<Ressource> get(uint16_t class_type, string fieldsNeeded, string where, string order, string limit){
			return get( getTable( class_type ), fieldsNeeded, where, order, limit );
		}

		vector<Ressource> get(string table, string fieldsNeeded, string where, string order, string limit){
			vector<mysqlpp::Row> v;
			vector< Ressource > ressources;
			mysqlpp::Query query = conn.query();
			query << "SELECT " << fieldsNeeded <<" FROM "<<table<<" WHERE "<< where <<" ORDER BY "<< order<< " "<<limit;
			mysqlpp::StoreQueryResult res = query.store();

			for(size_t i = 0; i < res.num_rows(); ++i)
				ressources.push_back( Ressource( (uint64_t)res[i]["id"], getClass_type(table) ) );

			return ressources;
		}

		vector<Ressource> get(uint16_t class_type, vector<uint64_t>& ids){
			return get( getTable( class_type ), ids );
		}

		vector<Ressource> get(string table, vector<uint64_t>& ids){
			string where = "id IN (";

			for(uint64_t i=0; i<ids.size(); i++){
				where += ( i != 0 ) ? "," : "";

				std::ostringstream id;
				id<<ids[i];
				where += id.str();
			}
			where += ")";
			return get( table, "*", where, "id", "");
		}

		uint64_t count(uint16_t class_type, string where, string order, string limit ){
			return count(getTable(class_type), where, order, limit);
		}

		uint64_t count(string table, string where, string order, string limit ){
			vector<mysqlpp::Row> v;
			mysqlpp::Query query = conn.query();
			query << "SELECT COUNT(*) AS number FROM "<< table<<" WHERE "<< where <<" ORDER BY "<< order<< " LIMIT "<<limit;
			mysqlpp::StoreQueryResult res = query.store();

			return (uint64_t)res[0]["number"];

		}










		
		//void update( Ressource& ressource);
		//void update( vector< Ressource& >& ressources );

};
#endif // SQLRESSOURCEMANAGER_H_INCLUDED
