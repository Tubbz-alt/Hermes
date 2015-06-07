#include "Metadata.h"

void Metadata::write(string location){
	tx::XMLDocument xml;
	tx::XMLElement* root = xml.NewElement( name.c_str() );
    xml.LinkEndChild( root );


	root->SetAttribute("class", class_type);
	root->SetAttribute("id", (double)id);

	for( map<string,string>::iterator it=fields.begin(); it != fields.end(); it++){
		tx::XMLElement* field = xml.NewElement( (it->first).c_str() );
		field->SetText( (it->second).c_str() );

		root->InsertEndChild( field );
	}

	if( reference.first !=-1 ){
		tx::XMLElement* field = xml.NewElement( "reference" );
		field->SetAttribute("class", reference.first);
		field->SetAttribute("id", (double)reference.second);
	}
    tx::XMLPrinter printer;
    xml.Print( &printer );
    cout<<printer.CStr()<<endl;
    cout<<location.c_str()<<endl;
	xml.SaveFile( location.c_str() );
}

void Metadata::hydrate(string location){
	tx::XMLDocument doc;
    doc.LoadFile( location.c_str() );

    tx::XMLNode* elmt= doc.FirstChildElement( name.c_str() );
    class_type      	= elmt->ToElement()->IntAttribute( "class" );
    id		            = elmt->ToElement()->IntAttribute( "id" );

    while( elmt != NULL || elmt->Value() != "reference"){
		set(elmt->Value(), elmt->FirstChild()->ToText()->Value() );
		elmt = elmt->NextSibling();
	}

	if( elmt != NULL && elmt->Value() == "reference" ){
		reference.first = elmt->ToElement()->IntAttribute( "class" );
		reference.second = elmt->ToElement()->IntAttribute( "id" );
	}
}
