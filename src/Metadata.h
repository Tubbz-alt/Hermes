#ifndef METADATA_H_INCLUDED
#define METADATA_H_INCLUDED

#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <boost/filesystem.hpp>

#include <libxml++/libxml++.h>

using namespace std;
namespace fs=boost::filesystem;

class Metadata{
	protected:
		string name ="";

		uint16_t class_type = 0;
		uint64_t id =0; //ressource id

		map<string,string> fields;

		///storage
		pair<uint16_t, uint64_t> reference; //if needed : (classe_type, id)
		//conteiners;

	public:
		Metadata(){
			reference = pair<uint16_t, uint64_t>(0,0);

		}
	
		Metadata(uint16_t c, uint64_t i) : class_type(c), id(i), name("ressource"){
			reference = pair<uint16_t, uint64_t>(0,0);
		}

		virtual ~Metadata(){}

		void setId(uint64_t i){ id = i; }
		
		uint64_t getId(){ return id; }
		uint16_t getClass_type(){ return class_type; }

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
		template<typename T>
		string toStr(T value){
			ostringstream o;
			o<<value;
			return o.str();
		}
		
		void buildXml(xmlpp::Document& xml ){
			xmlpp::Element* root = xml.create_root_node(name);
			
			root->set_attribute("class", toStr(class_type) );
			root->set_attribute("id", toStr(id) );

			for( map<string,string>::iterator it=fields.begin(); it != fields.end(); it++){
				xmlpp::Element* field = root->add_child( toStr(it->first) );
				field->add_child_text( it->second );
			}

			if( reference.first != 0 ){
				xmlpp::Element* field = root->add_child( "reference" );
				field->set_attribute("class", toStr(reference.first) );
				field->set_attribute("id", toStr(reference.second) );
			}
		}
		 
		virtual void write(string location){
			xmlpp::Document xml("1.0");
			buildXml( xml );
			xml.write_to_file(location); 
		}
		
		/**
		 * @brief hydrate current object from file
		 */
		virtual void hydrate(string location){ /// Non tester, en theorie ne marche pas encore
			xmlpp::DomParser parser;
			parser.parse_file(location);
			if(parser){
				const xmlpp::Node* node = parser.get_document()->get_root_node(); //deleted by DomParser.
			    std::vector< xmlpp::Node* > nodes = node->find( "/" + name ); //xpath
				if ( nodes.size() != 1 )
					throw "a definir";
				
				const xmlpp::Element* elmt = dynamic_cast<const xmlpp::Element*>( nodes[0] );
				istringstream ( elmt->get_attribute("class")->get_value() ) >> class_type;
				istringstream ( elmt->get_attribute("id")->get_value() ) >> id;
				
				std::list< xmlpp::Node* > children = elmt->get_children();
				for(int k=0; k<children.size(); k++){
					const xmlpp::Element* tmpElmt = dynamic_cast<const xmlpp::Element*>( node );
					if( tmpElmt){
						if( tmpElmt->get_name() != "reference")
							set( tmpElmt->get_name(), tmpElmt->get_child_text()->get_content() ); 
						else{
							stringstream ( tmpElmt->get_attribute("class")->get_value() ) >> reference.first;
							stringstream ( tmpElmt->get_attribute("id")->get_value() ) >> reference.second;
						}
					}
					
				}				      
			}
		}
		
		virtual void extend_children( list< pair<uint16_t, uint64_t> >& c){}
};
#endif //METADATA_H_INCLUDED
