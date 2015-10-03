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


enum class_type { t_Document, t_Text, t_Video, t_Image, t_Audio, t_Directory };

class Ressource{
	protected:
		uint64_t id;
		uint16_t class_type;
		uint16_t state;

		string data;
		string filename; ///Temporary filename
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
        Ressource(){
			metadata = new Metadata();
		}

		Ressource(uint64_t i, uint16_t c): id(i), class_type(c){
			metadata = new Metadata( c, i);
		}

		Ressource(uint64_t i, uint16_t c, uint16_t s): id(i), class_type(c), state(s){
			metadata = new Metadata( c, i);
		}

		virtual ~Ressource(){
			if( metadata != NULL)
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
        
        void setMetadata( Metadata* m){
			if( metadata != NULL)
				delete metadata;
			metadata = m;
		}
		
        uint16_t contentType2ClassType(string contentType){
			map<string, uint16_t> map_class_type={
				{"application/javascript" , t_Text},
				{"application/ogg"        , t_Video},
				{"application/xhtml+xml"  , t_Text},
				{"application/json"       , t_Text},
				{"application/xml"        , t_Text},
				{"application/x-directory", t_Directory},
				{"inode/directory",			t_Directory	},
				{"text/directory",    		t_Directory}
			};
			contentType = contentType.substr(0, contentType.find_first_of("/"));

			if( contentType == "audio")
				return t_Audio;
			else if( contentType == "image")
				return t_Image;
			else if( contentType == "text")
				return t_Text;
			else if( contentType == "video")
				return t_Video;

			if( map_class_type.count(contentType) > 0)
				return map_class_type[contentType];
			else
				return t_Document;
		}

		void setData( string d ){ data = d; }
		void setFilename( string f ){ filename = f; }
		
		string location(const char* parent_dir){ return location( fs::path( parent_dir ) ); }
		
		string location(fs::path parent_dir){ ///We assume that parent_dir/class_type/ have already been created
			ostringstream c;
			c<<class_type;
			parent_dir/=c.str();

			ostringstream c1;
			c1<<id;
			parent_dir+=c1.str();
			return parent_dir.c_str();
		}
		string metadata_location(fs::path parent_dir){
			ostringstream c;
			c<<class_type;
			parent_dir/=c.str();

			ostringstream c1;
			c1<<id;
			parent_dir+=c1.str()+".xml";
			return parent_dir.c_str();
		}
		
		///network exchange purposes
		string serialize(){
			ostringstream ofs;
			boost::archive::text_oarchive oa( ofs );
			oa << (*this);
			return ofs.str();
		}
		 
		void unserialize( string data){
			istringstream ifs( data );
			boost::archive::text_iarchive ia( ifs );
			ia>>(*this);
		}

		virtual void save(fs::path parent_dir){
			cout<<"saving"<<endl;
			metadata->write( metadata_location(parent_dir) );
		}
		
		virtual void save(string parent_dir){ save( fs::path( parent_dir) ); } 
		
		virtual list< Ressource* > get_children(bool strict=true, list< Ressource* >acc=list< Ressource* >()){ return acc; }
};

#endif // RESSOURCE_H_INCLUDED
