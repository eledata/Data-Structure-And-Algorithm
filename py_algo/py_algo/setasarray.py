#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on Sep 28, 2015

@author: MHuang1
'''

import sys

from py_algo.set import Set
from py_algo.array import Array
from py_algo.iterator import Iterator
from py_algo.visitor import Visitor

class SetAsArray(Set):
    
    def __init__(self, n):
        super(SetAsArray, self).__init__(n)
        self._array = Array(self._universeSize)
        for item in xrange(0, self._universeSize):
            self._array[item] = False
    
    def insert(self, item):
        self._array[item] = True
    
    def __contains__(self, item):
        return self._array[item]
    
    def withdraw(self, item):
        self._array[item] = False
        
    def getisempty(self):
        for item in xrange(0, self._universeSize):
            if self._array[item] is True:
                return False
        return True
    
    def getisfull(self):
        for item in xrange(0, self._universeSize):
            if self._array[item] is False:
                return True
        return False        
    
    def purge(self):
        for item in xrange(0, self._universeSize):
            self._array[item] = False

    def accept(self, visitor):
        assert isinstance(visitor, Visitor)
        for item in xrange(0, self._universeSize):
            if item in self:
                visitor.visit(item)

    def getcount(self):
        count = 0
        for item in xrange(0, self._universeSize):
            if self._array[item] is True:
                count += 1
        return count
    
    def __or__(self, set):
        assert isinstance(set, SetAsArray)
        print "__or__"
        result = SetAsArray(self._universeSize)
        for i in  xrange(0, self._universeSize):
            result._array[i] = self._array[i] or set._array[i]
        return result
        
    def __and__(self, set):
        assert isinstance(set, SetAsArray)
        print "__and__"
        result = SetAsArray(self._universeSize)
        for i in  xrange(0, self._universeSize):
            result._array[i] = self._array[i] and set._array[i]
        return result       

    def __sub__(self, set):
        assert isinstance(set, SetAsArray)
        print "__sub__"
        result = SetAsArray(self._universeSize)
        for i in  xrange(0, self._universeSize):
            result._array[i] = self._array[i] and not set._array[i]
        return result


    def __eq__(self, set):
        assert isinstance(set, SetAsArray)
        print "__eq__"
        result = SetAsArray(self._universeSize)
        for i in  xrange(0, self._universeSize):
            if self._array[i] != set._array[i]:
                return False
        return True


    def __le__(self, set): 
        assert isinstance(set, SetAsArray)
        print "__le__"
        result = SetAsArray(self._universeSize)
        for i in  xrange(0, self._universeSize):
            if self._array[i] and not set._array[i]:
                return False
        return True
    
    class Iterator(Iterator):
        def __init__(self, set):
            super(SetAsArray.Iterator, self).__init__(set)
            self._item = -1
        
        def next(self):
            self._item += 1
            while self._item < self._container._universeSize:
                if self._item in self._container:
                    break
                self._item += 1
            
            if self._item == self._container._universeSize:
                self._item = -1
                raise StopIteration
            
            return self._item
        
    def __iter__(self):
        return self.Iterator(self)

    def _compareto(self, obj):
        assert isinstance(self, obj.__class__)
        raise NotImplementedError

    
    
    
    
            
