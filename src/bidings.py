from pybindgen import *

def generate(file_):
	mod = Module('pyHermes')


	mod.add_include('<boost/filesystem.hpp>')
	
	boost = mod.add_cpp_namespace('boost')
	fs = boost.add_cpp_namespace('filesystem')
	fs.add_class('path')
	
	mod.add_include('<string>')
	mod.add_include('<list>')

	


	#mod.add_include('"string"')
	mod.add_container('std::list<std::string>', 'std::string', 'list') # declare a container only once

	#Manager
	mod.add_include('"SQLManager.h"')
	manager = mod.add_class('SQLManager', allow_subclassing=True)


	#Metadata
	mod.add_include('"Metadata.h"')
	metadata = mod.add_class('Metadata')
	metadata.add_constructor([param('int', 'c'), param('int', 'i')])
	metadata.add_method('get', retval('std::string'), [param('std::string', 'key')])
	metadata.add_method('set', None, [param('std::string','key'), param('std::string', 'value')])
	metadata.add_method('addReference', None, [param('int','c'), param('int', 'i')])
	metadata.add_method('write', None, [param('std::string','location')], is_virtual=True)
	metadata.add_method('hydrate', None, [param('std::string','location')], is_virtual=True)



	#Ressource
	mod.add_include('"Ressource.h"')

	mod.add_enum('class_type', ['t_Directory', 't_Document', 't_Text', 't_Video', 't_Image', 't_Audio']) 
		
	ressource = mod.add_class('Ressource', allow_subclassing=True)
	ressource.add_constructor([param('int', 'i'), param('int', 'c')])
	ressource.add_method('getId', retval('int'), [])
	ressource.add_method('getClass_type', retval('int'), [])
	ressource.add_method('getState', retval('int'), [])
	ressource.add_method('getMetadata',retval('Metadata *', caller_owns_return=True), [])
	ressource.add_method('setId', None, [param('int','i')])
	ressource.add_method('setClass_type', None, [param('int','c')])
	ressource.add_method('setState', None, [param('int','s')])
	ressource.add_method('setData', None, [param('std::string','d')])
	ressource.add_method('setFilename', None, [param('std::string','f')])
	ressource.add_method('setData', None, [param('std::string','d')])
	ressource.add_method('setMetadata', None, [param('Metadata *','m', transfer_ownership=True)])
	ressource.add_method('serialize', retval('std::string'), [])
	ressource.add_method('unserialize', None, [param('std::string','data')])
	ressource.add_method('save', None, [param('std::string','parent_dir')], is_virtual=True)
	
	ressource.add_method('location', retval("std::string"), [param('std::string','parent_dir')])
	

	ressource.add_method('contentType2ClassType', retval("int"), [param('std::string','contentType')])


	#Document
	mod.add_include('"Document.h"')
	document = mod.add_class('Document', allow_subclassing=True)
	document.add_constructor([param('int', 'i')])
	document.add_method('getId', retval('int'), [])
	document.add_method('getClass_type', retval('int'), [])
	document.add_method('getState', retval('int'), [])
	document.add_method('getMetadata',retval('Metadata *', caller_owns_return=True), [])
	document.add_method('setId', None, [param('int','i')])
	document.add_method('setClass_type', None, [param('int','c')])
	document.add_method('setState', None, [param('int','s')])
	document.add_method('setData', None, [param('std::string','d')])
	document.add_method('setFilename', None, [param('std::string','f')])
	document.add_method('setData', None, [param('std::string','d')])
	document.add_method('setMetadata', None, [param('Metadata *','m', transfer_ownership=True)])
	document.add_method('serialize', retval('std::string'), [])
	document.add_method('unserialize', None, [param('std::string','data')])
	document.add_method('save', None, [param('std::string','parent_dir')], is_virtual=True)
	
	ressource.add_method('location', retval("std::string"), [param('std::string','parent_dir')])

	
	document.add_method('contentType2ClassType', retval("int"), [param('std::string','contentType')])

	
	#Text
	mod.add_include('"Text.h"')
	text = mod.add_class('Text')
	text.add_constructor([param('int', 'i')])
	text.add_method('getId', retval('int'), [])
	text.add_method('getClass_type', retval('int'), [])
	text.add_method('getState', retval('int'), [])
	text.add_method('getMetadata',retval('Metadata *', caller_owns_return=True), [])
	text.add_method('setId', None, [param('int','i')])
	text.add_method('setClass_type', None, [param('int','c')])
	text.add_method('setState', None, [param('int','s')])
	text.add_method('setData', None, [param('std::string','d')])
	text.add_method('setFilename', None, [param('std::string','f')])
	text.add_method('setData', None, [param('std::string','d')])
	text.add_method('setMetadata', None, [param('Metadata *','m', transfer_ownership=True)])
	text.add_method('serialize', retval('std::string'), [])
	text.add_method('unserialize', None, [param('std::string','data')])
	text.add_method('save', None, [param('std::string','parent_dir')], is_virtual=True)
	
	ressource.add_method('location', retval("std::string"), [param('std::string','parent_dir')])
	
	text.add_method('contentType2ClassType', retval("int"), [param('std::string','contentType')])

	
	#Image
	mod.add_include('"Image.h"')
	image = mod.add_class('Image')
	image.add_constructor([param('int', 'i')])
	image.add_method('getId', retval('int'), [])
	image.add_method('getClass_type', retval('int'), [])
	image.add_method('getState', retval('int'), [])
	image.add_method('getMetadata',retval('Metadata *', caller_owns_return=True), [])
	image.add_method('setId', None, [param('int','i')])
	image.add_method('setClass_type', None, [param('int','c')])
	image.add_method('setState', None, [param('int','s')])
	image.add_method('setData', None, [param('std::string','d')])
	image.add_method('setFilename', None, [param('std::string','f')])
	image.add_method('setData', None, [param('std::string','d')])
	image.add_method('setMetadata', None, [param('Metadata *','m', transfer_ownership=True)])
	image.add_method('serialize', retval('std::string'), [])
	image.add_method('unserialize', None, [param('std::string','data')])
	image.add_method('save', None, [param('std::string','parent_dir')], is_virtual=True)
	
	ressource.add_method('location', retval("std::string"), [param('std::string','parent_dir')])
	
	image.add_method('contentType2ClassType', retval("int"), [param('std::string','contentType')])

	
	#Audio
	mod.add_include('"Audio.h"')
	audio = mod.add_class('Audio')
	audio.add_constructor([param('int', 'i')])
	audio.add_method('getId', retval('int'), [])
	audio.add_method('getClass_type', retval('int'), [])
	audio.add_method('getState', retval('int'), [])
	audio.add_method('getMetadata',retval('Metadata *', caller_owns_return=True), [])
	audio.add_method('setId', None, [param('int','i')])
	audio.add_method('setClass_type', None, [param('int','c')])
	audio.add_method('setState', None, [param('int','s')])
	audio.add_method('setData', None, [param('std::string','d')])
	audio.add_method('setFilename', None, [param('std::string','f')])
	audio.add_method('setData', None, [param('std::string','d')])
	audio.add_method('setMetadata', None, [param('Metadata *','m', transfer_ownership=True)])
	audio.add_method('serialize', retval('std::string'), [])
	audio.add_method('unserialize', None, [param('std::string','data')])
	audio.add_method('save', None, [param('std::string','parent_dir')], is_virtual=True)
	
	ressource.add_method('location', retval("std::string"), [param('std::string','parent_dir')])
	
	audio.add_method('contentType2ClassType', retval("int"), [param('std::string','contentType')])
	
	#Video
	mod.add_include('"Video.h"')
	video = mod.add_class('Video')
	video.add_constructor([param('int', 'i')])
	video.add_method('getId', retval('int'), [])
	video.add_method('getClass_type', retval('int'), [])
	video.add_method('getState', retval('int'), [])
	video.add_method('getMetadata',retval('Metadata *', caller_owns_return=True), [])
	video.add_method('setId', None, [param('int','i')])
	video.add_method('setClass_type', None, [param('int','c')])
	video.add_method('setState', None, [param('int','s')])
	video.add_method('setData', None, [param('std::string','d')])
	video.add_method('setFilename', None, [param('std::string','f')])
	video.add_method('setData', None, [param('std::string','d')])
	video.add_method('setMetadata', None, [param('Metadata *','m', transfer_ownership=True)])
	video.add_method('serialize', retval('std::string'), [])
	video.add_method('unserialize', None, [param('std::string','data')])
	video.add_method('save', None, [param('std::string','parent_dir')], is_virtual=True)
	
	ressource.add_method('location', retval("std::string"), [param('std::string','parent_dir')])
	
	video.add_method('contentType2ClassType', retval("int"), [param('std::string','contentType')])

	#Directory	
	mod.add_include('"Directory.h"')
	directory = mod.add_class('Directory')
	directory.add_constructor([param('int', 'i')])
	directory.add_method('getId', retval('int'), [])
	directory.add_method('getClass_type', retval('int'), [])
	directory.add_method('getState', retval('int'), [])
	directory.add_method('getMetadata',retval('Metadata *', caller_owns_return=True), [])
	directory.add_method('setId', None, [param('int','i')])
	directory.add_method('setClass_type', None, [param('int','c')])
	directory.add_method('setState', None, [param('int','s')])
	directory.add_method('setData', None, [param('std::string','d')])
	directory.add_method('setFilename', None, [param('std::string','f')])
	directory.add_method('setData', None, [param('std::string','d')])
	directory.add_method('setMetadata', None, [param('Metadata *','m', transfer_ownership=True)])
	directory.add_method('serialize', retval('std::string'), [])
	directory.add_method('unserialize', None, [param('std::string','data')])
	directory.add_method('save', None, [param('std::string','parent_dir')], is_virtual=True)
	
	ressource.add_method('location', retval("std::string"), [param('std::string','parent_dir')])
	
	directory.add_method('contentType2ClassType', retval("int"), [param('std::string','contentType')])
	directory.add_method('add_child', None, [param('Ressource *', 'r',transfer_ownership=True)] )
	
	#directory.add_method('init_python_children', None, [param('bool','strict')])
	#directory.add_method('python_reset_current', None, [])
	#directory.add_method('python_get_child', retval("Ressource*", caller_owns_return=True), [])
	#directory.add_method('python_set_child', None, [param('Ressource *','r', transfer_ownership=True)])
	#directory.add_method('python_next_child', None, [])

	#SQLRessourceManager
	#mod.adds_container('std::vector<Ressource >', 'Ressource ', 'vector', custom_name="vR") # declare a container only once
	#mod.add_container('std::vector<Document >', 'Document ', 'vector', custom_name="vR_doc") # declare a container only once
	#mod.add_container('std::vector<Directory >', 'Directory ', 'vector', custom_name="vR_dir") # declare a container only once
	#mod.add_container('std::vector<Text >', 'Text ', 'vector', custom_name="vR_t") # declare a container only once
	#mod.add_container('std::vector<Image >', 'Image ', 'vector', custom_name="vR_i") # declare a container only once
	#mod.add_container('std::vector<Audio >', 'Audio ', 'vector', custom_name="vR_a") # declare a container only once
	#mod.add_container('std::vector<Video >', 'Video ', 'vector', custom_name="vR_v") # declare a container only once

	mod.add_include('"SQLRessourceManager.h"')
	sqlRessourceManager = mod.add_class('SQLRessourceManager')
	sqlRessourceManager.add_constructor([])
	sqlRessourceManager.add_method('getTable', retval('std::string'), [param('uint64_t', 'class_type') ])
	sqlRessourceManager.add_method('add_acc', None, [param('Ressource*', 'r', transfer_ownership=False)])
	sqlRessourceManager.add_method('add_acc', None, [param('Document*', 'r', transfer_ownership=False)])
	sqlRessourceManager.add_method('add_acc', None, [param('Text*', 'r', transfer_ownership=False)])
	sqlRessourceManager.add_method('add_acc', None, [param('Image*', 'r', transfer_ownership=False)])
	sqlRessourceManager.add_method('add_acc', None, [param('Video*', 'r', transfer_ownership=False)])
	sqlRessourceManager.add_method('add_acc', None, [param('Audio*', 'r', transfer_ownership=False)])
	sqlRessourceManager.add_method('add_acc', None, [param('Directory*', 'r', transfer_ownership=False)])
	sqlRessourceManager.add_method('insert_with_acc', retval('int'), [param('uint16_t', 'class_type')])
	#sqlRessourceManager.add_method('insert', retval('uint64_t'), [param('uint16_t', 'class_type'),param('std::vector< Ressource >', 'ressources') ])
	#sqlRessourceManager.add_method('insert', retval('uint64_t'), [param('uint16_t', 'class_type'),param('std::vector< Document >', 'ressources') ])
	#sqlRessourceManager.add_method('insert', retval('uint64_t'), [param('uint16_t', 'class_type'),param('std::vector< Text >', 'ressources') ])
	#sqlRessourceManager.add_method('insert', retval('uint64_t'), [param('uint16_t', 'class_type'),param('std::vector< Image >', 'ressources') ])
	#sqlRessourceManager.add_method('insert', retval('uint64_t'), [param('uint16_t', 'class_type'),param('std::vector< Video >', 'ressources') ])
	#sqlRessourceManager.add_method('insert', retval('uint64_t'), [param('uint16_t', 'class_type'),param('std::vector< Audio >', 'ressources') ])
	#sqlRessourceManager.add_method('insert', retval('uint64_t'), [param('uint16_t', 'class_type'),param('std::vector< Directory >', 'ressources') ])

	ressource.add_method('location', retval("std::string"), [param('std::string','parent_dir')])

	mod.generate(file_)
