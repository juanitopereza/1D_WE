import numpy as np
import matplotlib.pyplot as plt
# %%

dat = np.loadtxt("inicial.txt")
datf = np.loadtxt("final.txt")


plt.plot(dat[:,0], dat[:,1])
plt.show()
plt.plot(datf[:,0], datf[:,1])
plt.show()
