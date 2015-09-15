#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on Sep 15, 2015

@author: mhuang1
'''
import sys
from exception import *

class LinkedList(object):
    
    def __init__(self):
        self._head = None
        self._tail = None
        
    def purge(self):
        self._head = None
        self._tail = None
    
    class Element(object):
        def __init__(self, list, data, next):
            self._list = list
            self._data = data
            self._next = next
            
        def getdata(self):
            return self._data
        value = property(fget = lambda self: self.getdata())
        
        def getnext(self):
            return self._next
        next = property(fget = lambda self: self.getnext())
        
        def insertafter(self, data):
            self._next = LinkedList.Element(self._list, data, self._next)
            if self._list._tail is self:
                self._list._tail = self._next
        
        def insertbefore(self, data):
            tmp = LinkedList.Element(self._list, data, self)
            if self is self._list._head:
                self._list._head = tmp
            else:
                pre = self._list._head
                while pre is not None and pre._next is not self:
                    pre = pre._next
                pre._next = tmp
                
            
            
            
            
            
            
            
            
            
            
            