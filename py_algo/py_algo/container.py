#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on Sep 16, 2015

@author: MHuang1
'''

import sys
from py_algo.abstractmethod import abstractmethod
from py_algo.object import Object
from py_algo.visitor import Visitor
from py_algo.exception import MethodNotImplemented

class Container(Object):
    def __init__(self):
        super(Container, self).__init__()
        self._count = 0
        
    @abstractmethod
    def purge(self): pass
    
    @abstractmethod
    def __iter__(self): pass
    
    def getcount(self):
        return self._count
    
    count = property(fget = lambda self: self.getcount())
    
    def getisempty(self):
        return self.count == 0
    
    isempty = property(fget = lambda self: self.getisempty())
    
    def getisfull(self):
        return False
    isfull = property(fget = lambda self: self.getisfull())
    
    def accept(self, visitor):
        assert isinstance(visitor, Visitor)
        for obj in self:
            visitor.visit(obj)
    
    def elements(self):
        for obj in self:
            yield obj
    
    class StrVisitor(Visitor):
        def __init__(self):
            self._string = ""
            self._comma = False
        
        def visit(self, obj):
            if self._comma:
                self._string = self._string + ","
            self._string = self._string + str(obj)
            self._comma = True
            
        def __str__(self):
            return self._string
        
    def __str__(self):
        visitor = Container.StrVisitor()
        self.accept(visitor)
        return "%s {%s}"%(self.__class__.__name__, str(visitor))
    
    def __hash__(self):
        result = hash(self.__class__)
        for obj in self:
            result = (result + hash(obj)) & sys.maxint
        return result
        