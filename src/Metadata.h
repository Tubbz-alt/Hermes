#ifndef METADATA_H_INCLUDED
#define METADATA_H_INCLUDED

#import <map>
#import <fstream>
#include <boost/filesystem.hpp>

#include <tinyxml2.h>



using namespace std;
namespace tx=tinyxml2;
namespace fs=boost::filesystem;

class Metadata{
	protected:
		string name;
	
		uint16_t class; 
		uint64_t id; //ressource id
		
		map<string,string> fields;
		
		///storage
		pair<uint16_t, uint64_t> reference; //if needed
		//conteiners;
		
	protected:
		Metadata(c,i) : class(c), id(i), name("ressource"){
			reference = pair<uint16_t, uint64_t>(-1,-1);
		}
		
		string get(string key){ return fields[key]; }
		void set(string key, value){  fields[key] = value; }
		
		template<typename T>
		void set(string key, T value){
			ostreamstring stream;
			stream<<value;
			fields[key]=stream.str(); 
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
