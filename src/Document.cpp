#include "Document.h"

void Document::save(fs::path parent_dir){
	Ressource::save(parent_dir);
	
	ofsteam ofs( location().c_str(), ofstream::binary );
	ofs<<data;
	ofs.close();
}
