#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on Oct 15, 2015

@author: MHuang1
'''
import sys
from py_algo.abstractmethod import abstractmethod
from py_algo.object import Object
from py_algo.array import Array

class Sorter(Object):
    def __init__(self):
        super(Sorter, self).__init__()
        self._array = None
        self._n = 0
        
    def swap(self, i, j):
        tmp = self._array[i]
        self._array[i] = self._array[j]
        self._array[j] = tmp
    
    def _compareto(self, obj):
        assert isinstance(self, obj.__class__)
        raise NotImplementedError    
    
    def straightinsertionsorter_v1(self, array):
        assert isinstance(array, Array)
        self._array = array
        self._n = len(array)
        if self._n > 0:
            for i in xrange(1, self._n):
                j = i
                while j > 0 and self._array[j - 1] > self._array[j]:
                    self.swap(j, j - 1)
                    j -= 1
        self._array = None
        
    def straightinsertionsorter_v2(self, array):
        assert isinstance(array, Array)
        self._array = array
        self._n = len(array)
        if self._n > 0:
            for i in xrange(1, self._n - 1):
                if (self._array[i + 1] < self._array[i]):
                    self._array[0] = self._array[i + 1]
                    self._array[i + 1] = self._array[i]
                    j = i - 1
                    while j > 0 and self._array[0] < self._array[j]:
                        self._array[j + 1] = self._array[j]
                        j -= 1
                    self._array[j + 1] = self._array[0]
            self._array[0] = None
        self._array = None
        
    def binaryinsertsorter_v1(self, array):
        assert isinstance(array, Array)
        self._array = array
        self._n = len(array)
        if self._n > 0:
            for i in xrange(1, self._n):
                self._array[0] = self._array[i]
                low = 1
                high = i - 1
                while low <= high:
                    mid = (low + high)/2
                    if self._array[0] < self._array[mid]:
                        high = mid - 1
                    else:
                        low = mid + 1
                
                j = i - 1
                while j > high and j < i:
                    self._array[j + 1] = self._array[j]
                    j -= 1
                
                self._array[high + 1] = self._array[0]
                
            self._array[0] = None
        self._array = None    
 
    def binaryinsertsorter_v2(self, array):
        assert isinstance(array, Array)
        self._array = array
        self._n = len(array)
        if self._n > 0:     
            for i in xrange(1, self._n):    
                tmp = self._array[i]
                low = 0
                high = i
                while low < high:
                    mid = (low + high)/2
                    if tmp >= self._array[mid]:
                        low = mid + 1
                    else:
                        high = mid - 1
                j = i
                while j > high + 1:
                    self.swap(j - 1, j)
                    j -= 1        
        self._array = None    
        
        
        
        
        
        
        
        