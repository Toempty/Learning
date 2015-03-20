#-------------------------------------------------------------------------------
# Name:        性能度量
# Purpose:
#
# Author:      Administrator
#
# Created:     19/02/2014
# Copyright:   (c) Administrator 2014
# Licence:     <your licence>
#-------------------------------------------------------------------------------


def foo1():
   sum = 0
   for i in range(1000000):
          sum += i
   return sum

def foo2():
    i = 0
    sums = 0
    while (i < 1000000):
        sums += i
        i += 1
    return sums

from time import time

t = time()
sum1 = foo1()
t1 = time() - t
print(t1,'s')

t = time()
sum2 = foo2()
t2 = time() - t
print(t2,'s')
