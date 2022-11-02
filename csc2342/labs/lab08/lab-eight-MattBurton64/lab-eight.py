"""
Matt Burton
csc2342 01
3/21/15
"""

"""Functions"""
"""
Factorial
_________
A function to calculate the factorial of any positive integer.
"""
def factorial(n):
	factorial = 1

	if n < 0:
		print("Error: can't factorial negative numbers.")
	if n == 0:
		factorial = 1
	else:
		for i in range(1,n + 1):
			factorial = factorial*i

	return factorial

"""Main"""

string = str(input("Enter a string:"))
length = int(len(string))

print("Enter a k larger than " + str(length) + ".")
k = length - 1
while 0 >= length or length >= k:
	k = int(input("k:"))

print("(", length, ")! / (", length, " - ", k, ")!")
print(" = ", factorial(length) / factorial(length - k))


