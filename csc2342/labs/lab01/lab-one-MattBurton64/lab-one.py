#!/usr/bin/env python3



############################
# THIS IS A B LEVEL PROJECT#
############################




__author__ = "Matthew Burton"
__copyright__ = "Copyright 2021"
__credits__ = ["Jake Lagana and Reily Kobbe"]
__license__ = "GPLv3"
__version__ = "1.0.0"
__maintainer__ = "none"
__email__ = "mburton2@highpoint.edu"
__status__ = "Complete"

# define your functions here
import re
def instructions():
	print("TRUTH TABLE GENERATOR")
	print("Enter a propositional statement below.")
	print("Use operators to evaluate your propositions")
	print("  AND     /\ \n  OR      \/ \n  IMPLIES >")
	print("Express the proposition as 'p /\ q' for example, with spaces for separation.")
	print("Use the ~ to expres NOT. Example: ~p > ~q")
def evaluate(prop):
	
	splitProp = prop.split()
	length = len(splitProp)
	numVars = length / 2 + 1
	rows = pow(2, numVars)
	p = 0

	tableLabel(prop, numVars)
	if numVars == 1:
		loopOne(splitProp, numVars)
	if numVars == 2:
		loopTwo(splitProp, numVars)
	if numVars == 3:
		loopThree(splitProp, numVars)

def loopOne(splitProp, numVars):
	p = 0
	x = 0
	while x < 2:
		tableOne(p)
		p += 1
		x += 1

def loopTwo(splitProp, numVars):
	p = 0
	while p < 2:
		q = 0
		while q < 2:	
			#AND
			if splitProp[1] == '/\\':
				pp, qq, result = andOp(p, q, splitProp)
			#OR
			elif splitProp[1] == '\/':
				pp, qq, result = orOp(p, q, splitProp)
			#IMPLIES
			elif splitProp[1] == '>':
				pp, qq, result = impliesOp(p, q, splitProp)

			tableTwo(pp, qq, result)
			q += 1
		p += 1
			
def loopThree(splitProp, numVars):
	p = 0
	while p < 2:
		q = 0
		while q < 2:
			r = 0
			while r < 2:
				#AND
				if splitProp[1] == '/\\':
					pp, qq, result = andOp(p, q, splitProp)
				#OR
				elif splitProp[1] == '\/':
					pp, qq, result = orOp(p, q, splitProp)
				#IMPLIES
				elif splitProp[1] == '>':
					pp, qq, result = impliesOp(p, q, splitProp)

				tableThree(pp, qq, r, result)
				r += 1
			q += 1
		p += 1
	
def andOp(p, q, splitProp):
	
	if re.match('~', splitProp[0]):
		if (p % 2) == 0:
			p = 1
		else:
			p  = 0
	
	if re.match('~', splitProp[2]):
		if (q % 2) == 0:
			q = 1
		else:
			q = 0

	if (p % 2) == (q % 2):
		return p, q, 'T'
	else:
		return p, q, 'F'

def orOp(p, q, splitProp):
		
	if re.match('~', splitProp[0]):
		if p == 0:
			p = 1
		else:
			p = 0
	
	if re.match('~', splitProp[2]):
		if q == 0:
			q = 1
		else:
			q = 0

	if p == 0 or q == 0:
		return p, q, 'T'
	else:
		return p, q, 'F'
	
def impliesOp(p, q, splitProp):
		
	if re.match('~', splitProp[0]):
		if p == 0:
			p = 1
		else:
			p = 0
	
	if re.match('~', splitProp[2]):
		if q == 0:
			q = 1
		else:
			q = 0

	if p == 1 and q == 0:
		return p, q, 'F'
	else:
		return p, q, 'T'

def tableLabel(prop, numVars):
	
	prop.lower()
	if numVars > 1:
		spaces = ""
		x = 0
		while x < numVars:
			spaces += "   "
			x += 1
		print(prop + spaces + "results")
	else:
		print(prop)

def tableOne(p):
	if (p % 2) == 0:
		a = 'T'
	else:
		a = 'F'
	print(a)

def tableTwo(p, q, result):
	if p == 0:
		a = 'T'
	else:
		a = 'F'

	if q == 0:
		b = 'T'
	else:
		b = 'F'

	print(a + "    " + b + "        " + result)


def tableThree(p, q, r, result):
	if p == 0:
		a = 'T'
	else:
		a = 'F'

	if q == 0:
		b = 'T'
	else:
		b = 'F'
	
	if r == 0:
		c = 'T'
	else:
		c = 'F'

	print(a + "    " + b + "    " + c + "        " + result)

#  truth = ['T','F']

def main():
	instructions()
	prop = input("Proposition: ")	
	evaluate(prop)
	
#	charPattern = '[a-zA-Z]'
#	tilde = '~'


#	count = 0
#	if length == 1:
#		print(prop)
#		while count < 2:
#			print(truth[count])
#			count += 1
#	elif length == 3:
#		print(prop + "  results")
#
		# DETERMINE AND OR IMPLIES
#		if splitProp[1] == "/\\":
#			p = 0
#			while p < 4:
#				q = 0
#				while q < 2:
#					if re.match(tilde, splitProp[0]):
						
					#compares p and q
#					if truth[p] == truth[q]:
#						x = 0
#					else:
#						x = 1
#					print(truth[p] + "    " + truth[q] + "       " + truth[x])
#					q += 1
#				p += 1
#		elif splitProp[1] == "\/":
#			p = 0
#			while p < 4:
#				q = 0
#				while q < 2:
#					#compares p and q
#					if (truth[p] == 'T') or (truth[q] == 'T'):
#						x = 0
#					else:
#						x = 1
#					print(truth[p] + "    " + truth[q] + "       " + truth[x])
#					q += 1
#				p += 1
#		elif splitProp[1] == ">":
#			p = 0
#			while p < 4:
#				q = 0
#				while q < 2:
#					#compares p and q
#					if truth[p] == 'F' and truth[q] == 'T':
#						x = 0
#					else:
#						x = 1
#					print(truth[p] + "    " + truth[q] + "       " + truth[x])
#					q += 1
#				p += 1

if __name__ == "__main__":
    main()
