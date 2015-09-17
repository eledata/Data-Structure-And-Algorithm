#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on Sep 17, 2015

@author: mhuang1
'''
import unittest
from unittest import TestCase

from array import Array

class T_Array(TestCase):
    def test(self):
        a = Array(5)
        a[0] = 1
        a[1] = 2
        
        print a[0]
        
