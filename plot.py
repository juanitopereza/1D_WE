import numpy as np
import matplotlib.pyplot as plt

#%%

data = np.loadtxt("cuerda.dat")

np.shape(data)
size_x = np.shape(data)[1]
size_y = np.shape(data)[0]

x = np.linspace(0,1, size_x)

#%%

fig = plt.figure(figsize=(15,10))
ax = fig.add_subplot(131)
ax.imshow(data, aspect="auto")

ax2 = fig.add_subplot(132)
tiempos = [0, 50, 100, 200, 300, 400, 500, 600, -1]
for tiempo in tiempos:
    ax2.plot(x,data[tiempo])

plt.savefig("resultados.png")
