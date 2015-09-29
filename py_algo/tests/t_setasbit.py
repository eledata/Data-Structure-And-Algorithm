#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on Sep 17, 2015

@author: mhuang1
'''

import unittest
from unittest import TestCase

from py_algo.setasbit import SetAsBit
from py_algo.visitor import Visitor

class T_DequeAsArray(TestCase):
    
    def test(self):
        saa = SetAsBit(20)
        sab = SetAsBit(30)
        
        for i in xrange(10):
            saa.insert(i)

        for i in xrange(20):
            sab.insert(i)
        
        print saa.getcount()
        print sab.getcount()
                   
        saa.withdraw(5)

        print "============="     
        for data in saa:
            print data
        
        #Use the visitor patten.
        class Vi_P(Visitor):
            def __init__(self):
                super(Vi_P,self).__init__()
            
            def visit(self, obj):
                print "visit %s " %(obj)
                
        vis = Vi_P()      
        #Use accept method to call the visitor method.     
        saa.accept(vis);
        
        print saa>=sab