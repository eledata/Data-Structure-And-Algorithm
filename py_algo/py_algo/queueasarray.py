#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on Sep 18, 2015

@author: mhuang1
'''
#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on Sep 18, 2015

@author: mhuang1
'''

import sys

from py_algo.queue import Queue
from py_algo.array import Array
from py_algo.iterator import Iterator
from py_algo.visitor import Visitor
from py_algo.exception import *


class QueueAsArray(Queue):
    
    def __init__(self, size = 0):
        super(QueueAsArray, self).__init__()
        self._array = Array(size)
        self._head = self._tail = 0
        
    def purge(self):
        for i in xrange(len(self._array)):
            self._array[i] = None
        self._count = 0
        
    def gethead(self):
        if self._count == 0:
            raise ContainerEmpty
        return self._array[self._head]
    
    head = property(fget = lambda self: self.gethead())

    def enqueue(self, data):
        if self._count > len(self._array):
            raise ContainerFull
        self._tail = self._tail + 1
        if self._tail == len(self._array):
            self._tail = 0
        self._array[self._tail] = data
        self._count = self._count + 1
        
    def dequeue(self):
        
        if self._count == 0:
            raise ContainerEmpty
        result = self._array[self._head]
        if self._tail == len(self._array):
            self._tail = 0
        self._count = self._count - 1
        return result
    
    def accept(self, visitor):
        assert isinstance(visitor, Visitor)
        pos = self._head
        for i in xrange(self._count):
            visitor.visit(self._array[pos])
            if visitor.isdone:
                return
            pos = pos + 1
            if ++pos == len(self._array):
                pos = 0
            
    class Iterator(Iterator):
        def __init__(self, queue):
            super(QueueAsArray.Iterator, self).__init__(queue)
            self._position = self._container._head
            
        def next(self):
            self._position = self._position + 1
            if self._position == self._container._count:
                self._position = -1
                raise StopIteration
            return self._container._array[
                (self._container._head + self._position)
                % len(self._container._array)]
            
            

    def __iter__(self):
        return self.Iterator(self)

    def _compareto(self, obj):
        assert isinstance(self, obj.__class__)
        raise MethodNotImplemented





    
    