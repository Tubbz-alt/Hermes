#ifndef METADATADIRECTORY_H_INCLUDED
#define METADATADIRECTORY_H_INCLUDED

#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <boost/filesystem.hpp>

#include <libxml++/libxml++.h>

#include "Metadata.h"

using namespace std;
namespace fs=boost::filesystem;

class MetadataDirectory : public Metadata{
	protected:
		string name ="";

		uint16_t class_type = 0;
		uint64_t id =0; //ressource id
		
		list< pair<uint16_t, uint64_t> > children;

	public:
		MetadataDirectory(){
			reference = pair<uint16_t, uint64_t>(0,0);

		}
	
		MetadataDirectory(uint16_t c, uint64_t i) : class_type(c), id(i), name("ressource"){
			reference = pair<uint16_t, uint64_t>(0,0);
		}


		list< pair<uint16_t, uint64_t> > getChildren(){ return children; }
		void setChildren( list< pair<uint16_t, uint64_t> >& c ){ children = c; }
		
		bool child_exists( pair<uint16_t, uint64_t>& c){
			for(list< pair<uint16_t, uint64_t> >::iterator it = children.begin(); it != children.end() ; it++)
				if( *it == c)
					return true;
			return false;
		}
		
		void extend_children( list< pair<uint16_t, uint64_t> >& c){
			for(list< pair<uint16_t, uint64_t> >::iterator it = c.begin(); it != c.end() ; it++)
				if( !child_exists( *it ) )
					children.push_back( *it );
		}
		
		void buildXml(xmlpp::Document& xml){
			Metadata::buildXml( xml ) ;
			xmlpp::Element* root = xml.get_root_node();
	
			xmlpp::Element* children_field = root->add_child( "children" );
			for( list< pair<uint16_t, uint64_t> >::iterator it=children.begin(); it != children.end(); it++){
				xmlpp::Element* field = children_field->add_child( "child" );
				field->set_attribute("class", toStr( it->first ) );
				field->set_attribute("id", toStr( it->second ) );
			}

			if( reference.first != 0 ){
				xmlpp::Element* field = root->add_child( "reference" );
				field->set_attribute("class", toStr(reference.first) );
				field->set_attribute("id", toStr(reference.second) );
			}	
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
						if( tmpElmt->get_name() == "reference" ){
							stringstream ( tmpElmt->get_attribute("class")->get_value() ) >> reference.first;
							stringstream ( tmpElmt->get_attribute("id")->get_value() ) >> reference.second;
						}else if( tmpElmt->get_name() == "child" ){
							uint64_t tmpId(0);
							uint16_t tmpClass_type(0);
							
							stringstream ( tmpElmt->get_attribute("class")->get_value() ) >> tmpClass_type;
							stringstream ( tmpElmt->get_attribute("id")->get_value() ) >> tmpId;
							
							this->children.push_back( pair<uint16_t, uint64_t>( tmpClass_type, tmpId ) );
						}else
							set( tmpElmt->get_name(), tmpElmt->get_child_text()->get_content() ); 
					}
					
				}				      
			}
		}
};
#endif //METADATADIRECTORY_H_INCLUDED
