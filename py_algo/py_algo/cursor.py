#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on 2015年9月19日

@author: mhuang1
'''
import sys

from py_algo.abstractmethod import abstractmethod
from py_algo.object import Object
from py_algo.exception import *

class Cursor(Object):
    
    def __init__(self, list):
        super(Cursor, self).__init()
        self._list = list
        
    @abstractmethod
    def getdata(self): pass
    
    data = property(fget = lambda self: self.getdata())
    
    @abstractmethod
    def insertafter(self, obj): pass
    
    @abstractmethod
    def insertbefore(self, obj): pass
    
    @abstractmethod
    def withdraw(self, obj): pass
    
    def _compareto(self, obj):
        assert isinstance(self, obj.__class__)
        raise MethodNotImplemented