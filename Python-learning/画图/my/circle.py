from matplotlib.patches import Ellipse, Circle
import matplotlib.pyplot as plt

fig = plt.figure()
ax = fig.add_subplot(111)

# center
x, y = 0, 0

# plot circle
cir1 = Circle(xy = (x, y), radius=2, alpha=0.5)
ax.add_patch(cir1)

# plot center
ax.plot(x, y, 'ro')


# set axis
plt.axis('equal')
plt.xlim(-4, 4)

plt.axis('equal')
plt.ylim(-4, 4)

plt.show()
