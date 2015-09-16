#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on Sep 16, 2015

@author: MHuang1
'''
import sys

from Object import Object
from abstractmethod import abstractmethod
from exception import MethodNotImplemented

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