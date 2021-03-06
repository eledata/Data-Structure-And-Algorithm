#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on Sep 16, 2015

@author: MHuang1
'''

from py_algo.abstractmethod import abstractmethod
from py_algo.container import Container

class Stack(Container):
    def __init__(self):
        super(Container, self).__init__()
        
    @abstractmethod
    def gettop(self): pass
    top = property(fget = lambda self: self.gettop())
    
    @abstractmethod
    def push(self, obj): pass
    
    @abstractmethod
    def pop(self): pass