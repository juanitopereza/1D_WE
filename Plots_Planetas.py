# coding: utf-8

#%%
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
#%%
datos = np.loadtxt('Pos_Planetas.csv', delimiter=',')
#%%

np.shape(datos)

sol = datos[:,1:4]
mercurio = datos[:,4:7]
venus = datos[:,7:10]
tierra = datos[:,10:13]
marte = datos[:,13:16]
jupiter = datos[:,16:19]
saturno = datos[:,19:22]
urano = datos[:,22:25]
neptuno = datos[:,25:28]
pluton = datos[:,28:]

#%%
fig = plt.figure(figsize=(10,10))
ax = fig.gca(projection='3d')
ax.plot(sol[:,0], sol[:,1], sol[:,2], label='Sol')
ax.plot(mercurio[:,0], mercurio[:,1], mercurio[:,2], label='Mercurio')
ax.plot(venus[:,0], venus[:,1], venus[:,2], label='Venus')
ax.plot(tierra[:,0], tierra[:,1], tierra[:,2], label='Tierra')
ax.plot(marte[:,0], marte[:,1], marte[:,2], label='Marte')
ax.plot(jupiter[:,0], jupiter[:,1], jupiter[:,2], label='Jupiter')
ax.plot(saturno[:,0], saturno[:,1], saturno[:,2], label='Saturno')
ax.plot(urano[:,0], urano[:,1], urano[:,2], label='Urano')
ax.plot(neptuno[:,0], neptuno[:,1], neptuno[:,2], label='Neptuno')
ax.plot(pluton[:,0], pluton[:,1], pluton[:,2], label='Pluton')
ax.scatter([0.0],[0.0],[0.0], s=600)
ax.set_xlabel('$x\ [AU]$')
ax.set_ylabel('$y\ [AU]$')
ax.set_zlabel('$z\ [AU]$')
ax.set_title('$Orbitas$', fontsize= 20)
ax.legend()
#plt.show()

plt.savefig('Orbitas')

#%%
for i in np.arange(10):
    fig = plt.figure(figsize=(10,10))
    ax = fig.gca(projection='3d')
    ax.plot([sol[i*1000,0]], [sol[i*1000,1]], [sol[i*1000,2]], 'ro', label='Sol')
    ax.plot([mercurio[i*1000,0]], [mercurio[i*1000,1]], [mercurio[i*1000,2]],'bo', label='Mercurio')
    ax.plot([venus[i*1000,0]], [venus[i*1000,1]], [venus[i*1000,2]],'go', label='Venus')
    ax.plot([tierra[i*1000,0]], [tierra[i*1000,1]], [tierra[i*1000,2]],'yo', label='Tierra')
    ax.plot([marte[i*1000,0]], [marte[i*1000,1]], [marte[i*1000,2]],'ko', label='Marte')
    ax.plot([jupiter[i*1000,0]], [jupiter[i*1000,1]], [jupiter[i*1000,2]],'co', label='Jupiter')
    ax.plot([saturno[i*1000,0]], [saturno[i*1000,1]], [saturno[i*1000,2]],'mo', label='Saturno')
    ax.plot([urano[i*1000,0]], [urano[i*1000,1]], [urano[i*1000,2]],'bo', label='Urano')
    ax.plot([neptuno[i*1000,0]], [neptuno[i*1000,1]], [neptuno[i*1000,2]],'bo', label='Neptuno')
    ax.plot([pluton[i*1000,0]], [pluton[i*1000,1]], [pluton[i*1000,2]],'bo', label='Pluton')
    ax.set_xlabel('$x\ [AU]$')
    ax.set_ylabel('$y\ [AU]$')
    ax.set_zlabel('$z\ [AU]$')
    ax.set_title('$Orbitas$', fontsize= 20)
    ax.legend()

    plt.savefig('orb_{}'.format(i))

#%%
os.system("ffmpeg -nostats -loglevel 0 -framerate 1 -start_number 0 -i orb_%d.png -c:v libx264 -pix_fmt yuv420p Orbitas.mp4")
os.system("rm orb*")



 #%%
