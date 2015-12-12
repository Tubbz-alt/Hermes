from .Document import Document
from .Ressource import RType

import shutil

class Video( Document ):
	_type	= RType.video
	def __init__(self, i=-1, tmp=None): 
		Document.__init__(self, i, tmp)
