#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on 2015年9月19日

@author: mhuang1
'''
import sys
from py_algo.queue import Queue
from py_algo.deque import Deque
from py_algo.queueasarray import QueueAsArray
from py_algo.exception import *


class DequeAsArray(QueueAsArray, Deque):
    
    def __init__(self, size = 0):
        super(DequeAsArray, self).__init__(size)
    
    def gettail(self):
        if self._count == 0:
            raise ContainerEmpty
        return self._array[self._tail]    
        
    def enqueuehead(self, obj):
        if self._count == len(self._array): raise ContainerFull
        
        if self._head == 0:
            self._head = len(self._array) - 1
        else:
            self._head = self._head - 1
        self._array[self._head] = obj
        self._count += 1
        
    def dequeuetail(self):
        if self._count == 0: raise ContainerEmpty
        result = self._array[self._tail]
        self._array[self._tail] = None
        
        if self._tail == 0:
            self._tail = len(self._array) - 1
        else:
            self._tail = self._tail - 1
        self._count -= 1    
        return result
    
                
        