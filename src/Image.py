from .Document import Document
from .Ressource import RType

import shutil

class Image( Document ):
	_type	= RType.image
	def __init__(self, i=-1, tmp=None): 
		Document.__init__(self, i, tmp)
