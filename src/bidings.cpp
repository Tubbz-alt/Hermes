#include <boost/python.hpp>

#include "Ressource.h"
#include "Ressource.cpp"
#include "Document.h"
#include "Document.cpp"
#include "Metadata.h"
#include "Metadata.cpp"

BOOST_PYTHON_MODULE(libpyRessource){
	using namespace boost::python;
	
	class_<Ressource>("Ressource", init<int, int, int>)
		.def("setData", &Ressource::setData) 
		.def("save", &Ressource::save);
		
	class_<Metadata>("Metadata", init<>())
		.def("get", &Metadata::get)
		.def("set", &Metadata::set)
		;
	class_<RessourceHandler>("RessourceHandler", init<ChunkManager*>())
		.def("buildRevision", &RessourceHandler::buildRevision)
		.def("newRevision", &RessourceHandler::newRevision)
		;
}
