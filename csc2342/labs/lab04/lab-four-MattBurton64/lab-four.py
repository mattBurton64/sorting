"""
Matt Burton
2/12/21
csc2342 01
"""
from itertools import permutations
import random

def start():
	
	print("Enter a domain and a codomain.")
	domain = set()
	codomain = set()

	domain.update(newSet(0))
	codomain.update(newSet(1))

	return (domain, codomain)

def newSet(count):

	print("Separate set values with spaces.\npress [Enter] when finished.")

	if count == 0:
		label = "Domain"
	else:
		label = "Codomain"

	nSet = inputSet(label)

	return nSet

def inputSet(label):

	nSet = set()

	print(" " + str(label) + ": ", end='')
	x = input()
	nSet.update(x)

	nSet.discard(' ')
	nSet.discard(',')
	nSet.discard('{')
	nSet.discard('}')

	return nSet

def function():
		
	print("Choose a function method.\n  1) One-to-one\n  2) Onto")
	method = input()

	return method

def output(method, domain, codomain):

	print("f:")
	if method == '1': #One-to-one
		if len(domain) is not len(codomain):
			print("  err: Invalid arguments for a one-to-one function.")
		else:
			for x in range(0, len(codomain)):
				print(domain.pop(), end='')
				print(" -> ", end='')
				print(codomain.pop())

	elif method == '2': #Onto
		for x in range(0, len(codomain)):
			d = random.sample(domain, 1)
			print(d[0] , end='')
			print(" -> ", end='')
			print(codomain.pop())
		
"""MAIN"""

enterNew = 'True'
while enterNew == 'True':
	domain, codomain = start()
	method = function()
	output(method, domain, codomain)
	
	enterNew = input("To repeat the program type 'True', otherwise enter 'False'.")
	str(enterNew)

