#some code provided by Jarrett Lancaster
import numpy as np
from matplotlib import pyplot as plt

N = 100000 # number of steps 10^5
tmax = 10 # time range max 3 - 30
t = np.linspace(0,tmax,N)
dt = t[1] - t[0] # time between each step
    
G = 0.1 # force of gravity 
ϵ = 0.01 # softening factor 0.01 - 0.1
    
m1 = 100 # mass of body one 1-10
m2 = 1 # mass of body two 1-10
m3 = 1 # mass of body three 1-10

x1 = np.zeros(N) # x position for body one
x1[0] = 0 # initial x position for body one
y1 = np.zeros(N) # y position for body one
y1[0] = 0 # initial y position for body one
x2 = np.zeros(N) # x position for body two
x2[0] = 1 # initial x position for body two
y2 = np.zeros(N) # y position for body two
y2[0] = 0 # initial y position for body two
x3 = np.zeros(N) # x position for body three
x3[0] = 0 # initial x position for body three
y3 = np.zeros(N) # y position for body three
y3[0] = 2 # initial y position for body three

#vo = np.sqrt((G * m2) / x2[0]) # initial velocity

vx1 = np.zeros(N) # x velocity for body one
vx1[0] = 0 # initial x velocity for body one
vy1 = np.zeros(N) # y velocity for body one
vy1[0] = 0 # initial y velocity for body one
vx2 = np.zeros(N) # x velocity for body two
vx2[0] = 0 # initial x velocity for body two
vy2 = np.zeros(N) # y velocity for body two
vy2[0] = 3 # initial y velocity for body two
vx3 = np.zeros(N) # x velocity for body three
vx3[0] = 2 # initial x velocity for body three
vy3 = np.zeros(N) # y velocity for body three
vy3[0] = 0 # initial y velocity for body three

param = np.zeros(4)
param[0] = G
param[1] = m1
param[2] = m2
param[3] = m3

def dxdt(x,t,param):
    G = param[0]
    m1 = param[1]
    m2 = param[2]
    m3 = param[3]
    
    x1 = x[0]
    y1 = x[1]
    x2 = x[2]
    y2 = x[3]
    x3 = x[4]
    y3 = x[5]
    vx1 = x[6]
    vy1 = x[7]
    vx2 = x[8]
    vy2 = x[9]
    vx3 = x[10]
    vy3 = x[11]
    
    dx1 = vx1
    dy1 = vy1
    dx2 = vx2
    dy2 = vy2
    dx3 = vx3
    dy3 = vy3
    
    dvx1 = ((-1 * ((G * m1 * m2) * (x1 - x2) / ((x1 - x2)**2 + (y1 - y2)**2 + ϵ)**(3/2))) - (-1 * ((G * m1 * m3) * (x1 - x3) / ((x1 - x3)**2 + (y1 - y3)**2 + ϵ)**(3/2)))) / m1
    dvy1 = ((-1 * ((G * m1 * m2) * (y1 - y2) / ((x1 - x2)**2 + (y1 - y2)**2 + ϵ)**(3/2))) - (-1 * ((G * m1 * m3) * (y1 - y3) / ((x1 - x3)**2 + (y1 - y3)**2 + ϵ)**(3/2)))) / m1
    dvx2 = ((-1 * ((G * m2 * m1) * (x2 - x1) / ((x2 - x1)**2 + (y2 - y1)**2 + ϵ)**(3/2))) - (-1 * ((G * m2 * m3) * (x2 - x3) / ((x2 - x3)**2 + (y2 - y3)**2 + ϵ)**(3/2)))) / m2
    dvy2 = ((-1 * ((G * m2 * m1) * (y2 - y1) / ((x2 - x1)**2 + (y2 - y1)**2 + ϵ)**(3/2))) - (-1 * ((G * m2 * m3) * (y2 - y3) / ((x2 - x3)**2 + (y2 - y3)**2 + ϵ)**(3/2)))) / m2
    dvx3 = ((-1 * ((G * m3 * m1) * (x3 - x1) / ((x3 - x1)**2 + (y3 - y1)**2 + ϵ)**(3/2))) - (-1 * ((G * m3 * m2) * (x3 - x2) / ((x3 - x2)**2 + (y3 - y2)**2 + ϵ)**(3/2)))) / m3
    dvy3 = ((-1 * ((G * m3 * m1) * (y3 - y1) / ((x3 - x1)**2 + (y3 - y1)**2 + ϵ)**(3/2))) - (-1 * ((G * m3 * m2) * (y3 - y2) / ((x3 - x2)**2 + (y3 - y2)**2 + ϵ)**(3/2)))) / m3
    
    return np.array([dx1, dy1, dx2, dy2, dx3, dy3, dvx1, dvy1, dvx2, dvy2, dvx3, dvy3])

def rk4step(dxdt,t,x,dt,param):
    k1 = dt * dxdt(x,t,param)
    k2 = dt * dxdt(x + 0.5 * k1,t + 0.5 * dt, param)
    k3 = dt * dxdt(x + 0.5 * k2,t + 0.5 * dt, param)
    k4 = dt * dxdt(x + k3, t + dt, param)
    return (1.0/6.0)*(k1 + 2*k2 + 2*k3 + k4)

for i in range(0,N-1):
    x = [x1[i], y1[i], x2[i], y2[i], x3[i], y3[i], vx1[i], vy1[i], vx2[i], vy2[i], vx3[i], vy3[i]]
    step = rk4step(dxdt, t, x, dt, param)
    x1[i+1] = step[0] + x1[i]
    y1[i+1] = step[1] + y1[i]
    x2[i+1] = step[2] + x2[i]
    y2[i+1] = step[3] + y2[i]
    x3[i+1] = step[4] + x3[i]
    y3[i+1] = step[5] + y3[i]
    vx1[i+1] = step[6] + vx1[i]
    vy1[i+1] = step[7] + vy1[i]
    vx2[i+1] = step[8] + vx2[i]
    vy2[i+1] = step[9] + vy2[i]
    vx3[i+1] = step[10] + vx3[i]
    vy3[i+1] = step[11] + vy3[i]

plt.plot(x1,y1)
plt.plot(x2,y2)
plt.plot(x3,y3)
plt.show()