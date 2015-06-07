#ifndef DOCUMENT_H_INCLUDED
#define DOCUMENT_H_INCLUDED

#include <fstream>

#include "Ressource.h"

using namespace std;

class Document : public Ressource{
	protected :

	public:
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

		void save(fs::path parent_dir);
};

#endif //DOCUMENT_H_INCLUDED
