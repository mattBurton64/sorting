#!/usr/bin/env python3

__author__ = "Jason M. Pittman and Matt Burton"
__copyright__ = "Copyright 2021"
__credits__ = ["Jason M. Pittman and Matt Burton"]
__license__ = "GPLv3"
__version__ = "1.0.0"
__maintainer__ = "Jason M. Pittman and Matt Burton"
__email__ = "jpittman@highpoint.edu and mburton2@highpoint.edu"
__status__ = "Finished"

from sympy import *

class Proof:
	"""A class to demonstrate the modus ponens rule of inference"""

	def Proposition(self, p):
		"""Takes in a single proposition as a Boolean value and returns the appropriate Truth Value"""
		return sympify(p)

	def Implication(self, p, q):
		"""Takes in two propositions as Boolean values and returns appropriate Truth Value based on the implication connective"""
		x, y = symbols('x, y')
		return (x >> y).subs({x : p, y: q})

	def Ponens(self, p, q):
		"""Takes in two propositions as Boolean values and returns the approriate Truth Value based on modus ponens"""	
		return self.Implication(self.Proposition(p) and self.Implication(p, q), q)

	def Tollens(self, p, q):
		"""Takes in two propositions as Boolean values and returns the appropriate Truth Value based on modus Tollens"""
		return self.Implication(self.Proposition(not q) and self.Implication(p, q), not p)

	def CharToBool(self, p):
		"""Takes in a proposition as a Char and returns the appropriate Boolean value"""
		if p == 'T':
			return True
		else:
			return False

proof = Proof()

print("Enter only 'T' or 'F'.")
p = input("p: ")
q = input("q: ")
print("Select from the following list of rules of inference.\n 1) Ponens\n 2) Tollens")
roi = input("#: ")

p = proof.CharToBool(p)
q = proof.CharToBool(q)

if roi == '1':
	print(proof.Ponens(p,q))
elif roi == '2':
	print(proof.Tollens(p,q))
else:
	print("Invalid input.")

"""
		
		if self.Proposition(p) and self.Implication(p,q):
			return self.Implication(True, q)
		else:
			return self.Implication(False, q)

		if self.Proposition(not q) and self.Implication(p, q):	
			return self.Implication(True, not p)
		else:
			return self.Implication(False, not p)

	def Not(self, p):
	#Takes in a proposition as a Boolean value and returns the opposite Truth Value
		if sympify(p):
			return False
		else:
			return True

print("\np q results \n")
print(proof.Proposition(p))
print(proof.Proposition(q))

print("\nPonens truth table\n")
print(proof.Ponens(True, True)) 
print(proof.Ponens(True, False)) 
print(proof.Ponens(False, True))	 
print(proof.Ponens(False, False)) 

print("\nTollens truth table\n")
print(proof.Tollens(True, True)) 
print(proof.Tollens(True, False)) 
print(proof.Tollens(False, True)) 
print(proof.Tollens(False, False))
"""
