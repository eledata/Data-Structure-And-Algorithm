#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on Sep 17, 2015

@author: mhuang1
'''

import sys
from exceptions import IndexError

class Array(object):
    
    def __init__(self, length = 0, baseidex = 0):
        assert length >= 0
        self._data = [None for i in xrange(length)]
        self._baseindex = baseidex
        
    def __copy__(self):
        result = Array(len(self._data))
        for i, data in enumerate(self._data):
            result[i] = data
        result._baseindex = self._baseindex
        return result
    
    def getoffset(self, index):
        offset = index - self._baseindex
        if offset < 0 or offset >= len(self._data):
            raise IndexError
        return offset
    
    def __getitem__(self, index):
        return self._data[self.getoffset(index)]
    
    def __setitem__(self, index, data):
        self._data[self.getoffset(index)] = data
        
    def getdata(self):
        return self._data
    
    data = property(fget = lambda self: self.getdata())
    
    def getbaseindex(self):
        return self._baseindex
    
    def setbaseindex(self, index):
        self._baseindex = index
        
    baseindex = property(fget = lambda self: self.getbaseindex(),
                         fset = lambda self, value: self.setbaseindex(value))
    
    def __len__(self):
        return len(self._data)
    
    def setlen(self, length):
        if self.__len__() != length:
            newarr = [None for i in xrange(length)]
            minilen = min(self.__len__(),length)
            for i in xrange(minilen):
                newarr[i] = self._data[i]
            self._data = newarr
    
    length = property(fget = lambda self: self.__len__(),
                      fset = lambda self, value: self.setlen(value))
    
    def __str__(self):
        return "Array {baseIndex = %d, data = %s}" % (
            self._baseindex, str(self._data))
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    