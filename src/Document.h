#ifndef DOCUMENT_H_INCLUDED
#define DOCUMENT_H_INCLUDED

#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/system/error_code.hpp>
#include "Ressource.h"



using namespace std;
namespace fs=boost::filesystem;

class Document : public Ressource{
	protected :

	public:
		Document(){}
		Document(uint64_t i){
            id          = i;
            class_type  = t_Document;
			metadata    = new Metadata( t_Document, i);
		}

		Document(uint64_t i, uint16_t s){
            id          = i;
            class_type  = t_Document;
            state       = s ;
			metadata    = new Metadata( t_Document, i);
		}

		void save(fs::path parent_dir){
			Ressource::save(parent_dir);

			if( data != "" ){
				ofstream ofs( location(parent_dir).c_str(), ofstream::binary );
				ofs<<data;
				ofs.close();
			}else if( filename != "" ){
				fs::copy(fs::path(filename.c_str()), fs::path( location(parent_dir).c_str() ));
			}
		}
};

#endif //DOCUMENT_H_INCLUDED
