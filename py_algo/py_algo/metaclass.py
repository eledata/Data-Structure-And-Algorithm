#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on Sep 15, 2015

@author: mhuang1
'''

import sys
import sets
import string

from py_algo.abstractmethod import abstractmethod

class Metaclass(type):
    
    def __init__(self, name, bases, dict):
        type.__init__(self, name, bases, dict)
        self.__new__ = staticmethod(self.new)

        abstractMethodSet = sets.Set()
        reverseMRO = list(self.__mro__)
        reverseMRO.reverse()
        for cls in reverseMRO:
            for (attrName, attr) in cls.__dict__.iteritems():
                if isinstance(attr, abstractmethod):
                    abstractMethodSet.add(attrName)
                else:
                    abstractMethodSet.discard(attrName)
        self.__abstractmethods__ = list(abstractMethodSet)
        self.__abstractmethods__.sort()

    @staticmethod
    def new(*args, **kwargs):
        cls = args[0]
        if len(cls.__abstractmethods__) > 0:
            msg = "Can't instantiate abstract class %s. " % (
                cls.__name__)
            msg += "Missing methods %s." % (
                str(cls.__abstractmethods__))
            raise TypeError, msg
        else:
            for base in cls.__mro__:
                if not isinstance(base, Metaclass) and \
                        base is not type:
                    return base.__new__(*args, **kwargs)
            return object.__new__(*args, **kwargs)