#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on 2015年10月11日

@author: mhuang1
'''

import sys
from py_algo.prepostvisitor import PrePostVisitor


class InOrder(PrePostVisitor):
    
    def __init__(self, visitor):
        super(InOrder, self).__init__()
        self._visitor = visitor
        
    def invisit(self, obj):
        self._visitor.visit(obj)
        
    def getisdone(self):
        return self._visitor.isdone