#ifndef Directory_H_INCLUDED
#define Directory_H_INCLUDED

#include <fstream>

#include <boost/filesystem.hpp>
#include <list>

#include "Ressource.h"
#include "MetadataDirectory.h"



using namespace std;
namespace fs=boost::filesystem;

class Directory : public Ressource{
	protected :
		list< Ressource* > children; ///Not physical representation, only in metadata file
		 
		list< Ressource* > python_children;
		list< Ressource*>::iterator current;
	public:
		Directory(){}
		
		Directory(uint64_t i){
            id          = i;
            class_type  = t_Directory;
			metadata    = new MetadataDirectory( t_Directory, i);
		}

		Directory(uint64_t i, uint16_t s){
            id          = i;
            class_type  = t_Directory;
            state       = s ;
			metadata    = new MetadataDirectory( t_Directory, i);
		}
		
		~Directory(){
			if( metadata != NULL )
				delete metadata;
				
			for(list<Ressource *>::iterator it = children.begin(); it != children.end() ; it++)
				if( (*it)!= NULL)
					delete (*it);
		}
		
		void add_child( Ressource* r){
			children.push_back( r );
		}
		
		list< Ressource* > get_children(bool strict=true, list< Ressource* >acc=list< Ressource* >()){ ///strict : not subdirectories fetching
			if( strict )
				return children;
			
			for(list<Ressource *>::iterator it = children.begin(); it != children.end() ; it++){
				(*it)->get_children(strict, acc);	
				acc.push_back( *it );
			}
			return acc;
		}
		
		///Pour fucking python bindgen
		void init_python_children(bool strict=false){
			python_children = get_children();
			current			= python_children.begin();
		}
		
		void python_reset_current(){ current = python_children.begin(); }
		
		bool python_next_child(){
			if( current != python_children.end() )
				current ++;
				return current != python_children.end();
			return false;
		}
		
		Ressource* python_get_child(){
			return *current;
		} 
		
		void python_set_child(Ressource* r){
			delete (*current);
			*current	= r;
		}
	
		void save(fs::path parent_dir){
			list< pair<uint16_t, uint64_t> > metadata_children=list< pair<uint16_t, uint64_t> >( children.size() );
			for(list<Ressource *>::iterator it = children.begin(); it != children.end() ; it++)
				metadata_children.push_back( pair<uint16_t, uint64_t>( (*it)->getId(), (*it)->getClass_type() ) );
			
			metadata->extend_children( metadata_children );
			
			Ressource::save(parent_dir);
		}		
};

#endif //Directory_H_INCLUDED
