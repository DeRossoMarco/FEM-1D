import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm

fig = plt.figure(figsize= (8, 8))
ax = plt.axes(projection='3d')

# Load parameters
h = np.loadtxt("../build/output.csv", delimiter=",", usecols=0, max_rows=1)
dt = np.loadtxt("../build/output.csv", delimiter=",", usecols=1, max_rows=1)

# Load 2D array
Z = np.loadtxt("../build/output.csv", delimiter=",", skiprows=1)

# Set space and time range
row_count = len(Z)
col_count = len(Z[0])
t = np.arange(0.0, dt * row_count, dt, dtype=float)
x = np.arange(0.0, h * col_count, h, dtype=float)

# Set mesh
X, T = np.meshgrid(x, t)

# Set plot option
surf = ax.plot_surface(T, X, Z, cmap=cm.jet)
fig.colorbar(surf, shrink=0.5, aspect=5)
ax.set_xlabel('Time [s]', labelpad=20)
ax.set_ylabel('Position [m]', labelpad=20)
ax.set_zlabel('Intensity', labelpad=20)

# Save solution plot
plt.suptitle("SOLUTION")
plt.savefig("../build/solution.pdf")

# DIsplay 3D solution
plt.show()
