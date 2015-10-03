#ifndef AUDIO_H_INCLUDED
#define AUDIO_H_INCLUDED

#include <fstream>

#include <boost/filesystem.hpp>

#include "Document.h"



using namespace std;
namespace fs=boost::filesystem;

class Audio : public Document{
	protected :

	public:
		Audio(){}
		
		Audio(uint64_t i){
            id          = i;
            class_type  = t_Audio;
			metadata    = new Metadata( t_Audio, i);
		}

		Audio(uint64_t i, uint16_t s){
            id          = i;
            class_type  = t_Audio;
            state       = s ;
			metadata    = new Metadata( t_Audio, i);
		}
};

#endif //AUDIO_H_INCLUDED
