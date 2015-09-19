#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on 2015年9月19日

@author: mhuang1
'''
from py_algo.abstractmethod import abstractmethod
from py_algo.queue import Queue

class Deque(Queue):
    def __init__(self):
        super(Deque, self).__init__()
        
    @abstractmethod
    def gethead(self): pass
    
    head = property(fget = lambda self: self.gethead())
    
    @abstractmethod
    def gettail(self): pass
    
    tail = property(fget = lambda self: self.gettail())
    
    @abstractmethod
    def enqueuehead(self, obj): pass
    
    def dequeuehead(self): return self.dequeue()
    
    def enqueuetail(self, obj): return self.enqueuetail(obj)
    
    @abstractmethod
    def dequeuetail(self): pass
    
    
    