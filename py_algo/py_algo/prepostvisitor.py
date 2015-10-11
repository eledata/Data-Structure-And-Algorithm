#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on 2015年10月11日

@author: mhuang1
'''

import sys
from py_algo.visitor import Visitor

class PrePostVisitor(Visitor):
    
    def __init__(self):
        super(PrePostVisitor, self).__init__()
        
    def previsit(self, obj): pass
    
    def invisit(self, obj): pass
    
    def postvisit(self, obj): pass
    
    #default
    visitor = invisit