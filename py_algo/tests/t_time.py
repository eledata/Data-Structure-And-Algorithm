#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on Sep 17, 2015

@author: mhuang1
'''
import unittest

from unittest import TestCase
from py_algo.timer import Timer

class T_Array(TestCase):
    
    def test(self):
        t = Timer()
        t.start()
        for i in range(40000000):
            pass
        t.stop()
        print "Elapsed time %g." % (t.getelapsedtime())
        return 0