#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on Jun 5, 2015

@author: MHuang1
'''

import sys
import exceptions

# Setting four error state.

class InternalError(Exception):
    pass

class StateError(Exception):
    pass

class ContainerEmpty(StateError):
    pass

class ContainerFull(StateError):
    pass

