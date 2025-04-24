
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt

dist1=np.random.normal(0.1,06,10000)
dist2=np.random.normal(0.9,0.9,10000)

fig, ax = plt.subplots(2,2,figsize=(10,10))
ax = ax.flatten()

##Legend size may look bad, so let's override it
plt.rcParams['legend.fontsize']=15

ax[0].hist(dist1, bins=50, lw=2, alpha=0.5,label='dist1')
ax[0].hist(dist2, bins=50, lw=2, alpha=0.5,label='dist2')
ax[0].set_title('basic')
ax[0].legend(loc='upper left')

ax[1].hist(dist1, bins=50, lw=2, alpha=0.5,label='dist1',density=True)
ax[1].hist(dist2, bins=50, lw=2, alpha=0.5,label='dist2',density=True)
ax[1].set_title('normalized')
ax[1].legend(loc='upper right')

ax[2].hist(dist1, bins=50, lw=2, alpha=0.5,label='dist1',log=True)
ax[2].hist(dist2, bins=50, lw=2, alpha=0.5,label='dist2',log=True)
ax[2].set_title('logscale')
ax[2].legend(loc='lower right')

ax[3].hist(dist1, bins=50, lw=3, histtype='step',alpha=0.5,label='dist1',log=True,density=True)
ax[3].hist(dist2, bins=50, lw=3, histtype='step',alpha=0.5,label='dist2',log=True,density=True)
ax[3].set_title('cosmetic changes')
ax[3].legend(loc='lower center')

plt.savefig("tity_plot.png")