#some code provided by Jarrett Lancaster
import numpy as np
from matplotlib import pyplot as plt

N = 100000 # number of steps 10^5
tmax = 5 # time range max 3 - 30
t = np.linspace(0,tmax,N)
dt = t[1] - t[0] # time between each step

G = 0.1 # force of gravity 

m1 = 100 # mass of body one 1-10
m2 = 1 # mass of body two 1-10

x1 = np.zeros(N) # x position for body one
x1[0] = 0 # initial x position for body one
y1 = np.zeros(N) # y position for body one
y1[0] = 0 # initial y position for body one
x2 = np.zeros(N) # x position for body two
x2[0] = 1 # initial x position for body two
y2 = np.zeros(N) # y position for body two
y2[0] = 0 # initial y position for body two

vo = np.sqrt((G * m1) / x2[0]) # initial velocity

vx1 = np.zeros(N) # x velocity for body one
vx1[0] = 0 # initial x velocity for body one
vy1 = np.zeros(N) # y velocity for body one
vy1[0] = 0 # initial y velocity for body one
vx2 = np.zeros(N) # x velocity for body two
vx2[0] = 0 # initial x velocity for body two
vy2 = np.zeros(N) # y velocity for body two
vy2[0] = vo # initial y velocity for body two
vx3 = np.zeros(N) # x velocity for body three

param = np.zeros(4)
param[0] = G
param[1] = m1
param[2] = m2

def dxdt(x,t,param):
    G = param[0]
    m1 = param[1]
    m2 = param[2]
    x1 = x[0]
    y1 = x[1]
    x2 = x[2]
    y2 = x[3]
    vx1 = x[4]
    vy1 = x[5]
    vx2 = x[6]
    vy2 = x[7]
    
    dx1 = vx1
    dy1 = vy1
    dx2 = vx2
    dy2 = vy2
    
    dvx1 = (-1 * ((G * m1 * m2) * (x1 - x2) / ((x1 - x2)**2 + (y1 - y2)**2)**(3/2))) / m1
    dvy1 = (-1 * ((G * m1 * m2) * (y1 - y2) / ((x1 - x2)**2 + (y1 - y2)**2)**(3/2))) / m1
    dvx2 = (-1 * ((G * m2 * m1) * (x2 - x1) / ((x2 - x1)**2 + (y2 - y1)**2)**(3/2))) / m2
    dvy2 = (-1 * ((G * m2 * m1) * (y2 - y1) / ((x2 - x1)**2 + (y2 - y1)**2)**(3/2))) / m2

    return np.array([dx1, dy1, dx2, dy2, dvx1, dvy1, dvx2, dvy2])

def rk4step(dxdt,t,x,dt,param):
    k1 = dt * dxdt(x,t,param)
    k2 = dt * dxdt(x + 0.5 * k1,t + 0.5 * dt, param)
    k3 = dt * dxdt(x + 0.5 * k2,t + 0.5 * dt, param)
    k4 = dt * dxdt(x + k3, t + dt, param)
    return (1.0/6.0)*(k1 + 2*k2 + 2*k3 + k4)

for i in range(0,N-1):
    x = [x1[i], y1[i], x2[i], y2[i], vx1[i], vy1[i], vx2[i], vy2[i]]
    step = rk4step(dxdt, t, x, dt, param)
    x1[i+1] = step[0] + x1[i]
    y1[i+1] = step[1] + y1[i]
    x2[i+1] = step[2] + x2[i]
    y2[i+1] = step[3] + y2[i]
    vx1[i+1] = step[4] + vx1[i]
    vy1[i+1] = step[5] + vy1[i]
    vx2[i+1] = step[6] + vx2[i]
    vy2[i+1] = step[7] + vy2[i]
    
plt.plot(x1,y1)
plt.plot(x2,y2)
plt.show()