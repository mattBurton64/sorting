import numpy as np
from matplotlib import pyplot as plt

def rw2d(x,y):
    # YOUR CODE HERE
    a = int(np.sign(np.random.rand() - 0.5))
    xnew = x + a
    b = int(np.sign(np.random.rand() - 0.5))
    ynew = y + b
    return xnew, ynew

Nt = 10000
x = np.zeros(Nt)
y = np.zeros(Nt)

for n in range(0,Nt-1):
    x[n+1], y[n+1] = rw2d(x[n],y[n])
    
plt.plot(x,y)
plt.plot(x[0],y[0],'bo')
plt.plot(x[Nt-1],y[Nt-1],'ro')
plt.xlabel('x')
plt.ylabel('y')
plt.show()