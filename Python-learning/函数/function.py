def add(x, y):
	out = x + y
	return out

c = add(134, 221)
print c

def sayhello():
	print "Hello Python!"

sayhello()

def addnums(nums):
	out = 0
	for x in nums:
		out = add(out, x)
	return out

nums = [1, 2, 3, 4, 5, 6, 7]

print addnums(nums)