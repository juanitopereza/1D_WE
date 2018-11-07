import numpy as np
import matplotlib.pyplot as plt
from matplotlib import animation
#%%

def init():
    line.set_data({},{})
    time_text.set_text("")
    return line,
def animate(i):
    x = datos[0,:]
    y = datos[i,0:]
    line.set_data(x,y)
    time_text.set_text("$t\ =\ %f$" %datos[i,0])
    return line,

datos = np.loadtxt("datos.txt")

fig = plt.figure()

ax = plt.axes(xlim=(0, 1), ylim=(-1.5, 1.5))
ax.set_title("$Onda$")
time_text = ax.text(0.02, 0.85, '', transform=ax.transAxes)
line, = ax.plot([], [], lw=2, c="#f21aef")


anim = animation.FuncAnimation(fig, animate, init_func=init,
                               frames=350, interval=10, blit=True)
anim.save('datos.gif', fps=30, writer="imagemagick")
