#!/usr/bin/env python
import os
from distutils.core import setup, Extension
from bidings import generate

try:
    os.mkdir("build")
except OSError:
    pass
    
module_fname = os.path.join("build", "pyHermes-binding.cpp")
with open(module_fname, "wt") as file_:
    print("Generating file {}".format(module_fname))
    generate(file_)

pyHermes = Extension('pyHermes',
                     sources = [module_fname],
                     include_dirs=['.', '/usr/include/mysql', '/usr/include/mysql++', '/usr/local/include',
                     '/usr/include/glibmm-2.4',
                     '/usr/lib/x86_64-linux-gnu/glibmm-2.4/include',
                     '/usr/include/sigc++-2.0',
                     '/usr/lib/x86_64-linux-gnu/sigc++-2.0/include', 
                     '/usr/include/glib-2.0', 
                     '/usr/lib/x86_64-linux-gnu/glib-2.0/include',
                     '/usr/include/libxml++-2.6', 
                     '/usr/lib/libxml++-2.6/include', 
                     ],
                     extra_compile_args= [ '-Wall', '-std=c++11'],
                     extra_link_args=['-lmysqlpp', '-lmysqlclient'],
                     libraries=['boost_system', 
								'boost_filesystem', 
								'boost_serialization', 'boost_iostreams',
								#'boost_filesystem-mt',
								'mysqlclient', 'mysqlpp'
								, 'xml++-2.6', 'xml2', 'glibmm-2.4', 'gobject-2.0', 'sigc-2.0', 'glib-2.0' 
								],
                     library_dirs=['/opt/local/lib/', '/usr/lib/x86_64-linux-gnu']               )

setup(name='PyHermes',
      version="0.0",
      description="provides standard obj between the different parts of the athena project",
      author='severus',
      author_email='yyy@zz',
      ext_modules=[pyHermes],
     )
