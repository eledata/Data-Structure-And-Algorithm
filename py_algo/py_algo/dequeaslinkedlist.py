#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on 2015年9月19日

@author: mhuang1
'''
import sys
from py_algo.queue import Queue
from py_algo.deque import Deque
from py_algo.queueaslinkedlist import QueueAsLinkedList
from py_algo.exception import *

class DequeAsLinkedList(QueueAsLinkedList, Deque):
    
    def __init__(self):
        super(DequeAsLinkedList, self).__init__()
        
    def gettail(self):
        if self._count == 0: raise ContainerEmpty
        return self._list.taildata
    
    def enqueuehead(self, obj):
        self._list.prepend(obj)
        self._count += 1
        
    def dequeuetail(self):
        if self._count == 0: raise ContainerEmpty
        result = self._list.taildata
        self._list.extract(result)
        self._count -= 1
        return result
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        