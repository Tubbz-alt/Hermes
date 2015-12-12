import os
import tempfile
import mimetypes
import sys
from hashlib import sha224


from .Ressource import Ressource, Metadata
from .Document import Document
from .Text import Text
from .Video import Video
from .Audio import Audio
from .Image import Image	
from .Directory import Directory

sys.setrecursionlimit( 10000 )
mimetypes.init()

DEFAULT_CONTENT_TYPE = "application/octet-stream"

map_contentTypes2Ressource={
	"application/javascript"	: Text,
	"application/ogg"        	: Video,
	"application/xhtml+xml"  	: Text,
	"application/json"       	: Text,
	"application/xml"        	: Text,
	"application/x-directory"	: Directory,
	"inode/directory"			: Directory,
	"text/directory"			: Directory
}

def contentType2Ressource(contentType):
	if contentType in map_contentTypes2Ressource :
		return map_contentTypes2Ressource[ contentType ]()
	
	token 	= contentType.split("/")[0]
	
	if( token == "audio"):
		return Audio()
	elif( token == "image"):
		return Image()
	elif( token == "text"):
		return Text()
	elif( token == "video"):
		return Video()

	return Document()




def hashfile_aux(afile, hasher, blocksize=65536):
	afile.seek(0)
	buff = afile.read(blocksize)

	while buff :
		hasher.update( buff )
		buff = afile.read(blocksize)
		
	afile.seek(0)
		
def hashfile(afile, hasher, blocksize=65536):
	hashfile_aux(afile, hasher, blocksize)
	return hasher.hexdigest()

##os.scandir pour python 3.4
def hashdir(path, hasher, blocksize=65536): 
	buff = ""
	for path, dirs, files in os.walk(path):
		for filename in files:
			hashfile_aux( open(os.path.join(path, filename), "rb") , hasher, blocksize)			
	return hasher.hexdigest()
				
def filesize(afile):
	current = afile.tell()
	afile.seek(0, os.SEEK_END)
	size = afile.tell()
	afile.seek(current, os.SEEK_SET)
	return size
	
def dirsize(path):
	size = 0
	for path, dirs, files in os.walk(path):
		for filename in files:
			size += os.path.getsize( os.path.join(path, filename) )
		for dirname in dirs:
			size += dirsize( os.path.join(path, dirname) )
			
	return size
	
#def dirsize(path):
	#size = 0
	#for entry in os.scandir(path):
		#if entry.is_file():		
			#size += os.path.getsize( os.path.join(path, entry.name) )
		#elif entry.is_dir() and entry.name != "."  and entry.name != "..":
			#size += dirsize( os.path.join(path, entry.name) )
	#return size
    	
def build(tmp, contentType):
		"""
			tmp : temporaryDirector, str => directory
					temporaryFile,file => file
			parent : if parent : parent.add_child(ressource) for tail recursion
		"""
		if type( tmp ) == tempfile.TemporaryDirectory or type( tmp ) == str : 
			if type( tmp ) == str :
				h_sha224 	= hashdir(tmp, sha224())
				size		= dirsize(tmp)
			else:
				h_sha224 	= hashdir(tmp.name, sha224())
				size		= dirsize(tmp.name)
		else : 
			h_sha224 	= hashfile(tmp, sha224())
			size		= filesize(tmp)
			
			
		ct_list		= contentType.split(";")
		contentType = ct_list[0].strip()
		charset 	= ( ct_list[1].strip() if len(ct_list)>1 else "")			
		
		
		ressource		= contentType2Ressource( contentType )
		ressource._tmp	= tmp
		metadata 		= Metadata( ressource )
		
		
		metadata["contentType"]	= contentType
		metadata["sha224"]		= h_sha224
		metadata["size"]		= size
					
		
		if type( tmp ) == tempfile.TemporaryDirectory or type( tmp ) == str :
			path 	= (tmp if type(tmp) == str else tmp.name)
					
			#recursive construction for dir, will crash if dept dir >999
			local_path, local_dirs, local_files = os.walk(path , topdown=True).__next__() #only the first layer

			for local_dir in local_dirs:
				l_ressource = build( os.path.join(local_path, local_dir), 
					"inode/directory")
				ressource.add_child( l_ressource )
			
			for local_file in local_files:
				location = os.path.join(local_path, local_file) 
				
				local_ct = mimetypes.guess_type(location, strict=False)[0] 
				if not local_ct :
					local_ct = "application/octet-stream"
					
				l_ressource =  build( open(location, "rb"), local_ct)
				ressource.add_child( l_ressource )
			
		
		return ressource

		
