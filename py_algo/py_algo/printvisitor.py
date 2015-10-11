#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on 2015年10月11日

@author: mhuang1
'''

from py_algo.visitor import Visitor

class PrintVisitor(Visitor):
    
    def __init__(self):
        super(PrintVisitor, self).__init__()
        self._comma = False
    
    def visit(self, obj):
        if self._comma:
            print ", "
        print obj
        self._comma = True
        
    def finish(self):
        print ""
        self._comma = False