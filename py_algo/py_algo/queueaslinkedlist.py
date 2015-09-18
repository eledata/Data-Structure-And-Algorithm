#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on Sep 18, 2015

@author: mhuang1
'''

import sys

from py_algo.queue import Queue
from py_algo.linkedlist import LinkedList
from py_algo.iterator import Iterator
from py_algo.visitor import Visitor
from py_algo.exception import *


class QueueAsLinkedList(Queue):
    
    def __init__(self):
        super(QueueAsLinkedList, self).__init__()
        self._list = LinkedList()
        
    def purge(self):
        self._list.purge()
        self._count = 0
        
    def gethead(self):
        if self._count == 0:
            raise ContainerEmpty
        return self._list.headdata
    
    head = property(fget = lambda self: self.gethead())

    def enqueue(self, data):
        self._list.append(data)
        self._count = self._count + 1
        
    def dequeue(self):
        
        if self._count == 0:
            raise ContainerEmpty
        result = self._list.headdata
        self._list.extract(result)
        self._count = self._count - 1
        return result
    
    def accept(self, visitor):
        assert isinstance(visitor, Visitor)
        pre = self._list.head
        while pre is not None:
            visitor.visit(pre.data)
            if visitor.isdone:
                return
            pre = pre.next
            
    class Iterator(Iterator):
        def __init__(self, queue):
            super(QueueAsLinkedList.Iterator, self).__init__(queue)
            self._position = None
            
        def next(self):
            element = self._container._position
            self._container._position = self._container._position.next
            if self._position is None:
                raise StopIteration
            return element.data

    def __iter__(self):
        return self.Iterator(self)

    def _compareto(self, obj):
        assert isinstance(self, obj.__class__)
        raise MethodNotImplemented





    
    