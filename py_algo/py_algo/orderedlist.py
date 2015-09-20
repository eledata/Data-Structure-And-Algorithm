#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on 2015年9月19日

@author: mhuang1
'''

import  sys

from py_algo.abstractmethod import abstractmethod
from py_algo.searchablecontainer import SearchableContainer

class OrderedList(SearchableContainer):
    
    def __init__(self):
        super(SearchableContainer, self).__init__()
        
    @abstractmethod
    def __getitem__(self, i ): pass
    
    @abstractmethod
    def findposition(self, obj): pass
    