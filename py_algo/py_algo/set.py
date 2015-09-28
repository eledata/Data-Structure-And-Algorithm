#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on Sep 23, 2015

@author: mhuang1
'''

import sys
from py_algo.abstractmethod import abstractmethod
from py_algo.searchablecontainer import SearchableContainer

class Set(SearchableContainer):


    def __init__(self, universeSize):
        self._universeSize = universeSize

    def getUniverseSize(self):
        return self._universeSize

    universeSize = property(
        fget = lambda self: self.getUniverseSize())

    @abstractmethod
    def __or__(self, set): pass

    @abstractmethod
    def __and__(self, set): pass

    @abstractmethod
    def __sub__(self, set): pass

    @abstractmethod
    def __eq__(self, set): pass

    @abstractmethod
    def __le__(self, set): pass
    
    def find(self, i):
        if self.isMember(i):
            return i
        else:
            return None