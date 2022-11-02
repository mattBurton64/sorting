"""
Matt Burton
csc2342
2/26/21
"""

def isPrime(num):	
	
	if len(num) > 6:
		print("Computing...")

	prime = True
	
	if int(num) <= 1:
		prime = False
		
	for x in range(2, int(num) - 1):
		if int(num) % x == 0:
			prime = False

	return prime

#input
num = input("Enter an integer to determine if it is prime or composite:\n")

#output
if isPrime(num):
	print(str(num) + " is prime.")
else:
	print(str(num) + " is composite.")
