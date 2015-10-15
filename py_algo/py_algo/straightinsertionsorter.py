#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on Oct 15, 2015

@author: MHuang1
'''
import sys

from py_algo.sorter import Sorter
from py_algo.array import Array

class StraightInsertionSorter(Sorter):
    def __init__(self):
        super(StraightInsertionSorter, self).__init__()
        
    def _sort(self):
        for i in xrange(1, self._n):
            j = i
            while j > 0 and self._array[j - 1] > self._array[j]:
                self.swap(j, j - 1)
                j -= 1
            
    def _sort_oth(self):
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
                
    def sort(self, array):
        assert isinstance(array, Array)
        self._array = array
        self._n = len(array)
        if self._n > 0:
            self._sort_oth()
        self._array = None
                    