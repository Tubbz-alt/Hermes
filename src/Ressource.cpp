#include "Ressource.h"

string Ressource::location(fs::path parent_dir){
	parent_dir/=class;
	parent_dir/=id;
	return parent_dir.str();
}

string Ressource::metadata_location(fs::path parent_dir){
	parent_dir/=class;
	parent_dir/=id;
	return (parent_dir/".xml").str();
}

void Ressource::save(fs::path parent_dir){
	metadata->write( metadata_location() );
}

string Ressource::serialize(){
	ostreamstring ofs;
	boost::archive::text_oarchive oa( ofs );
    oa << (*this);
    
    return ofs.string(); 
}

void Ressource::unserialize( string data){
	istreamstring ifs( data );
	boost::archive::text_iarchive ia( ifs );
	ia>>(*this);
}
