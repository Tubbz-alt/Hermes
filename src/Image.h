#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include <fstream>

#include <boost/filesystem.hpp>

#include "Document.h"



using namespace std;
namespace fs=boost::filesystem;

class Image : public Document{
	protected :

	public:
		Image(){}
	
		Image(uint64_t i){
            id          = i;
            class_type  = t_Image;
			metadata    = new Metadata( t_Image, i);
		}

		Image(uint64_t i, uint16_t s){
            id          = i;
            class_type  = t_Image;
            state       = s ;
			metadata    = new Metadata( t_Image, i);
		}
};

#endif //IMAGE_H_INCLUDED
