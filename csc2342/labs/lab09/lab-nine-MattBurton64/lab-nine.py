"""
Matt Burton
csc2342
03/29/21
"""

A = 0.01 * float(input("Enter the percentage of the population that has skin cancer: ")) #20%
B = 0.01 * float(input("Enter the percentage of population with moles but no skin cancer: ")) #15%
print("A: ",A,"%")
print("B: ",B,"%")
BA = A * B / B

print("The conditional probabiltiy is:", BA * A / B)
