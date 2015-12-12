from .Document import Document
from .Ressource import RType

import shutil

class Text( Document ):
	_type	= RType.text
	def __init__(self, i=-1, tmp=None): 
		Document.__init__(self, i, tmp)
