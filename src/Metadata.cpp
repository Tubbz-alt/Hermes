#import "Metadata.h"

void write(string location){
	tx::XMLDocument xml;
	tx::XMLElement* root = xml.NewElement( name.c_str() );
	
	root->SetAttribute("class", class);
	root->SetAttribute("id", id);
	
	for( map<string,string>::iterator it=fields.beg(); it != fields.end(); it++){
		tx::XMLElement* field = xml.NewElement( (it->first).c_str() );
		field->setText( (it->second).c_str() );
		
		root->InsertLastChild( field );
	}
	
	if( reference.first !=-1 ){
		tx::XMLElement* field = xml.NewElement( "reference" );
		field->SetAttribute("class", reference.first);
		field->SetAttribute("id", reference.second);
	}
	
	
	xml.SaveFile( location.c_str() );
}

void hydrate(string location){
	XMLDocument doc;
    doc.LoadFile( location.c_str() );
    
    tx::XMLElement* elmt = doc.FirstChildElement( name.c_str() );
    class 	= elmt->IntAttribute( "class" );
    id		= elmt->IntAttribute( "id" );
    
    while( elmt != NULL || elmt->value() != "reference"){
		set(elmt->value(), elmt->FirstChild()->ToText()->value() );
		elmt = elmt->NextSibling()
	}
	
	if( elmt != NULL && elmt->value() == "reference" ){
		reference.first = elmt->IntAttribute( "class" );
		reference.second = elmt->IntAttribute( "id" );
	}
	
	
}
