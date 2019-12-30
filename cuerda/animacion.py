import numpy as np
import matplotlib.pyplot as plt

datos = np.loadtxt('datos_cuerda.dat')

for i in range(np.shape(datos)[0]):
    plt.plot(datos[i], c='red')
    plt.ylim(-1.5,1.5)
    plt.title('Cuerda Vibrando')
    if(i<10):
        plt.savefig('cuerda_00%d.png'%(i))
        plt.close()
    elif(i<100):
        plt.savefig('cuerda_0%d.png'%(i))
        plt.close()
    else:
        plt.savefig('cuerda_%d.png'%(i))
        plt.close()
