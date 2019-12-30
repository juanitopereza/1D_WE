# coding=utf-8

import numpy as np
import matplotlib.pyplot as plt

#%%

def f(x,y,yp):
    return q_m * B_z * yp + (q_m * Lambda * x)/(2 * np.pi * epsilon_0 * (x**2 + y**2))
def g(x,y,xp):
    return -q_m * B_z * xp + (q_m * Lambda * y)/(2 * np.pi * epsilon_0 * (x**2 + y**2))

def RK_step(delta_t, x_old, y_old, xp_old, yp_old):

    k_x1 = xp_old * delta_t
    k_y1 = yp_old * delta_t
    k_xp1 = f(x_old, y_old, yp_old) * delta_t
    k_yp1 = g(x_old, y_old, xp_old) * delta_t

    #print (k_x1, k_y1, k_xp1, k_yp1)

    k_x2 = (xp_old + k_xp1/2.0) * delta_t
    k_y2 = (yp_old + k_yp1/2.0) * delta_t
    k_xp2 = f(x_old + k_x1/2.0, y_old + k_y1/2.0, yp_old + k_yp1/2.0) * delta_t
    k_yp2 = g(x_old + k_x1/2.0, y_old + k_y1/2.0, xp_old + k_xp1/2.0) * delta_t

    #print (k_x2, k_y2, k_xp2, k_yp2)

    k_x3 = (xp_old + k_xp2/2.0) * delta_t
    k_y3 = (yp_old + k_yp2/2.0) * delta_t
    k_xp3 = f(x_old + k_x2/2.0, y_old + k_y2/2.0, yp_old + k_yp2/2.0) * delta_t
    k_yp3 = g(x_old + k_x2/2.0, y_old + k_y2/2.0, xp_old + k_xp2/2.0) * delta_t

    #print (k_x3, k_y3, k_xp3, k_yp3)

    k_x4 = (xp_old + k_xp3) * delta_t
    k_y4 = (yp_old + k_yp3) * delta_t
    k_xp4 = f(x_old + k_x3, y_old + k_y3, yp_old + k_yp3) * delta_t
    k_yp4 = g(x_old + k_x3, y_old + k_y3, xp_old + k_xp3) * delta_t

    #print (k_x4, k_y4, k_xp4, k_yp4)

    x_new = x_old + (1.0/6.0)*(k_x1 + 2.0*k_x2 + 2.0*k_x3 + k_x4)
    y_new = y_old + (1.0/6.0)*(k_y1 + 2.0*k_y2 + 2.0*k_y3 + k_y4)
    xp_new = xp_old + (1.0/6.0)*(k_xp1 + 2.0*k_xp2 + 2.0*k_xp3 + k_xp4)
    yp_new = yp_old + (1.0/6.0)*(k_yp1 + 2.0*k_yp2 + 2.0*k_yp3 + k_yp4)

    return x_new, y_new, xp_new, yp_new
#%%

q_m = -1.76e11
Lambda = -1e-12
B_z = 1e-5
epsilon_0 = 9e-12

N_points = 2000
t_final = 2e-5

delta_t = t_final/N_points

delta_t

t = np.zeros(N_points)
X = np.zeros(N_points)
Y = np.zeros(N_points)
XP = np.zeros(N_points)
YP = np.zeros(N_points)

t[0] = 0.0
X[0] = 2.0
Y[0] = 2.0
XP[0] = 0.0
YP[0] =-3000.0

for i in range(1,N_points):
    X[i], Y[i], XP[i], YP[i] = RK_step(delta_t, X[i-1], Y[i-1], XP[i-1], YP[i-1])
    t[i] = t[i-1] + delta_t
    #print (t[i], X[i], Y[i], XP[i], YP[i])


#%%
plt.plot(X,Y, label= "$RK4$")
plt.legend()
plt.xlabel("$x\ [m]$")
plt.ylabel("$y\ [m]$")
plt.title(u"$Trayectoria\ electrón$")

plt.savefig("electron.pdf")

#plt.show()
