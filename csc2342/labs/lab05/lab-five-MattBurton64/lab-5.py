import time
from algorithm import Algorithm

#creates an algorithm class object
algorithm = Algorithm()

#user input integer list
ints = input("Enter a list of integers separated by whitespace:\n")
ints = ints.split()
length = len(ints)

#start stort
startTime = time.process_time()
algorithm.sort(ints, length)
endTime = time.process_time()
#end sort
timeElapsed = endTime - startTime

print("Time elapsed: ", timeElapsed, " seconds")

"""
The algorithm does not sort the list of integers from least to greatest as expected. The syntax of the code inside of the 'if-else' in the 'for' loop of sort() makes no sense to me. Also I tried printing the returned value of the sort() function as instructed by step 5. but it always results None because there is only one return and it is the escape return for lists of only one element. I ran what I have and compiled a list of the times below.

The sort function's Big O: O(n) since the for loop range increases linearly as there are more elements input

Input 						Results in seconds
1 2 3 						4.04810000000002e-05 
1 2 3 4 						9.084199999999897e-05
1 3 5 4 2					0.0005253789999999994
1 3 5 4 2 6 				0.0019387539999999991
1 3 5 4 2 6 8 7			0.11946689599999999
1 3 15 4 2 6 8 7 10 5   10.553621146

Make:
Model: Macbook Air
CPU Type: Dual-Core Intel Core i5
CPU Speed: 1.6 GHz
RAM: 8 GB
"""
