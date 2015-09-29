#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on 2015年9月28日

@author: mhuang1
'''

import sys
import time
from py_algo.exception import *

class Timer(object):
    
    STOPPED = 1

    RUNNING = 2

    TOLERANCE = 100
    
    def __init__(self):
        self._starttime = time.time()
        self._stoptime = self._starttime
        self._startclock = time.clock()
        self._stopclock = self._startclock
        self._state = self.STOPPED
        
    def start(self):
        if self._state != self.STOPPED:
            raise StateError
        self._starttime = time.time()
        self._startclock = time.clock()
        self._state = self.RUNNING
    
    def stop(self):
        if self._state != self.RUNNING:
            raise StateError
        self._stoptime = time.time()
        self._stopclock = time.clock()
        self._state = self.STOPPED
        
    def getelapsedtime(self):
        if self._state == self.RUNNING:
            self._stopclock = time.clock()
            self._stoptime = time.time()
        elapsedtime = self._stoptime - self._starttime
        if elapsedtime < self.TOLERANCE:
            elapsedtime = self._stopclock - self._startclock
        return elapsedtime
    