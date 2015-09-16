#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on Sep 16, 2015

@author: MHuang1
'''
import sys
from Object import Object
from exception import MethodNotImplemented

class Visitor(Object):
    def __init__(self):
        super(Visitor, self).__init__()
        
    def visit(self, obj): pass
    
    def getisdone(self):
        return False
    
    isdone = property(fget = lambda self: self.getisdone())
    
    def _compareto(self, obj):
        assert isinstance(self, obj.__class__)
        raise MethodNotImplemented