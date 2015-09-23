#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on Sep 17, 2015

@author: mhuang1
'''

import unittest
from unittest import TestCase

from py_algo.orderedlistaslinkedlist import OrderedListAsLinkedList
from py_algo.visitor import Visitor

class T_QueueAsArray(TestCase):
    
    def test(self):
        list = OrderedListAsLinkedList()
        
        list.insert(1)
        list.insert(2)
        list.insert(3)
        list.insert(4)
        print list
        obj = list.find(2)
        print obj
        list.withdraw(obj)
        print list
        position = list.findposition(3)
        position.insertafter(5)
        print list
        position.insertbefore(6)
        print list
        position.withdraw()
        print list
        for i in list:
            print i
        
        liit = list.Iterator(list)
        print liit.next()
        
        #Use the visitor patten.
        class Vi_P(Visitor):
            def __init__(self):
                super(Vi_P,self).__init__()
            
            def visit(self, obj):
                print "visit %s " %(obj.data)
                
        vis = Vi_P()      
        #Use accept method to call the visitor method.     
        list.accept(vis);
        