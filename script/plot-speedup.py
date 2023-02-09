import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm

fig = plt.figure(figsize= (8, 8))

# Load sequential time required to compute speedup
seq_time = np.loadtxt("../build/timing.csv", delimiter=",", usecols=1, max_rows=1)

# Load input points
Z = np.loadtxt("../build/timing.csv", delimiter=",", skiprows=1)
X = Z[:,0]
Y = seq_time/Z[:,1]

# Compute linear regression
coef = np.polyfit(X,Y,1)
poly1d_fn = np.poly1d(coef) 

# Plotting data
plt.scatter(X, Y)
plt.plot(X, poly1d_fn(X), '--k')

# Setting axis
plt.xscale('log')
plt.xlabel('# Processors')
plt.ylabel('Speedup')
plt.grid(True)

# Save solution plot
plt.suptitle("TIMING")
plt.savefig("../build/timing.png")

# DIsplay plot
plt.show()