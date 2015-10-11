#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on 2015年10月11日

@author: mhuang1
'''

import sys
from py_algo.abstractmethod import abstractmethod
from py_algo.container import Container
from py_algo.queueaslinkedlist import QueueAsLinkedList
from py_algo.stackaslinkedlist import StackAsLinkedList
from py_algo.prepostvisitor import PrePostVisitor
from py_algo.preorder import PreOrder
from py_algo.inorder import InOrder
from py_algo.postorder import PostOrder
from py_algo.iterator import Iterator
from py_algo.visitor import Visitor
from py_algo.printvisitor import PrintVisitor

class Tree(Container):
    
    @abstractmethod
    def getkey(self): pass
    key = property(fget = lambda self: self.getkey())
    
    @abstractmethod
    def getsubtree(self, i): pass
    
    @abstractmethod
    def getisleaf(self): pass
    isleaf = property(fget = lambda self: self.getisleaf())
    
    @abstractmethod
    def getdegree(self): pass
    degree = property(fget = lambda self: self.getdegree())

    def __init__(self):
        super(Tree, self).__init__()
        
    def depthfirsttraversal(self, visitor):
        assert isinstance(visitor, PrePostVisitor)
        
        if not self.isempty and not visitor.isdone:
            visitor.previsit(self.key)
            for i in xrange(self.degree):
                self.getsubtree(i).depthfirsttraversal(visitor)
            visitor.postvisit(self.key)
    
    # mode
    PREORDER = -1
    INORDER = 0
    POSTORDER = +1
    
    def depthfirstgenerator(self, mode):
        if not self.isempty:
            if mode == self.PREORDER:
                yield self.key
            for i in xrange(self.degree):
                for obj in self.getsubtree(i).depthfirstgenerator(mode):
                    yield obj
            if mode == self.POSTORDER:
                yield self.key
            
    
    def breadthfirsttraversal(self, visitor):
        assert isinstance(visitor, Visitor)
        queue = QueueAsLinkedList()
        if not self.isempty:
            queue.enqueue(self)
            
        while not self.isempty and not visitor.isdone:
            head = queue.dequeue()
            visitor.visit(head.key)
            for i in xrange(head.degree):
                child = head.getsubtree(i)
                if not child.isempty:
                    queue.enqueue(child)
    
    
    def breadthfirstgenerator(self):
        queue = QueueAsLinkedList()
        if not self.isempty:
            queue.enqueue(self)
            
        while not self.isempty:
            head = queue.dequeue()
            yield head.key
            for i in xrange(head.degree):
                child = head.getsubtree(i)
                if not child.isempty:
                    queue.enqueue(child)
    
    #default preorder
    def accept(self, visitor):
        assert isinstance(visitor, Visitor)
        self.depthfirsttraversal(PreOrder(visitor))
    
    def getheight(self):
        if self.isempty:
            return - 1
        height = -1
        for i in xrange(self.degree):
            height = max(height, self.getsubtree(i).height)
        return height+ 1
    
    height = property(fget = lambda self: self.getheight()) 
        
    def getcount(self):
        if self.isempty:
            return 0
        result = 1
        for i in xrange(self.degree):
            result = result + self.getsubtree(i).count
        return result   
            
    count = property(fget = lambda self: self.getcount())    
        
    class Iterator(Iterator):
        def __init__(self, tree):
            super(Tree.Iterator, self).__init__()
            self._stack = StackAsLinkedList()
            if not tree.isempty:
                self._stack.push(tree)
        
        def next(self):
            if self._stack.isempty:
                raise StopIteration
            top = self._stack.pop()
            i = top.degree - 1
            while i >= 0:
                subtree = top.getsubtree(i)
                if not subtree.isempty:
                    self._stack.push(subtree)
                i -= 1
            return top.key
        
    def __iter__(self):
        return Tree.Iterator(self)
        
        