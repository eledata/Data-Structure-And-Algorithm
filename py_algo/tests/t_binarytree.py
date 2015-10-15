#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on Sep 17, 2015

@author: mhuang1
'''
import unittest
from unittest import TestCase

from py_algo.binarytree import BinaryTree
from py_algo.printvisitor import PrintVisitor
from py_algo.preorder import PreOrder
from py_algo.inorder import InOrder
from py_algo.postorder import PostOrder

class T_Array(TestCase):
    def test(self):
        visitor = PrintVisitor()
        
        bt = BinaryTree(1)
        bt.attachright(BinaryTree(6))
        bt.attachleft(BinaryTree(7))
        print bt
#         print BinaryTree
#         print "Breadth-First traversal"
#         bt.breadthfirsttraversal(visitor)
#         visitor.finish()
#         print "Preorder traversal"
#         bt.depthfirsttraversal(PreOrder(visitor))
#         visitor.finish()
#         print "Inorder traversal"
#         bt.depthfirsttraversal(InOrder(visitor))
#         visitor.finish()
#         print "Postorder traversal"
#         bt.depthfirsttraversal(PostOrder(visitor))
#         visitor.finish()
#         print "Using iterator"
#         for i in BinaryTree:
#             print i
#         print "Using depth-first generator (preorder)"
        for i in bt.depthfirstgenerator(bt.INORDER):
            print i
#         print "Using breadth-first generator"
#         for i in bt.depthfirstgenerator():
#             print i