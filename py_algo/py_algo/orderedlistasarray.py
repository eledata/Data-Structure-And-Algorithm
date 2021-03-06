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
            if self._array[i]== obj: return i
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
        i = 0
        while i < self._count and self._array[i] != obj:
            i += 1
        return self.Cursor(self, i)      
    
    def __getitem__(self, offset):
        if offset < 0 or offset >= self._count:
            raise IndexError
        return self._array[offset]
        
    class Cursor(Cursor):
        def __init__(self, list, offset):
            super(OrderedListAsArray.Cursor, self).__init__(list)
            self._offset = offset
            
        def getdata(self):
            if self._offset <0 or self._offset >= self._list._count:
                raise IndexError
            return self._list._array[self._offset]
        
        def insertafter(self, obj):
            if self._offset <0 or self._offset >= self._list._count:
                raise IndexError
            
            if self._list._count == len(self._list._array):
                raise ContainerFull
            insertpos = self._offset + 1
            i = self._list._count
            while i > insertpos:
                self._list._array[i] = self._list._array[i - 1]
                i -=1
            self._list._array[insertpos] = obj
            self._list._count += 1
            
        def insertbefore(self, obj):
            if self._offset <0 or self._offset >= self._list._count:
                raise IndexError
            
            if self._list._count == len(self._list._array):
                raise ContainerFull
            insertpos = self._offset
            i = self._list._count
            while i > insertpos:
                self._list._array[i] = self._list._array[i - 1]
                i -=1
            self._list._array[insertpos] = obj
            self._list._count += 1                
            self._offset += 1
    
        def withdraw(self):
            if self._offset <0 or self._offset >= self._list._count:
                raise IndexError
            
            if self._list._count < 0:
                raise ContainerEmpty
            
            i = self._offset
            while i < self._list._count - 1:
                self._list._array[i] = self._list._array[i + 1]
                i +=1
                
            self._list._array[i] = None
            self._list._count -= 1            
    
    class Iterator(Iterator):
        def __init__(self, list):
            super(OrderedListAsArray.Iterator, self).__init__(list)
            self._position = -1
            
        def next(self):
            self._position += 1
            if self._position == self._container._count:
                self._position = -1
                raise StopIteration
            return self._container._array[self._position]
        
    def __iter__(self):
        return self.Iterator(self)

    def _compareto(self, obj):
        assert isinstance(self, obj.__class__)
        raise MethodNotImplemented
    
    
    
    
    
    
    
    
    
            
                
    