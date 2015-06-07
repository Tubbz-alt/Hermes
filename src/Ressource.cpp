#include "Ressource.h"

string Ressource::location(fs::path parent_dir){
    ostringstream c;
    c<<class_type;
	parent_dir/=c.str();

	ostringstream c1;
    c1<<id;
	parent_dir+=c1.str();
	return parent_dir.c_str();
}

string Ressource::metadata_location(fs::path parent_dir){
	ostringstream c;
    c<<class_type;
	parent_dir/=c.str();

	ostringstream c1;
    c1<<id;
	parent_dir+=c1.str()+".xml";
	return parent_dir.c_str();
}

uint16_t Ressource::getClassType(string contentType){
    map<string, uint16_t> map_class_type={
        {"application/javascript" , t_Text},
        {"application/ogg"        , t_Video},
        {"application/xhtml+xml"  , t_Text},
        {"application/json"       , t_Text},
        {"application/xml"        , t_Text}
    };
    contentType = contentType.substr(0, contentType.find_first_of("/"));

    if( contentType == "audio")
        return t_Audio;
    else if( contentType == "image")
        return t_Image;
    else if( contentType == "text")
        return t_Text;
    else if( contentType == "video")
        return t_Video;

    if( map_class_type.count(contentType) > 0)
        return map_class_type[contentType];
    else
        return t_Document;
}



void Ressource::save(fs::path parent_dir){
    cout<<"saving"<<endl;
	metadata->write( metadata_location(parent_dir) );
}

string Ressource::serialize(){
	ostringstream ofs;
	boost::archive::text_oarchive oa( ofs );
    oa << (*this);

    return ofs.str();
}

void Ressource::unserialize( string data){
	istringstream ifs( data );
	boost::archive::text_iarchive ia( ifs );
	ia>>(*this);
}


/// SQLRessourceManager
string SQLRessourceManager::getTable(uint64_t class_type){
//    map<int, string> m ={t_Directory:"directory", t_Document:"document", t_Text:"text", t_Video:"video", t_Image:"image", t_Audio:"audio"},
//	return m[ class_type ];
    return "";
}

uint16_t SQLRessourceManager::getClass_type( string table){
//	return {"directory":Directory, "document":Document, "text":Text, "video":Video, "image":Image, "audio":Audio}[ table ];
    return 0;
}

void SQLRessourceManager::insert( Ressource& ressource){
	mysqlpp::Query query = conn.query();
	query<<"INSERT INTO "<<getTable( ressource.getClass_type() )<<" VALUES ()";

	if (mysqlpp::SimpleResult res = query.execute())
		ressource.setId( (uint64_t)res.insert_id() );
	else{
		cerr << "Failed to get item list: " << query.error() << endl;
		throw "";
	}
}

void SQLRessourceManager::insert(uint16_t class_type, vector< Ressource* >& ressources ){
	if( ressources.empty() )
		return;

	mysqlpp::Query query = conn.query();
	mysqlpp::Query id_query = conn.query();

	query<<"INSERT INTO "<<getTable( class_type )<<" VALUES ";

	for(vector<Ressource* >::iterator it=ressources.begin(); it!=ressources.end(); it++){
		if( it != ressources.begin() )
			query<<", ";
		query<<"()";
	}

	if (mysqlpp::SimpleResult res = query.execute()){
		id_query<<"SELECT LAST_INSERT_ID() as id FROM "<<getTable( class_type );
		mysqlpp::StoreQueryResult id_res = id_query.store();

		uint64_t  I = (uint64_t)id_res[0]["id"];

		for( uint64_t i =0; i<ressources.size() ; i++)
			ressources[ ressources.size()-i-1 ]->setId( I-i );
	}else{
		cerr << "Failed to get item list: " << query.error() << endl;
		throw "";
	}
}

Ressource SQLRessourceManager::get(uint16_t class_type, uint64_t id){
	return get( getTable( class_type ), id );
}

Ressource SQLRessourceManager::get(string table, uint64_t id){
	stringstream idStr;
	idStr<<id;

	vector<Ressource> vect = get(table, "*", "id = "+idStr.str(), "id", "");
	if( vect.size() == 1 )
		return vect[0];
	else
		throw runtime_error("ressource not found");
}

vector<Ressource> SQLRessourceManager::get(uint16_t class_type, string fieldsNeeded, string where, string order, string limit){
	return get( getTable( class_type ), fieldsNeeded, where, order, limit );
}

vector<Ressource> SQLRessourceManager::get(string table, string fieldsNeeded, string where, string order, string limit){
	vector<mysqlpp::Row> v;
	vector< Ressource > ressources;
	mysqlpp::Query query = conn.query();
	query << "SELECT " << fieldsNeeded <<" FROM "<<table<<" WHERE "<< where <<" ORDER BY "<< order<< " "<<limit;
	mysqlpp::StoreQueryResult res = query.store();

	for(size_t i = 0; i < res.num_rows(); ++i)
		ressources.push_back( Ressource( (uint64_t)res[i]["id"], getClass_type(table) ) );

	return ressources;
}

vector<Ressource> SQLRessourceManager::get(uint16_t class_type, vector<uint64_t>& ids){
    return get( getTable( class_type ), ids );
}

vector<Ressource> SQLRessourceManager::get(string table, vector<uint64_t>& ids){
	string where = "id IN (";

	for(uint64_t i=0; i<ids.size(); i++){
		where += ( i != 0 ) ? "," : "";

		std::ostringstream id;
		id<<ids[i];
		where += id.str();
	}
	where += ")";
	return get( table, "*", where, "id", "");
}

uint64_t SQLRessourceManager::count(uint16_t class_type, string where, string order, string limit ){
	return count(getTable(class_type), where, order, limit);
}

uint64_t SQLRessourceManager::count(string table, string where, string order, string limit ){
	vector<mysqlpp::Row> v;
	mysqlpp::Query query = conn.query();
	query << "SELECT COUNT(*) AS number FROM "<< table<<" WHERE "<< where <<" ORDER BY "<< order<< " LIMIT "<<limit;
	mysqlpp::StoreQueryResult res = query.store();

	return (uint64_t)res[0]["number"];

}
