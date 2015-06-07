#ifndef RESSOURCE_H_INCLUDED
#define RESSOURCE_H_INCLUDED

#include <stdint.h>
#include <deque>
#include <map>

#include <boost/filesystem.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "SQLManager.h"
#include "Metadata.h"

using namespace std;
namespace fs=boost::filesystem;


enum class_type { t_Directory, t_Document, t_Text, t_Video, t_Image, t_Audio };


class Ressource{
	protected:
		uint64_t id;
		uint16_t class_type;
		uint16_t state;

		string data;
		//deque<char> data; //needed ???.. or only on hardr drive ??
		Metadata* metadata = NULL;

		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int version) {
				ar & id;
				ar & class_type;
				ar & state;
		}

	public:
        Ressource(){}

		Ressource(uint64_t i, uint16_t c): id(i), class_type(c){
			metadata = new Metadata( c, i);
		}

		Ressource(uint64_t i, uint16_t c, uint16_t s): id(i), class_type(c), state(s){
			metadata = new Metadata( c, i);
		}

		~Ressource(){
			delete metadata;
		}

		uint64_t getId(){ return id; }
		uint64_t getClass_type(){ return class_type; }
		uint16_t getState(){ return state; }
		Metadata*	getMetadata(){ return metadata; }


		void setId( uint64_t i ){
			id = i;
			metadata->setId( i);
		}
		void setClass_type( uint16_t c ){ class_type = c; }
        void setState( uint16_t s ){ state = s; }
        uint16_t getClassType(string contentType);

		void setData( string d ){ data = d; }
		string location(fs::path parent_dir);
		string metadata_location(fs::path parent_dir);

		string serialize(); ///network exchange purposes
		void unserialize( string data);

		virtual void save(fs::path parent_dir);
};

class SQLRessourceManager :public Manager {
	public :
		SQLRessourceManager(){}
		~SQLRessourceManager(){}

		string getTable(uint64_t class_type);
		uint16_t getClass_type( string table);

		void insert( Ressource& ressource);

		/**
		 * @brief assuming that all ressources have the same class_type => the argument
		 */
		void insert(uint16_t class_type, vector< Ressource* >& ressources );
		//void insert( vector< Ressource& >& ressources );

		Ressource get(uint16_t class_type, uint64_t id);
		Ressource get(string table, uint64_t id);
		vector<Ressource> get(uint16_t class_type, string fieldsNeeded, string where, string order, string limit);
		vector<Ressource> get(string table, string fieldsNeeded, string where, string order, string limit);
		vector<Ressource> get(uint16_t class_type, vector<uint64_t>& ids);
		vector<Ressource> get(string table, vector<uint64_t>& ids);

		//void update( Ressource& ressource);
		//void update( vector< Ressource& >& ressources );


		uint64_t count(uint16_t class_type, string where="", string order="", string limit="" );
		uint64_t count(string table, string where="", string order="", string limit="" );
};

#endif // RESSOURCE_H_INCLUDED
