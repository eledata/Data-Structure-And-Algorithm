#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on Sep 17, 2015

@author: mhuang1
'''
import unittest
import random
import sys
from unittest import TestCase

from py_algo.array import Array
from py_algo.timer import Timer
from py_algo.sorter import Sorter


class T_Sort(TestCase):
    
    def test_sis(self):
        sort = Sorter()
        data = Array(8)
        n = len(data)
        data[1] = 1
        data[2] = 20
        data[3] = 11
        data[4] = 32
        data[5] = 3
        data[6] = 8
        data[7] = 49
#         for i in xrange(1, n):
#             datum = int(sys.maxint * random.random())
#             data[i] = datum
        
        print data
        timer = Timer()
        timer.start()
        sort.binaryinsertsorter_v2(data)
        timer.stop()
        print "Time used:", timer.getelapsedtime()
        print data
        for i in xrange(1, n):
            if data[i] < data[i - 1]:
                print "FAILED"
                break