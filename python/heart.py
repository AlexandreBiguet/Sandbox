#!/usr/bin/env python3

from math import sqrt, fabs

scale = 2.0

def Fup(x) :
    return sqrt(1.0 - (fabs(x)-1)**2)

def Flow(x):
    return -3* sqrt ( 1.0 - sqrt(fabs(x)/(2.)) )

xmin = -2.
xmax = 2.
n = 30
delta = (xmax - xmin) / n

print("# x   up    low")

for i in range(n) :
    x = xmin + i * delta
    print(x, " ", Fup(x), " ", Flow(x))


### To print the heart print the second and third column w.r.t the first col.
