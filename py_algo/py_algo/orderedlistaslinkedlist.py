#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on 2015年9月19日

@author: mhuang1
'''

import sys
import  exceptions

from py_algo.orderedlist import OrderedList
from py_algo.linkedlist import LinkedList
from py_algo.cursor import Cursor
from py_algo.iterator import Iterator
from py_algo.visitor import Visitor
from py_algo.exception import *

class  OrderedListAsLinkedList(LinkedList):
    
    def __init__(self):
        super(OrderedListAsLinkedList, self).__init__()
        self._list = LinkedList()
        
    def insert(self, obj):
        self._list.append(obj)
        self._count += 1
        
    def purge(self):
        self._list.purge()
        self._count = 0
    
    def accept(self, visitor):
        assert isinstance(visitor, Visitor)
        pre = self._list.head
        while pre is not None:
            visitor.visit(pre)
            if visitor.isdone: return
            pre = pre.next
            
    
    def __contains__(self, obj):
        pre = self._list.head
        while pre is not None:
            if pre.data == obj: return True
            pre = pre.next
        return False
    
    def find(self, obj):
        pre = self._list.head
        while pre is not None:
            if pre.data == obj: return True
            pre = pre.next
        return False
    
    def withdraw(self, obj):
        target = self._list.head
        pre = None
        while target is not None and target.data is not obj:
            pre = target
            target = target.next
        
        self._count -= 1
        
    def findposition(self, obj):
        i = 0
        while i < self._count and self._array[i] != obj:
            i += 1
        return self.Cursor(self, i)      
    
    def __getitem__(self, offset):
        if offset < 0 or offset >= self._count:
            raise IndexError
        return self._array[offset]
        
    class Cursor(Cursor):
        def __init__(self, list, offset):
            super(OrderedListAsArray.Cursor, self).__init__(list)
            self._offset = offset
            
        def getdata(self):
            if self._offset <0 or self._offset >= self._list._count:
                raise IndexError
            return self._list._array[self._offset]
        
        def insertafter(self, obj):
            if self._offset <0 or self._offset >= self._list._count:
                raise IndexError
            
            if self._list._count == len(self._list._array):
                raise ContainerFull
            insertpos = self._offset + 1
            i = self._list._count
            while i > insertpos:
                self._list._array[i] = self._list._array[i - 1]
                i -=1
            self._list._array[insertpos] = obj
            self._list._count += 1
            
        def insertbefore(self, obj):
            if self._offset <0 or self._offset >= self._list._count:
                raise IndexError
            
            if self._list._count == len(self._list._array):
                raise ContainerFull
            insertpos = self._offset
            i = self._list._count
            while i > insertpos:
                self._list._array[i] = self._list._array[i - 1]
                i -=1
            self._list._array[insertpos] = obj
            self._list._count += 1                
            self._offset += 1
    
        def withdraw(self):
            if self._offset <0 or self._offset >= self._list._count:
                raise IndexError
            
            if self._list._count < 0:
                raise ContainerEmpty
            
            i = self._offset
            while i < self._list._count - 1:
                self._list._array[i] = self._list._array[i + 1]
                i +=1
                
            self._list._array[i] = None
            self._list._count -= 1            
    
    class Iterator(Iterator):
        def __init__(self, list):
            super(OrderedListAsArray.Iterator, self).__init__(list)
            self._position = -1
            
        def next(self):
            self._position += 1
            if self._position == self._container._count:
                self._position = -1
                raise StopIteration
            return self._container._array[self._position]
        
    def __iter__(self):
        return self.Iterator(self)

    def _compareto(self, obj):
        assert isinstance(self, obj.__class__)
        raise MethodNotImplemented
    
    
    
    
    
    
    
    
    
            
                
    