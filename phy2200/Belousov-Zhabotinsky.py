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


def bzstep(x,q,k1,k2,g):
    N = len(x)
    xnew = np.zeros((N,N))
    for i in range(0,N):
            for j in range(0,N):
                # YOUR CODE HERE
                if x[i,j] == q:
                    xnew[i,j] = 1
                elif x[i,j] == 1:
                    (il, ir, jl, jr) = nn(i,j,N)
                    neighbors = [x[il,jl], x[i,jl], x[ir, jl], x[il,j], x[ir,j], x[il,jr], x[i,jr], x[ir, jr]]
                    
                    a = 0
                    b = 0
                    for neighbor in neighbors:
                        if neighbor == q:
                            b += 1
                        elif neighbor > 1:
                            a += 1
                    
                    #a = len(neighbors[neighbors > 1 or neighbors < q])
                    #b = len(neighbors[neighbors==q])
                    xnew[i,j] = np.floor(a/k1) + np.floor(b/k2) + 1
                elif x[i,j] > 1 and x[i,j] < q:
                    (il, ir, jl, jr) = nn(i,j,N)
                    neighbors = [x[il,jl], x[i,jl], x[ir, jl], x[il,j], x[ir,j], x[il,jr], x[i,jr], x[ir, jr]]
                    
                    S = sum(neighbors) + x[i,j]
                    
                    c = 0
                    for neighbor in neighbors:
                        if neighbor == 2:
                            c += 1
                    #c = len(neighbors[neighbors==1])
                    
                    xnew[i,j] = S/(9 - c) + g
                if xnew[i,j] > q:
                    xnew[i,j] = q
                    
    return xnew              

N = 50
Nt = 300
x = np.zeros((N,N,Nt))

q = 200
k1 = 2 
k2 = 3
g = 70


x[:,:,0] = np.random.randint(0,q,(N,N))+1

for n in range(0,Nt-1):
    x[:,:,n+1] = bzstep(x[:,:,n],q,k1,k2,g)

for n in range(0,Nt):
    sleep(0.01) 
    plt.imshow(x[:,:,n])#,cmap='hot')
    clear_output(wait=True)
    plt.show()