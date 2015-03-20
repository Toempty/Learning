"""
def biggest_number(*args):
    print max(args)
    return max(args)
    
def smallest_number(*args):
    print min(args)
    return min(args)

def distance_from_zero(arg):
    print abs(arg)
    return abs(arg)


biggest_number(-10, -5, 5, 10)
smallest_number(-10, -5, 5, 10)
distance_from_zero(-10)
"""

nums = range(-10, 10);

print nums

maxnums = max(nums)
print maxnums

minnums = min(nums)
print minnums

absnums = abs(-10)
print absnums

flag = cmp(-10, 10)
print flag

flag = cmp(10, -10)
print flag

lennums = len(nums)
print lennums

lenstrings = len("lenstring")
print lenstrings

typenums = type(nums)
print typenums

