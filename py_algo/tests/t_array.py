#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on Sep 17, 2015

@author: mhuang1
'''
import unittest
from unittest import TestCase
from copy import copy
from py_algo.array import Array

class T_Array(TestCase):
    def test(self):
        a = Array(5)
        a[0] = 1
        a[1] = 2
        
        print a[0]
        print a.length
        print a.baseindex
        print a.data
        print a
        a.length = 10
        print a.length
        print a
        
        b = Array(2, 10)
        b[10] = 57
        
        c = Array(10)
        d = copy(c)
        print d

if __name__ == "__main__":
    unittest.main()