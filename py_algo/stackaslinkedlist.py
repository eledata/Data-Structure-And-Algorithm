#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on Sep 16, 2015

@author: MHuang1
'''
import sys

from stack import Stack
from linkedlist import LinkedList
from visitor import Visitor
from iterator import Iterator
from exception import *

class StackAsLinkedList(Stack):
    def __init__(self):
        super(StackAsLinkedList, self).__init__()
        self._list = LinkedList()
        self._count = 0
        
    def purge(self):
        self._list.purge()
        self._count = 0
    
    def push(self, obj):
        self._list.prepend(obj)
        self._count += 1
        
    def pop(self):
        if(self._count == 0):
            raise ContainerEmpty
        result = self._list.headdata
        self._list.extract(result)
        self._count -= 1
        return result
    
    def gettop(self):
        if self._count == 0: raise ContainerEmpty
        return self._list.headdata
    
    def accept(self, visitor):
        assert isinstance(visitor, Visitor)
        pre = self._list.head
        while pre is not None:
            visitor.visit(pre.data)
            if visitor.isdone:
                return
            pre = pre.next
    
    class Iterator(Iterator):
        def __init__(self, stack):
            super(StackAsLinkedList.Iterator, self).__init__(stack)
            self._position = stack._list.head
            
        def next(self):
            if self._position is None:
                raise StopIteration
            element = self._position
            self._position = self._position.next
            return element.data
        
    def __iter__(self):
        return self.Iterator(self)

    def _compareto(self, obj):
        assert isinstance(self, obj.__class__)
        raise MethodNotImplemented
        
        
        
        
        
        
        