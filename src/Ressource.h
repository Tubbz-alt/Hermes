#ifndef RESSOURCE_H_INCLUDED
#define RESSOURCE_H_INCLUDED

#include <stdint.h>
#include <deque>
#include <map>

#include <boost/filesystem.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using namespace std;
namespace fs=boost::filesystem;

class Ressource{
	protected:
		uint64_t id;
		uint16_t class;
		uint16_t state;
		
		string data;
		deque<char> data; //needed ???.. or only on hardr drive ??
		Metadata* metadata = NULL;
		
		friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version) {
                ar & id;
                ar & class;
                ar & state;
        } 
        
	public:
		Ressource(uint64_t i, uint16_t c): id(i), class(c){}
		Ressource(uint64_t i, uint16_t c, uint16_t s): id(i), class(c), state(s){}
	
		~Ressource(){
			if( metadata != NULL )
				delete metadata;
		}
	
		uint64_t getId(){ return id; }
		uint16_t getClass(){ return  class; }
		uint16_t getState(){ return state; }
		
		void setId( uint64_t i ){ id = i; }
		void setClass( uint16_t c ){ class = c; }  
		void setState( uint16_t s ){ state = s; }  
		
		void setData( string d ){ data = d; }
		string location(fs::path parent_dir){};
		string metadata_location(fs::path parent_dir){};
		
		string serialize(); ///network exchange purposes
		void unserialize( string );
		
		virtual void save(fs::path parent_dir);
};

enum class_type { Directory, Document, Text, Video, Image, Audio };
map<string, class_type> map_class_type;

/// application

map_class_type["application/javascript"] 		= Text;
map_class_type["application/ogg"] 				= Video;
map_class_type["application/xhtml+xml"] 		= Text;
map_class_type["application/json"] 				= Text;
map_class_type["application/xml"] 				= Text;

class_type getClassType(string contentType){
	switch( contentType.substr(0, str.find_first_of("/")) ){
		case "audio":
			return Audio;
		break;
		case "image":
			return Image;
		break;
		case "text":
			return Text;
		break;
		case "video":
			return Video;
		break;
	}
	
	if( map_class_type.count(contentType) > 0)
		return map_class_type[contentType];
	else
		return Document;
}



#endif // RESSOURCE_H_INCLUDED
