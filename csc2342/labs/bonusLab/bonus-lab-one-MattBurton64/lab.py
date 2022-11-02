"""
Matt Burton
2/7/21
csc2342 01

"""


def powerSet(A):
	"""A Function which takes the input set and returns a power set(a set of all subsets)"""
	null = 0
	for n in A:
		A.add(null, {A})
		print(A)

A = {}
generation = 0

while generation < 5:
	powerSet(A)
	generation += 1


"""
Von Neumann Universe
need to import a python library to output to a file
use sets and recursion

sample first few generation of output

input set: 0

first gen:  {0}
second gen: {0,{0}}
third gen:  {0,{0},{{0}},{0,{0}}}
				...

print this output to a file

while printing the generations, track the elapsed time between generations and print the time to the console
"""
