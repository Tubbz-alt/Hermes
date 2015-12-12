from .Ressource import Ressource, RType
import shutil
import os

class Document( Ressource ):
	_type	= RType.document
	def __init__(self, i=-1, tmp=None): 
		Ressource.__init__(self, i, tmp)
		
	def save(self, parent_dir, closed=True):
		"""
		"""
		Ressource.save(self, parent_dir)
		
		if not self._tmp :
			return
			
		with open( os.path.join(self._location, "data"), 'wb') as newFile:
			self._tmp.seek(0) 
			shutil.copyfileobj(self._tmp, newFile, 32768)
		
		if closed:
			self._tmp.close()
