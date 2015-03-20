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

if __name__ == "__main__":
    import profile
    profile.run("foo1()")
    profile.run("foo2()")
