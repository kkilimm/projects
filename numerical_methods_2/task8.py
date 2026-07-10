import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt('file8_2.txt')

x = data[:, 0]
y = data[:, 1]
u = data[:, 2]   
res = data[:, 3]   
error = data[:, 4] 

x_unique = np.unique(x)
y_unique = np.unique(y)
X, Y = np.meshgrid(x_unique, y_unique)

def grid_values(x, y, z):
    Z = np.full_like(X, np.nan, dtype=float)
    for i in range(len(x_unique)):
        for j in range(len(y_unique)):
            for k in range(len(x)):
                if x[k] == x_unique[i] and y[k] == y_unique[j]:
                    Z[j, i] = z[k]
    return Z


Z_u = grid_values(x, y, u)    
Z_res = grid_values(x, y, res)      
Z_error = grid_values(x, y, error)  

fig = plt.figure(figsize=(18, 5))

ax1 = fig.add_subplot(131, projection='3d')
ax1.plot_surface(X, Y, Z_u, cmap='viridis')
ax1.set_title('u(x, y)')
ax1.set_xlabel('x')
ax1.set_ylabel('y')

ax2 = fig.add_subplot(132, projection='3d')
ax2.plot_surface(X, Y, Z_res, cmap='plasma')
ax2.set_title('res')
ax2.set_xlabel('x')
ax2.set_ylabel('y')

ax3 = fig.add_subplot(133, projection='3d')
ax3.plot_surface(X, Y, Z_error, cmap='coolwarm')
ax3.set_title('error')
ax3.set_xlabel('x')
ax3.set_ylabel('y')

plt.show()
