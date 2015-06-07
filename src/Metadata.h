#ifndef METADATA_H_INCLUDED
#define METADATA_H_INCLUDED

#include <map>
#include <fstream>
#include <sstream>
#include <boost/filesystem.hpp>

#include "../extra/tinyxml2.h"

using namespace std;
namespace tx=tinyxml2;
namespace fs=boost::filesystem;

class Metadata{
	protected:
		string name;

		uint16_t class_type;
		uint64_t id; //ressource id

		map<string,string> fields;

		///storage
		pair<uint16_t, uint64_t> reference; //if needed : (classe_type, id)
		//conteiners;

	public:
		Metadata(uint16_t c, uint64_t i) : class_type(c), id(i), name("ressource"){
			reference = pair<uint16_t, uint64_t>(-1,-1);
		}

		void setId(uint64_t i){ id = i; }

		string get(string key){ return fields[key]; }

		template<typename T>
		void set(string key, T value){
			ostringstream stream;
			stream<<value;
			fields[key]=stream.str();
		}

		void addReference(uint16_t c, uint64_t i){
			reference	= pair<uint16_t, uint64_t>(c,i);
		}

		/**
		 * @brief write metadata into file on xml format
		 */
		void write(string location);

		/**
		 * @brief hydrate current object from file
		 */
		void hydrate(string location);
};
#endif //METADATA_H_INCLUDED
