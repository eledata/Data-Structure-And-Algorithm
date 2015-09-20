#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on 2015年9月19日

@author: mhuang1
'''

import sys
import  exceptions

from py_algo.orderedlist import OrderedList
from py_algo.array import Array
from py_algo.cursor import Cursor
from py_algo.iterator import Iterator
from py_algo.visitor import Visitor
from py_algo.exception import *

class  OrderedListAsArray(OrderedList):
    
    def __init__(self, size = 0):
        super(OrderedListAsArray, self).__init__()
        self._array = Array(size)
        
    def insert(self, obj):
        if self._count > len(self._array): raise ContainerFull
        self._array[self._count] = obj
        self._count += 1
        
    def purge(self):
        while self._count > 0:
            self._array[self._count] = None
            self._count -= 1
            
    def getisfull(self):
        return self._count == len(self._array)
    
    def accept(self, visitor):
        assert isinstance(visitor, Visitor)
        for i in xrange(self._count):
            visitor.visit(self._array[i])
            if visitor.isdone:
                return
    
    def __contains__(self, obj):
        for i in xrange(self._count):
            if self._array[i]== obj: return True
        return False
    
    def find(self, obj):
        for i in xrange(self._count):
            if self._array[i]== obj: return self._array[i]
        return None
    
    def withdraw(self, obj):
        if self._count == 0: raise ContainerEmpty
        i = 0
        while i < self._count and self._array[i] is not obj:
            i += 1
        if i == self._count:
            raise KeyError
        while i < self._count - 1:
            self._array[i] = self._array[i + 1]
            i += 1
        self._array[i] = None
        self._count -= 1
        
    def findposition(self, obj):
        for i in xrange(self._count):
            if self._array[i]== obj: return 
        return None       
    
    
    class Cursor(Cursor):
        def __init__(self, list, offset):
            super(OrderedListAsArray.Cursor, self).__init__(list)
            self._offset = offset
            
        
    
    
    
    
    
    
    
    
    
    
    
    
            
                
    