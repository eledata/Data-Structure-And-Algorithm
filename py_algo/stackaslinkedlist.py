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

class StackAsLinkList(Stack):
    def __init__(self):
        super(StackAsLinkList, self).__init()
        self._list = LinkedList()
        
    def purge(self):
        self._list.purge()
        self._count = 0
    
    def push(self, obj):
        self._list.prepend(obj)
        self._count += 1
        
    def pop(self):
        if(self._count == 0):
            raise ContainerEmpty
        result = self._list.head
        self._list.extract(result)
        self._count -= 1
        return result
    
    def gettop(self):
        if self._count == 0: raise ContainerEmpty
        return self._list.head
    
    def accept(self, visitor):
        