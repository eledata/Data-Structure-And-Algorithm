#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on Sep 16, 2015

@author: MHuang1
'''
import sys

from py_algo.object import Object
from py_algo.abstractmethod import abstractmethod
from py_algo.exception import MethodNotImplemented

class Iterator(Object):
    
    def __init__(self, container):
        super(Object, self).__init__()
        self._container = container

    def __iter__(self):
        return self
    
    @abstractmethod
    def next(self): pass
    
    def _compareto(self, obj):
        raise MethodNotImplemented