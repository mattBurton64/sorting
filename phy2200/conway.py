import numpy as np
from matplotlib import pyplot as plt
from time import sleep # To set the animation frame rate 
from IPython.display import clear_output # To redraw

def nn2(i,j,N):
    neighbors = np.zeros(8)
    
    il = i-1
    ir = i+1

    jl = j-1
    jr = j+1 
    
    upLeft = [il, jl]
    up = [il, j]
    upRight = [il, jr]
    left = [i, jl]
    right = [i, jr]
    downLeft = [ir, jl]
    down = [ir, j]
    downRight = [ir, jr]
    
    neighbors = [upLeft, up, upRight, left, right, downLeft, down, downRight]  
    return neighbors

def conwaystep2(x):
    N = len(x) #get system size (assumed square)
    xnew = np.zeros((N,N)) #array to store updated values
    
    for i in range(0,N):
        for j in range(0,N):
            neighbors = nn2(i,j,N)
            nsum = 0
            # YOUR CODE HERE
            for k in range(0, 8):
                if min(neighbors[k]) > -1 and max(neighbors[k]) < N:
                    io = neighbors[k][0]
                    jo = neighbors[k][1] 
                    nsum = nsum + x[io,jo]
            
            if x[i,j] == 1: # if the current cell is alive
                if nsum < 2 or nsum > 3:
                    xnew[i,j] = 0
                else:
                    xnew[i,j] = 1
            elif x[i,j] == 0: #if the current cell is dead
                if nsum == 3:
                    xnew[i,j] = 1
                else:
                    xnew[i,j] = 0
    
    return xnew

N = 50
Nt = 100
x = np.zeros((N,N,Nt))

x[:,:,0] = np.random.randint(0,2,(N,N))
for n in range(0,Nt-1):
    x[:,:,n+1] = conwaystep(x[:,:,n])

for n in range(0,Nt):
    sleep(0.01) # Sets the maximum animation speed
    plt.imshow(x[:,:,n],cmap='gray')
    clear_output(wait=True)
    plt.show()
