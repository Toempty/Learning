"""
numdictionaries = {'num1' : 100, 'num2' : 200, 'string1' : "one", 'string2' : "two"}

print numdictionaries['num2']
print numdictionaries['string2']

numdictionaries['num3'] = 300
numdictionaries['list1'] = [1, 2, 3]
numdictionaries['list2'] = ["a", "b", "c"]
"""

numdictionaries = {'num1': 100, 'num2': 200, 'num3': 300, 'list1': [1, 2, 3], 'list2': ['a', 'b', 'c'], 'string2': 'two', 'string1': 'one'}
print numdictionaries

print numdictionaries.keys()

print numdictionaries.values()

print numdictionaries.has_key('num1')

print numdictionaries.items()

numdictionaries2 = numdictionaries.copy()
print numdictionaries2

numdictionaries['list2'].remove('b')