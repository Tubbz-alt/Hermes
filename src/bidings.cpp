#include <boost/python.hpp>

#include "Ressource.h"
#include "Ressource.cpp"
#include "Document.h"
#include "Document.cpp"
#include <string>
#include <vector>
#include <stdint.h>
#include "Metadata.h"
#include "Metadata.cpp"


BOOST_PYTHON_MODULE(libpyRessource){
	using namespace boost::python;

	string	(Ressource::*p_serialize)()		= &Ressource::serialize;

	class_<Ressource>("Ressource", init<int, int>())
		.def(init<int,int,int>())
		.def("getId", &Ressource::getId)
		.def("getClass_type", &Ressource::getClass_type)
		.def("getState", &Ressource::getState)
		.def("getMetadata", &Ressource::getMetadata, return_internal_reference<>())
		.def("setId", &Ressource::setId)
		.def("setClass_type", &Ressource::setClass_type)
		.def("setState", &Ressource::setState)
		.def("setData", &Ressource::setData)
		.def("serialize", p_serialize)
		.def("unserialize", &Ressource::unserialize)
		.def("save", &Ressource::save) 
		;
	
	class_<Document, bases<Ressource> >("Document",init<int, int>())
		.def("getId", &Ressource::getId)
		.def("getClass_type", &Ressource::getClass_type)
		.def("getState", &Ressource::getState)
		.def("getMetadata", &Ressource::getMetadata, return_internal_reference<>())
		.def("setId", &Ressource::setId)
		.def("setClass_type", &Ressource::setClass_type)
		.def("setState", &Ressource::setState)
		.def("setData", &Ressource::setData)
		.def("serialize", p_serialize)
		.def("unserialize", &Ressource::unserialize)
		.def("save", &Ressource::save, &Document::save)
	;
	
	
	void	(SQLRessourceManager::*insert1)(Ressource&)		= &SQLRessourceManager::insert;
	void	(SQLRessourceManager::*insert2)(uint16_t, vector<Ressource*>&)		= &SQLRessourceManager::insert;
	
	
	Ressource	(SQLRessourceManager::*get1)(uint16_t, uint64_t)		= &SQLRessourceManager::get;
	Ressource	(SQLRessourceManager::*get2)(string, uint64_t)		= &SQLRessourceManager::get;
	vector<Ressource>	(SQLRessourceManager::*get3)(uint16_t, string, string, string, string)		= &SQLRessourceManager::get;
	vector<Ressource>	(SQLRessourceManager::*get4)(string, string, string, string, string)		= &SQLRessourceManager::get;
	vector<Ressource>	(SQLRessourceManager::*get5)(uint16_t, vector<uint64_t>&)		= &SQLRessourceManager::get;
	vector<Ressource>	(SQLRessourceManager::*get6)(string, vector<uint64_t>&)		= &SQLRessourceManager::get;
	
	class_<SQLRessourceManager>("SQLRessourceManager", init<>())
		.def("get", get1)
		.def("get", get2)
		.def("get", get3)
		.def("get", get4)
		.def("get", get5)
		.def("get", get6)
		.def("insert", insert1)
		.def("insert", insert2)
		;
	void	(Metadata::*set1)(string, int)		= &Metadata::set;
	void	(Metadata::*set2)(string, string)	= &Metadata::set;
	void	(Metadata::*set3)(string, float)	= &Metadata::set;

	class_<Metadata>("Metadata", init<int,int>())
		.def("get", &Metadata::get)
		.def("__getitem__", &Metadata::get)
		.def("set", set1)
		.def("set", set2)
		.def("set", set3)
		.def("__setitem__", set1)
		.def("__setitem__", set2)
		.def("__setitem__", set3)
		.def("addReference", &Metadata::addReference)
		;
}
