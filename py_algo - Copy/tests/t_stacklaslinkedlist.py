#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on Sep 17, 2015

@author: mhuang1
'''

import unittest
from unittest import TestCase

from py_algo.stackaslinkedlist import StackAsLinkedList
from py_algo.visitor import Visitor

class T_StackAsLinkedList(TestCase):
    
    def test(self):
        sall = StackAsLinkedList()
        
        for i in xrange(10):
            if not sall.isfull:
                sall.push(i)
        
        print "Top is %s"%(sall.top)

        while not sall.isempty:
            print sall.pop()

        for i in xrange(10):
            if not sall.isfull:
                sall.push(i)
        print "============="     
        for data in sall:
            print data
            
        #Use the visitor patten.
        class Vi_P(Visitor):
            def __init__(self):
                super(Vi_P,self).__init__()
            
            def visit(self, obj):
                print "visit %s " %(obj)
                
        vis = Vi_P()      
        #Use accept method to call the visitor method.     
        sall.accept(vis);
        