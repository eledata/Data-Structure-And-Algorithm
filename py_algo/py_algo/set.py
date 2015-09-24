#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on Sep 23, 2015

@author: mhuang1
'''

import sys
from py_algo.abstractmethod import abstractmethod
from py_algo.searchableContainer import SearchableContainer

class Set(SearchableContainer):


    def __init__(self, universeSize):
        """
        (Set, int) -> None
        Constructs a set with the given universe size.
        """
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