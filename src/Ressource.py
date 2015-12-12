#from enum import IntEnum
import os
import collections
import json
from enum import IntEnum
from time import time
from urllib.parse import urljoin
from hashlib import sha224
from random import random

class RType(IntEnum):
	ressource	= -1
	document	= 0 
	text		= 1
	video		= 2
	image		= 3
	audio 		= 4
	directory	= 5

class Metadata( collections.UserDict ) :
	_ressource 	= None
	
	def __init__(self, ressource):
		collections.UserDict.__init__(self)
		ressource._metadata = self
		self._ressource	= ressource
		
		self.data["_id"]=ressource._id
		self.data["_type"]=ressource._type
	
	def to_json(self):
		return json.dumps( self.data )

	def save(self, path):
		with open(path, "w") as f:
			return json.dump( self.data, f)
		
	def from_json(self, json_str):
		self.data = json.loads( self.data )

class Ressource:
	_id			= -1
	_type		= -1
	_tmp 		= None #Temporary[File|Directory]	
	_metadata	= None
	
	def __init__(self, i=-1, tmp=None): 
		self._id		= i
		self._tmp		= tmp
		self._children	= []
	
	def rec_children(self):
		"""
			get child of child of child ... in a ressource list 
		"""
		return []
	
	def generate_id(self, uri):
		#sha224 : p_collision pour 10**20 objets distinc : 0.0
		#time + uri : un truc uniq (si convention respecté par mast, slave, monitor)
		uniq = ''.join( [ str(time()), uri, str(self._type), 
			str(random()) ]).encode()
		self._id	= sha224( uniq ).hexdigest() #choix de la fonction de hash à faire en fct des collisions
		self._metadata.data["_id"]=self._id
		
	def generate_id_rec(self, uri):
		self.generate_id(uri)
		for child in self._children:
			child.generate_id_red( urljoin(uri+"/", str(self._id) ) )	
		
	def location(self, parent_dir):
		"""
			return parent_dir/class_type/id
			parent_dir/class_type/id:
				-metdata
				-etc..
		"""
		return os.path.join( parent_dir, str(self._type), str(self._id) )

	def metadata_location(self):
		return os.path.join( self._location, "metadata.json")	
	
	def save(self, parent_dir):
		if self._id == -1:
			raise "Error : not id for this ressource"
		self._location	= self.location( parent_dir )
		os.makedirs(self._location, mode=0o770, exist_ok=True)
		
		self._metadata.save( self.metadata_location() )		
	
	def __str__(self):
		return "Ressource : "+'|'.join([str(self._id), str(self._type)])
