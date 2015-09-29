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

class SetAsBit(Set):
    
    BITS = 32
    
    def __init__(self, n):
        super(SetAsBit, self).__init__(n)
        self._array = Array((n + self.BITS - 1) / self.BITS)
        for i in xrange(len(self._array)):
            self._array[i] = 0
    
    def insert(self, item):
        self._array[item/self.BITS] |= (1 << item % self.BITS)
    
    def __contains__(self, item):
        return (self._array[item/self.BITS] & (1 << item % self.BITS)) != 0
    
    def withdraw(self, item):
        self._array[item/self.BITS] &= ~(1 << item % self.BITS)
        
    def getisempty(self):
        for item in xrange(0, self._universeSize):
            if item is self:
                return False
        return True
    
    def getisfull(self):
        for item in xrange(0, self._universeSize):
            if item not in self:
                return True
        return False        
    
    def purge(self):
        for item in xrange(0, self._universeSize):
            self._array[item] = 0

    def accept(self, visitor):
        assert isinstance(visitor, Visitor)
        for item in xrange(0, self._universeSize):
            if item in self:
                visitor.visit(item)

    def getcount(self):
        count = 0
        for item in xrange(0, self._universeSize):
            if item in self:
                count += 1
        return count
    
    def __or__(self, set):
        assert isinstance(set, SetAsBit)
        print "__or__"
        result = SetAsBit(self._universeSize)
        for i in  xrange(0, self._universeSize):
            result._array[i] = self._array[i] | set._array[i]
        return result
        
    def __and__(self, set):
        assert isinstance(set, SetAsBit)
        print "__and__"
        result = SetAsBit(self._universeSize)
        for i in  xrange(0, self._universeSize):
            result._array[i] = self._array[i] & set._array[i]
        return result       

    def __sub__(self, set):
        assert isinstance(set, SetAsBit)
        print "__sub__"
        result = SetAsBit(self._universeSize)
        for i in  xrange(0, self._universeSize):
            result._array[i] = self._array[i] & ~ set._array[i]
        return result


    def __eq__(self, set):
        assert isinstance(set, SetAsBit)
        print "__eq__"
        result = SetAsBit(self._universeSize)
        for i in  xrange(0, self._universeSize):
            if self._array[i] != set._array[i]:
                return False
        return True


    def __le__(self, set): 
        assert isinstance(set, SetAsBit)
        print "__le__"
        result = SetAsBit(self._universeSize)
        for i in  xrange(0, self._universeSize):
            if self._array[i] &~ set._array[i] != 0:
                return False
        return True
    
    class Iterator(Iterator):
        def __init__(self, set):
            super(SetAsBit.Iterator, self).__init__(set)
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

    
    
    
    
            
