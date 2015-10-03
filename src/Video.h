#ifndef VIDEO_H_INCLUDED
#define VIDEO_H_INCLUDED

#include <fstream>

#include <boost/filesystem.hpp>

#include "Document.h"



using namespace std;
namespace fs=boost::filesystem;

class Video : public Document{
	protected :

	public:
		Video(){}
	
		Video(uint64_t i){
            id          = i;
            class_type  = t_Video;
			metadata    = new Metadata( t_Video, i);
		}

		Video(uint64_t i, uint16_t s){
            id          = i;
            class_type  = t_Video;
            state       = s ;
			metadata    = new Metadata( t_Video, i);
		}
};

#endif //VIDEO_H_INCLUDED
