#!/usr/bin/env python3

##############################
# THIS IS AN A LEVEL PROJECT #
##############################

__author__ = "Matt Burton"
__copyright__ = "Copyright 2020"
__credits__ = [""]
__license__ = "GPLv3"
__version__ = "1.0.0"
__maintainer__ = ""
__email__ = "mburton2@highpoint.edu"
__status__ = "Complete"

# define your functions here
import re

def instructions():
	print("Predicate Statememt Evaluation \n")
	print("Use 'x', 'y', and 'z' in that order to express from 1 to 3 variables.")
	print("Use '>', '<', or '==' to compare the provided predicates.")
	print("Use 'u' or 'e' for universal or existential respectively.")
	print("Use spaces in between variables and comparison operators.")
	print("Examples: x > 0 \t x + y = 1 \t x - y = z\n")

def parse(function, domain, quantifier):
	
	splitFunction = function.split()
	length = len(splitFunction)

	i = 0
	while i < length:
		if splitFunction[i] == 'z':
			numVars = 3
		elif splitFunction[i] == 'y':
			numVars = 2
		elif splitFunction[i] == 'x':
			numVars = 1
		i += 1

	if numVars == 1:
		truth = unary(function, domain, quantifier)
	if numVars == 2:
		truth = binary(function, domain, quantifier)
	if numVars == 3:
		truth = ternary(function, domain, quantifier)

	output(function, truth, domain)

def unary(function, domain, quantifier):
	
	truth = 'default'

	domain  = domain.split("...")
	low = int(domain[0])
	high = int(domain[1])
	
	x = low
	while x < high:
		if quantifier == 'u' and truth != 'F':
			if eval(function):
				truth = 'T'
			else:
				truth = 'F'
		elif quantifier == 'e':
			if eval(function):
				truth = 'T'
		x += 1
	return truth

def binary(function, domain, quantifier):
	
	truth = 'default'

	domain  = domain.split("...")
	low = int(domain[0])
	high = int(domain[1])
	
	x = low
	y = low
	while x < high:
		while y < high:
			if quantifier == 'u' and truth != 'F':
				if eval(function):
					truth = 'T'
				else:
					truth = 'F'
			elif quantifier == 'e':
				if eval(function):
					truth = 'T'
			y += 1
		x += 1
	return truth

def ternary(function, domain, quantifier):
	
	truth = 'default'

	domain  = domain.split("...")
	low = int(domain[0])
	high = int(domain[1])
	
	x = low
	y = low
	z = low

	while x < high:
		while y < high:
			while z < high:
				if quantifier == 'u' and truth != 'F':
					if eval(function):
						truth = 'T'
					else:
						truth = 'F'
				elif quantifier == 'e':
					if eval(function):
						truth = 'T'
				z += 1
			y += 1
		x += 1
	return truth

def output(function, truth, domain):
	if (truth == 'default'):
		truth = 'F'

	domain  = domain.split("...")

	print("The function " + function + " in the domain of (" + domain[0] + "-" + domain[1] + ") evaluates to " + truth)

def main():
	instructions()
	
	function = input("Enter a function in standard arithmetic construct form: ")
	domain = input("Enter the range for your variables as 'low...high': ")
	quantifier = input("Enter a quantifier 'u' for all values and 'e' for at least one: ")

	parse(function, domain, quantifier)

if __name__ == "__main__":
    main()
