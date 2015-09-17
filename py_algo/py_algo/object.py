#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on Sep 15, 2015

@author: mhuang1
'''

import sys
from py_algo.abstractmethod import abstractmethod
from py_algo.metaclass import Metaclass

class Object(object):
    
    def __init__(self):
        super(Object, self).__init__()
        
    def __cmp__(self, obj):
        if isinstance(self, obj.__class__):
            return self._compareTo(obj)
        elif isinstance(obj, self.__class__):
            return obj._compareTo(self)
        else:
            return cmp(self.__class__.__name__, obj.__class__.__name__)
    @abstractmethod
    def _compareto(self, obj): pass
    
    __metaclass__ = Metaclass
        
        