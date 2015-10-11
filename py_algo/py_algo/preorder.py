#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on 2015年10月11日

@author: mhuang1
'''

import sys
from py_algo.prepostvisitor import PrePostVisitor


class PreOrder(PrePostVisitor):
    
    def __init__(self, visitor):
        super(PreOrder, self).__init__()
        self._visitor = visitor
        
    def previsit(self, obj):
        self._visitor.visit(obj)
        
    def getisdone(self):
        return self._visitor.isdone