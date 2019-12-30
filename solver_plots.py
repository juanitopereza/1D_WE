import numpy as np
import matplotlib.pyplot as plt
#%%

data1 = np.loadtxt("data_euler.dat")
data2 = np.loadtxt("data_rk4.dat")

np.shape(data1)

fig = plt.figure(figsize=(25,10))
ax = fig.add_subplot(121)
ax.plot(data1[:,0], data1[:,1], label="euler")
ax.plot(data2[:,0], data2[:,1], label="rk4")
ax.set_title("$x\ vs.\ t$")
ax.legend(loc="lower right")

ax1 = fig.add_subplot(122)
ax1.plot(data1[:,1], data1[:,2], label="euler")
ax1.plot(data2[:,1], data2[:,2], label="rk4")
ax1.set_title("$v\ vs.\ x$")
ax1.legend()

plt.savefig("plot_1.png")
plt.close()

lambs=["1","2","3","1/2", "3/2", "4"]

fig2 = plt.figure(figsize=(15,15))
ax = fig2.add_subplot(111)
for i in range(6):
    data = np.loadtxt("data_fr_{}.dat".format(i))
    ax.plot(data[:,0], data[:,1], label="$\lambda=\ {}$".format(lambs[i]))
    ax.set_ylim(-1.5,1.5)
ax.legend()
plt.savefig("plot_fr.png")
plt.close()
