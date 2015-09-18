#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on Sep 18, 2015

@author: mhuang1
'''

from py_algo.abstractmethod import abstractmethod
from py_algo.container import Container

class Queue(Container):
    def __init__(self):
        super(Queue, self).__init__()
    
    @abstractmethod
    def gethead(self): pass
    
    head = property(fget = lambda self: self.gethead())
    
    @abstractmethod
    def enqueue(self, obj): pass
    
    @abstractmethod
    def dequeue(self): pass
    