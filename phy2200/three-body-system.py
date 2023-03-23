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

plt.plot(x1,y1, 'b.')
plt.plot(x2,y2, 'r.')
plt.plot(x3,y3, 'g.')
plt.show()