#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on Sep 15, 2015

@author: mhuang1
'''
import unittest
from unittest import TestCase

from py_algo.linkedlist import LinkedList
from copy import copy

class T_LinkList(TestCase):
    
    def test(self):
        l1 = LinkedList()
        l1.append(57)
        l1.append("hello")
        l1.append(None)
        print l1
        print "isEmpty returns %s" % (l1.isempty)
        
        ptr = l1.head
        
        while ptr is not l1.tail:
            print ptr.data
            ptr = ptr.next
            
        l1.extract(57)
        ptr = l1.head
        while ptr is not l1.tail:
            print ptr.data
            ptr = ptr.next
            

        l2 = copy(l1)
        print l2
        print l2.length
        print l2.headdata
        print l2.taildata

if __name__ == "__main__":
    unittest.main()