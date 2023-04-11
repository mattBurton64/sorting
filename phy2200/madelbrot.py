import numpy as np
from matplotlib import pyplot as plt

def mandelbrotstep(z,c):
    znew = z**2 + c
    return znew

Nx = 601
Ny = 401

N = 50

y = np.linspace(-1,1,Ny)
x = np.linspace(-2.5,0.5,Nx)

m = np.zeros((Ny,Nx))

bound = 4

for i in range(0,Nx):
    for j in range(0,Ny):
        c = x[i] + 1j*y[j]
        z = c
        # YOUR CODE HERE
        n = 0
        while(z < bound and n <= N):
            z = mandelbrotstep(z, c)
            n += 1
        if n < N:
            m[j, i] = 0
        else:
            m[j, i] = 1

f = plt.figure()
f.set_figwidth(12)
f.set_figheight(8)
plt.imshow(m,cmap='Greys')
plt.show()