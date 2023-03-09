#!usr/bin/env python
import cppyy

def pythonize_vector(klass, name):
    if 'vector<' in name:
        old_init = klass.__init__
        def pyinit(self, *args):
            if len(args) == 1:
                try:
                    iter(args[0])
                    old_init(self)
                    self.reserve(len(args[0]))
                    self += args[0]
                    return
                except TypeError:
                    pass
            return old_init(self, *args)
        klass.__init__ = pyinit

cppyy.py.add_pythonization(pythonize_vector, 'std')

from cppyy.gbl.std import vector, pair
from cppyy.gbl.std import map as dct
