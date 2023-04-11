import numpy as np
from matplotlib import pyplot as plt
from time import sleep # To set the animation frame rate 
from IPython.display import clear_output # To redraw

def nn(i,j,N):
    if i==0:
        il = N-1
        ir = 1    
    elif i==N-1:
        il = N-2
        ir = 0
    else:
        il = i-1
        ir = i+1
        
    if j==0:
        jl = N-1
        jr = 1    
    elif j==N-1:
        jl = N-2
        jr = 0
    else:
        jl = j-1
        jr = j+1 
    
    return [il,ir,jl,jr]        

def initialize(N):
    x = np.zeros((N,N))
    # YOUR CODE HERE
    for i in range(0, N - 1):
        for j in range(0, N - 1):
            if np.random.rand() <= 0.25:
                x[i, j] = 1
            else:
                x[i, j] = 0
    return x

def forestupdate(x,p,f):
    N = len(x)
    xnew = np.zeros((N,N))
    # YOUR CODE HERE
    for i in range(0, N - 1):
        for j in range(0, N - 1):
            if x[i, j] == 1: # tree
                (il, ir, jl, jr) = nn(i,j,N)
                if max([x[i,jl], x[i,jr], x[il,j], x[ir,j]]) == 2 or np.random.rand() <= f:
                     xnew[i, j] = 2
                else:
                    xnew[i, j] = 1
            elif x[i, j] == 0: # empty
                if np.random.rand() <= p:
                    xnew[i, j] = 1

    return xnew

N = 40
p = 30/(N**2)
f = 0.1/(N**2)

Nt = 100
x = np.zeros((N,N,Nt))

x[:,:,0] = initialize(N)
            
for n in range(0,Nt-1):
    x[:,:,n+1] = forestupdate(x[:,:,n],p,f)

for n in range(0,Nt):
    sleep(0.01) # Sets the maximum animation speed
    plt.imshow(x[:,:,n],cmap='turbo',vmin=0, vmax=2)
    clear_output(wait=True)
    plt.show()