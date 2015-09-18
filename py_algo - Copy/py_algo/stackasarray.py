#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on Sep 16, 2015

@author: MHuang1
'''
import sys

from py_algo.stack import Stack
from py_algo.array import Array
from py_algo.visitor import Visitor
from py_algo.iterator  import Iterator
from py_algo.exception import *

class StackAsArray(Stack):
    def __init__(self, size = 0):
        super(StackAsArray, self).__init__()
        self._array = Array(size)
        self._count = 0
        
    def purge(self):
        for i in xrange(self._array.length):
            self._array[i] = None
        self._count = 0
    
    def push(self, obj):
        if self._count == self._array.length:
            raise ContainerFull
        self._array[self._count] = obj
        self._count += 1
        
    def pop(self):
        if(self._count == 0):
            raise ContainerEmpty
        result = self._array[self._count - 1]
        self._array[self._count - 1] = None
        self._count -= 1
        return result
    
    def gettop(self):
        if self._count == 0: raise ContainerEmpty
        return self._array[self._count - 1]
    
    def accept(self, visitor):
        assert isinstance(visitor, Visitor)
        for i in xrange(self._count):
            visitor.visit(self._array[i])
            if visitor.isdone:
                return
    
    class Iterator(Iterator):
        def __init__(self, stack):
            super(StackAsArray.Iterator, self).__init__(stack)
            self._position = 0
            
        def next(self):
            if self._position >= self._container._count:
                raise StopIteration
            element = self._container._array[self._position]
            self._position = self._position + 1
            return element
        
    def __iter__(self):
        return self.Iterator(self)

    def _compareto(self, obj):
        assert isinstance(self, obj.__class__)
        raise MethodNotImplemented
        
        
        
        
        
        
        