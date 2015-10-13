#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on 2015年10月11日

@author: mhuang1
'''

import sys
from py_algo.abstractmethod import abstractmethod
from py_algo.container import Container


class Tree(Container):
    
    # mode
    PREORDER = -1
    INORDER = 0
    POSTORDER = +1
    
    def __init__(self):
        super(Tree, self).__init__()
    
    @abstractmethod
    def getkey(self): pass
    key = property(fget = lambda self: self.getkey())
    
    @abstractmethod
    def getsubtree(self, i): pass
    
    @abstractmethod
    def getisleaf(self): pass
    isleaf = property(fget = lambda self: self.getisleaf())
    
    @abstractmethod
    def getdegree(self): pass
    degree = property(fget = lambda self: self.getdegree())
    
    @abstractmethod
    def getheight(self):pass
    height = property(fget = lambda self: self.getheight())
    
    @abstractmethod  
    def depthfirsttraversal(self, visitor): pass
    @abstractmethod
    def depthfirstgenerator(self, mode): pass
    @abstractmethod
    def breadthfirsttraversal(self, visitor): pass
    @abstractmethod
    def breadthfirstgenerator(self): pass     
    def __iter__(self): pass