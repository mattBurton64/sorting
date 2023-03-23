#some code provided by Jarrett Lancaster
import numpy as np
from matplotlib import pyplot as plt

a = 1.0   #polarizability of each molecules
dR = 0.1  #scale of position fluctuations
dq = 1.0  #amount of charge separated +/- dq

K = 1.0   #constant in Coulomb's law, 1/(4 pi epsilon_0)

N = 50    #number of positions to sample
rmin = 2.0 #minimum r sampled
rmax = 5.0 #maximum r sampled
r = np.linspace(rmin,rmax,N) #sampled positions


U = np.zeros(N) #array to store U(r)

N2 = 500 #number of fluctuations sampled per separation

def randomδr(δR):
    δr = (np.random.rand() - 0.5) * δR
    return δr

def Uexact(K,r,δr,δr2,δq,δq2):
    U = ((K * δq * δq2) / r) * ((-1/(1 + ((δr + δr2) / (2 * r)))) + (1/(1 + ((δr - δr2) / (2 * r)))) + (1/(1 - ((δr - δr2) / (2 * r)))) + (-1/(1 - ((δr + δr2) / (2 * r)))))
    return U

def dipoleE(K,r,δr,δq):
    E = K * (δq / ((r - (δr / 2)) ** 2)) - K * (δq / ((r + (δr / 2)) ** 2))
    return E

def Usample(K,dR,dq,r,a):
    p = np.random.rand()
    if (p>0.5): 
        δr1 = randomδr(dR)
        δq1 = dq
        
        #calculate the electric field E1 at a distance r due to 
        #the field created by the dipole
        E1 = dipoleE(K,r,δr1,δq1)
        
        #induced dipole moment in second dipole
        p2 = a*E1
        δq2 = dq
        δr2 = p2/δq2
        
        
    else: #if p<=0.5 repeat the previous steps 
        δr2 = randomδr(dR)
        δq2 = dq
        E2 = dipoleE(K,r,δr2,δq2)
        p1 = a*E2
        δq1 = dq
        δr1 = p1/δq1
        
    #evaluate Coulomb electrostatic potential energy Uo due to this configuration
    Uo = Uexact(K,r,δr1,δr2,δq1,δq2)
        
    return Uo

for i in range(0,N): #loop of values of r[i]
    Usum = 0.0 #add up all values U(r[i]) we get from these samples
    for j in range(0,N2):
        #Update Uo = Uo + (...) where (...) is another sample of the energy at r[i]
        
        Usum = Usum + Usample(K,dR,dq,r[i],a)
    
    U[i] = Usum/N2

plt.loglog(r, -U)
plt.show()

C = 1
def exponent(r,U):
    slope = np.polyfit(np.log(r),np.log(-U),1)
    return slope[0]

exponent(r,U)