from .Document import Document
from .Ressource import RType

import shutil

class Audio( Document ):
	_type	= RType.audio
	def __init__(self, i=-1, tmp=None): 
		Document.__init__(self, i, tmp)
