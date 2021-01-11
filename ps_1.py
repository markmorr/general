# -*- coding: utf-8 -*-
"""
Created on Fri Feb  7 19:29:41 2020

@author: Mark
"""

import pandas as pd
import numpy as np
height = [171, 168, 191, 182, 150, 178]
weight = [80, 78, 100, 80, 65, 83]
x = 10

def neighbors(x):
    for i in range(0,7):
        a = np.array(height)
        a[np.abs(a - 6).argmin()]
        diff = x - height[i]
        