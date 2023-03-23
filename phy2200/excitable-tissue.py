import numpy as np
from matplotlib import pyplot as plt

I = 110
C = 20
gL = 2
gCa = 4.4
gK = 8
vL = -60
vCa = 130
vK = -84
v1 = -1.2
v2 = 18
v3 = 2
v4 = 30
ϕ = 0.04

param = np.zeros(13)
param[0] = I
param[1] = C
param[2] = gL
param[3] = gCa
param[4] = gK
param[5] = vL
param[6] = vCa
param[7] = vK
param[8] = v1
param[9] = v2
param[10] = v3
param[11] = v4
param[12] = ϕ

def mss(v,v1,v2):
    # YOUR CODE HERE
    return 0.5 * (1 + np.tanh((v - v1) / v2))
def wss(v,v3,v4):
    # YOUR CODE HERE
    return 0.5 * (1 + np.tanh((v - v3) / v4))
def τ(ϕ,v,v3,v4):
    # YOUR CODE HERE
    return 1 / (ϕ * np.cosh((v - v3) / (2 * v4)))
    
def dxdt(x,t,param):
    v = x[0]
    w = x[1]
    
    # YOUR CODE HERE
    I = param[0]
    C = param[1]
    gL = param[2]
    gCa = param[3]
    gK = param[4]
    vL = param[5]
    vCa = param[6]
    vK = param[7]
    v1 = param[8]
    v2 = param[9]
    v3 = param[10]
    v4 = param[11]
    ϕ = param[12]
    return np.array([(I - gL * (v - vL) - gCa * mss(v,v1,v2) * (v - vCa) - gK * w * (v - vK)) / C, (wss(v,v3,v4) - w) / τ(ϕ,v,v3,v4)])

def rk4step(deriv,t,x,dt,param):
    # YOUR CODE HERE    
    k1 = dt*deriv(x,t,param)
    k2 = dt*deriv(x+0.5*k1,t+0.5*dt,param)
    k3 = dt*deriv(x+0.5*k2,t+0.5*dt,param)
    k4 = dt*deriv(x+k3,t+dt,param)
 
    return (1.0/6.0)*(k1+2*k2+2*k3+k4)

vo = 0.0
wo = 0.0

xo = np.array([vo,wo])

tmax = 1000
N = 10000
t = np.linspace(0,tmax,N)
dt = t[1]-t[0]

v = np.zeros(N)
w = np.zeros(N)

v[0] = vo
w[0] = wo

for i in range(0,N-1):
    x = rk4step(dxdt,t,[v[i],w[i]],dt,param)
    v[i+1] = x[0] + v[i]
    w[i+1] = x[1] + w[i]

plt.plot(t,v)
plt.xlabel('t (ms)')
plt.ylabel('voltage (mV)')
plt.show()

plt.plot(v,w)
plt.xlabel('t (ms)')
plt.ylabel('voltage (mV)')
plt.show()