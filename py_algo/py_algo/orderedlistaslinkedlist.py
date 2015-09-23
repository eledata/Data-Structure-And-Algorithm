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

class  OrderedListAsLinkedList(OrderedList):
    
    def __init__(self):
        super(OrderedListAsLinkedList, self).__init__()
        self._linkedlist = LinkedList()
        
    def insert(self, obj):
        self._linkedlist.append(obj)
        self._count += 1
        
    def purge(self):
        self._linkedlist.purge()
        self._count = 0
    
    def accept(self, visitor):
        assert isinstance(visitor, Visitor)
        pre = self._linkedlist.head
        while pre is not None:
            visitor.visit(pre)
            if visitor.isdone: return
            pre = pre.next
            
    
    def __contains__(self, obj):
        pre = self._linkedlist.head
        while pre is not None:
            if pre.data == obj: return True
            pre = pre.next
        return False
    
    def find(self, obj):
        pre = self._linkedlist.head
        while pre is not None:
            if pre.data == obj: return True
            pre = pre.next
        return False
    
    def withdraw(self, obj):
        target = self._linkedlist.head
        pre = None
        while target is not None and target.data is not obj:
            pre = target
            target = target.next
        
        self._count -= 1
        
    def findposition(self, obj):
        pre = self._linkedlist.head
        while pre.data is not obj:
            pre = pre.next
        return self.Cursor(self, pre)      
    
    def __getitem__(self, offset):
        if offset < 0 or offset >= self._count:
            raise IndexError
        i = 0
        pre = self._linkedlist.head
        while i < offset and pre is not None:
            pre = pre.next
            i += 1
        return pre.data
 
    def __str__(self):
        string = "ordered list as linked list {"
        ptr = self._linkedlist.head
        while ptr is not None:
            string = string + str(ptr._data)
            if ptr._next is not None:
                string = string + ", "
            ptr = ptr._next
        string = string + "}"
        return string    
           
    class Cursor(Cursor):
        def __init__(self, list, element):
            super(OrderedListAsLinkedList.Cursor, self).__init__(list)
            self._element = element
            
        def getdata(self):
            return self._element.data
        
        def insertafter(self, obj):
            self._element.insertafter(obj)    
            self._list._count += 1
            
        def insertbefore(self, obj):
            self._element.insertbefore(obj)
            self._list._count += 1                
    
        def withdraw(self):
            self._list._linkedlist.extract(self._element.data)
            self._list._count -= 1            
    
    class Iterator(Iterator):
        def __init__(self, list):
            super(OrderedListAsLinkedList.Iterator, self).__init__(list)
            self._element = None
            
        def next(self):
            
            if self._element is None:
                self._element = self._container._linkedlist.head
            else:
                self._element = self._element.next
            if self._element is None:
                raise StopIteration
            return self._element.data
        
    def __iter__(self):
        return self.Iterator(self)

    def _compareto(self, obj):
        assert isinstance(self, obj.__class__)
        raise MethodNotImplemented
    
    
    
    
    
    
    
    
    
            
                
    