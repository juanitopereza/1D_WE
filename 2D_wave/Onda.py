
# coding: utf-8

#%%

import numpy as np
import os
import matplotlib.pyplot as plt
import time

#%%
inicio = time.time()
# Declaramos las variables del problema calculando dt de forma que cumpla con la condición de estabilidad para r.
tmin = 0.0
tmax = 60.0
xmin = -15.0
xmax = 15.0
ymin = -15.0
ymax = 15.0
NPoints = 300
dx = (xmax - xmin)/NPoints
dy = (ymax - ymin)/NPoints
dRejilla = 1.0
c = 1.0
r = 0.7
dt = (r*dx)/c
NTime = int((tmax - tmin)/dt)+1


#%%

# Creamos el espacio-tiempo del problema. Grilla con NPoints puntos espaciales.
xPoints=np.linspace(xmin,xmax,NPoints)
yPoints=np.linspace(ymin,ymax,NPoints)
xmesh,ymesh=np.meshgrid(xPoints,yPoints)
tPoints=np.linspace(tmin,tmax,NTime)
E_T=np.zeros((NTime,NPoints,NPoints))

#%%

# Imponemos condiciones iniciales. Pulso Gaussiano con amplitud -0.5, ubicado a un tercio de la Grilla.
stdev=0.2
E_T[0]=-0.5*np.exp(-xmesh**2/(2*stdev**2))*np.exp(-(ymesh-5)**2/(2*stdev**2))
E_T[1]=E_T[0]+r**2/2.*(np.roll(E_T[0],1,axis=0)+np.roll(E_T[0],-1,axis=0)+np.roll(E_T[0],1,axis=1)+np.roll(E_T[0],-1,axis=1)-4*E_T[0])
E_T[0,0]=0
E_T[0,-1]=0
E_T[0,99,:(NPoints/2-int(dRejilla/dx)/2)]=0
E_T[0,99,(NPoints/2+int(dRejilla/dx)/2):]=0
E_T[1,:,0]=0
E_T[1,:,-1]=0
E_T[1,99,:(NPoints/2-int(dRejilla/dx)/2)]=0
E_T[1,99,(NPoints/2+int(dRejilla/dx)/2):]=0

# Evolución temporal.
for i in range(2,NTime):

    E_T[i]=2*(1.0-2.0*r**2)*E_T[i-1]-E_T[i-2]+r**2*(np.roll(E_T[i-1],1,axis=1)+np.roll(E_T[i-1],-1,axis=1)+np.roll(E_T[i-1],1,axis=0)+np.roll(E_T[i-1],-1,axis=0))
    E_T[i,0]=0
    E_T[i,-1]=0
    E_T[i,:,0]=0
    E_T[i,:,-1]=0
    E_T[i,99,:(NPoints/2-int(dRejilla/dx)/2)]=0
    E_T[i,99,(NPoints/2+int(dRejilla/dx)/2):]=0


#%%

# Grafica la onda en la cubeta para tiempos t=30 y t=60.
tiempos = [425, 850]
for tiempo in tiempos:
    plt.pcolor(xPoints,yPoints,E_T[tiempo], cmap = 'gist_rainbow',vmin=-0.05, vmax=0.05)
    plt.hlines(y=-5.0, xmin = -15.0, xmax= 0.0-dRejilla/2.0,  color='k', linewidth=3)
    plt.hlines(y=-5.0, xmin = 0.0+dRejilla/2.0, xmax= 15.0,  color='k', linewidth=3)
    plt.hlines([-14.85, 14.82], xmin = -15.0, xmax= 15.0,  color='k', linewidth=5)
    plt.vlines([-14.8, 14.82], ymin=-15.0, ymax=15.0, color='k', linewidth=5)
    cbar = plt.colorbar()
    cbar.ax.set_ylabel('$Amplitud$',rotation=90)
    plt.xlim(xmin+dx,xmax-dx)
    plt.ylim(ymin+dy,ymax-dy)
    plt.xlabel('$x$')
    plt.ylabel('$y$')
    plt.title('$Onda\ en\ t\ =\ {}$'.format(int(tiempo*dt)+1))
    plt.savefig('Onda_t_{}'.format(int(tiempo*dt)+1))
    plt.close()

#%%
#Crea imagenes para hacer la animación
for i in np.arange(80):
    plt.pcolor(xPoints,yPoints,E_T[i*10], cmap = 'gist_rainbow',vmin=-0.05, vmax=0.05)
    plt.hlines(y=-5.0, xmin = -15.0, xmax= 0.0-dRejilla/2.0,  color='k', linewidth=3)
    plt.hlines(y=-5.0, xmin = 0.0+dRejilla/2.0, xmax= 15.0,  color='k', linewidth=3)
    plt.hlines([-14.85, 14.82], xmin = -15.0, xmax= 15.0,  color='k', linewidth=5)
    plt.vlines([-14.8, 14.82], ymin=-15.0, ymax=15.0, color='k', linewidth=5)
    cbar = plt.colorbar()
    cbar.ax.set_ylabel('$Amplitud$',rotation=90)
    plt.xlim(xmin+dx,xmax-dx)
    plt.ylim(ymin+dy,ymax-dy)
    plt.xlabel('$x$')
    plt.ylabel('$y$')
    plt.title('$Onda\ en\ t\ =\ {}$'.format(int(i*10*dt)+1))
    plt.savefig('foto_{}'.format(i))
    plt.close()
#%%
# Crea animación en formato .mp4 (Requiere ffmpeg) y borra las imagenes creadas anteriormente.
os.system("ffmpeg -nostats -loglevel 0 -framerate 4 -start_number 0 -i foto_%d.png -c:v libx264 -pix_fmt yuv420p Onda.mp4")
os.system("rm foto*")
#%%
final = time.time()
print(final-inicio)
