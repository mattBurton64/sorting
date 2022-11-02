""""
Matt Burton
csc2342 01
03/05/21
C grade
"""
import itertools

def orderedInput():
	
	inputSet = set()

	inputSet = input("Separate set values with spaces.\n")
	intSet = inputSet.split()

	return intSet

def listInput():
		
	allLists = []

	oneList = input("Separate list values with spaces.\nEnter '!' when finished.\n")
	
	while oneList != '!':
		allLists.append(oneList)
		oneList = input()
	
	for string in allLists:
		intList = string.split()
		for i in intList:
			intList[i] = int(intList[i])
		allLists[string] = intList

	return allLists


"""MAIN"""
order = input("Welcome to the combinatorics and permutation calculator.\nDoes order matter? y/n.\n")

if order == 'y' or order == "Y":	
	r = int(input("Enter r.\n"))
	if r < 0:
		r = 0
	perm = itertools.permutations(orderedInput(), r)
	print(*perm)
else:
	allLists = listInput()
#	allSets.discard(' ')
	print(allLists)
	print("Sum Rule\n")
	print(sum(allLists))

	print("Product Rule\n")
	print(itertools.product(allLists))

