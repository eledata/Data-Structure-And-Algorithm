#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on 2015年10月11日

@author: mhuang1
'''

import sys
from py_algo.tree import Tree
from py_algo.queueaslinkedlist import QueueAsLinkedList
from py_algo.stackaslinkedlist import StackAsLinkedList
from py_algo.prepostvisitor import PrePostVisitor
from py_algo.preorder import PreOrder
from py_algo.inorder import InOrder
from py_algo.postorder import PostOrder
from py_algo.iterator import Iterator
from py_algo.visitor import Visitor
from py_algo.printvisitor import PrintVisitor

from py_algo.exception import *

class BinaryTree(Tree):
    
    def __init__(self, *args):
        super(BinaryTree, self).__init__()
        
        if len(args) == 0:
            self._key = 0
            self._left = None
            self._right = None
        elif len(args) == 1:
            self._key = args[0]
            self._left = BinaryTree()
            self._right = BinaryTree()
        elif len(args) == 3:
            self._key = args[0]
            self._left = args[1]
            self._right = args[2]
        else:
            raise  ValueError
    
    def purge(self):
        self._key = 0
        self._left = None
        self._right = None
        
    def getleft(self):
        if self.isempty:
            return StateError          
        return self._left
    left = property(fget = lambda self: self.getleft())
    
    def getright(self):
        if self.isempty:
            return StateError
        return self._right
    right = property(fget = lambda self: self.getright())
    
    def getisleaf(self):
        return not self.isempty and self._left.isempty and self._right.isempty
    
    def getdegree(self):
        if self.isempty:
            return 0
        else:
            return 2
    
    def getheight(self):pass
    
    def getcount(self):
        if self.isempty:
            return 0
        result = 1
        for i in xrange(self.degree):
            result = result + self.getsubtree(i).count
        return result          
   
    def getisempty(self):
        return self._key is None
    
    def getkey(self):
        if self.isempty:
            raise ValueError
        return self._key
    
    def getsubtree(self, i):
        if i == 0:
            return self._left
        elif i == 1:
            return self._right
        else:
            raise IndexError
        
    def attachkey(self, obj):
        if not self.isempty:
            raise StateError
        self._key = obj
        self._left = BinaryTree()
        self._right = BinaryTree()
    
    def detachkey(self):
        if not self.isempty:
            raise StateError
        result = self._key
        self._key = None
        self._left = None
        self._right = None
        return result
    
    def attachleft(self, obj):
        if self.isempty or not self._left.isempty:
            raise StateError
        self._left = obj
        
    def detachleft(self):
        if self.isempty:
            raise StateError
        result = self._left
        self._left = BinaryTree()
        return result
    
    def attachright(self, obj):
        if self.isempty or not self._right.isempty:
            raise StateError
        self._right = obj
        
    def detachright(self):
        if self.isempty:
            raise StateError
        result = self._right
        self._right = BinaryTree()
        return result   
    
    def depthfirsttraversal(self, visitor):
        assert isinstance(visitor, PrePostVisitor)
        
        if not self.isempty:
            visitor.previsit(self.key)
            self.left.depthfirsttraversal(visitor)
            visitor.invisit(self.key)
            self.left.depthfirsttraversal(visitor)
            visitor.postvisit(self.key)

    
    def depthfirstgenerator(self, mode):
        if not self.isempty:
            if mode == self.PREORDER:
                yield self.key
            for obj in self.left.depthfirstgenerator(mode):
                yield obj
            if mode == self.INORDER:
                yield self.key
            for obj in self.right.depthfirstgenerator(mode):
                yield obj        
            if mode == self.POSTORDER:
                yield self.key
    
    def _compareto(self, bt):
        assert isinstance(self, bt.__class__)
        
        if self.isempty:
            if bt.isempty:
                return 0
            else:
                return -1
        elif bt.isempty:
            return 1
        else:
            result = cmp(self._key, bt._key)
            if result == 0:
                result = cmp(self._left, bt._left)
            if result == 0:
                result = cmp(self._right, bt._right)
            return result
    
    def breadthfirsttraversal(self, visitor): pass

    def breadthfirstgenerator(self): pass

    def accept(self, visitor): pass