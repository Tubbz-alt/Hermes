#include "Document.h"

void Document::save(fs::path parent_dir){
	Ressource::save(parent_dir);
    cout<<location(parent_dir).c_str()<<endl;
	ofstream ofs( location(parent_dir).c_str(), ofstream::binary );
	ofs<<data;
	ofs.close();
}
