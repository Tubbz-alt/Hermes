#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include <fstream>

#include <boost/filesystem.hpp>

#include "Document.h"



using namespace std;
namespace fs=boost::filesystem;

class Text : public Document{
	protected :

	public:
		Text(){}
		
		Text(uint64_t i){
            id          = i;
            class_type  = t_Text;
			metadata    = new Metadata( t_Text, i);
		}

		Text(uint64_t i, uint16_t s){
            id          = i;
            class_type  = t_Text;
            state       = s ;
			metadata    = new Metadata( t_Text, i);
		}
};

#endif //TEXT_H_INCLUDED
