from .Ressource import Ressource, RType

class Directory( Ressource ):
	_type		= RType.directory

	def __init__(self, i=-1, tmp=None): 
		Ressource.__init__(self, i, tmp)
		 
	def rec_children(self):
		"""
			get child of child of child ... in a ressource list 
		"""
		l	= []
		for child in self._children:
			l.append( child )
			l.extend( child.rec_children() )
		return l
		 
	def add_child(self, child):
		self._children.append( child )
		
	def save(self, parent_dir):
		self._metadata["children"]	=  [ child._id for child in self._children ]
		Ressource.save(self, parent_dir)
		
		for child in self._children:
			child.save( parent_dir )
