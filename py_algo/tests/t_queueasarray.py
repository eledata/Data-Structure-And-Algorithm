#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on Sep 17, 2015

@author: mhuang1
'''

import unittest
from unittest import TestCase

from py_algo.queueasarray import QueueAsArray
from py_algo.visitor import Visitor

class T_QueueAsArray(TestCase):
    
    def test(self):
        qaa = QueueAsArray(10)
        
        for i in xrange(10):
            qaa.enqueue(i)
        
        print "head is %s"%(qaa.head)


        print "============="     
        for data in qaa:
            print data
        
        #Use the visitor patten.
        class Vi_P(Visitor):
            def __init__(self):
                super(Vi_P,self).__init__()
            
            def visit(self, obj):
                print "visit %s " %(obj)
                
        vis = Vi_P()      
        #Use accept method to call the visitor method.     
        qaa.accept(vis);
        