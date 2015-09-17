#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on Sep 15, 2015

@author: mhuang1
'''

import sys
import inspect
import types


class abstractmethod(object):
    
    def __init__(self, func):
        self._func = func
    
    def __get__(self, obj, type):
        return self.method(obj, self._func, type)
    
    class method(object):
        
        def __init__(self, obj, func, cls):
            self._self = self
            self._func = func
            self._class = cls
            self.__name__ = func.__name__
            
        def __call__(self, *args, **kwargs):
            msg = "Abstract method %s of class %s called." %(self._func.__name__, self._class.__name__)
            raise TypeError, msg
        
        def __get__(self,*msg):
            return self
        
