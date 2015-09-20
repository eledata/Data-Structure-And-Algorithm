#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on 2015年9月19日

@author: mhuang1
'''
import sys

from py_algo.abstractmethod import abstractmethod
from py_algo.container import Container
from py_algo.visitor import Visitor

class SearchableContainer(Container):
    
    def __init__(self):
        super(SearchableContainer, self).__init__()
        
    @abstractmethod
    def __contains__(self, obj): pass
    
    @abstractmethod
    def insert(self, obj): pass
    
    @abstractmethod
    def withdraw(self, obj): pass
    
    @abstractmethod
    def find(self, obj): pass
    