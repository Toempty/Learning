from matplotlib.patches import Ellipse, Circle
import matplotlib.pyplot as plt

fig = plt.figure()
ax = fig.add_subplot(111)


# center
x, y = 0, 0

# plot circle
ell = Ellipse(xy = (x, y), width = 4, height = 8, angle = 30.0, facecolor= 'yellow', alpha=0.3)
ax.add_patch(ell)


# plot center
ax.plot(x, y, 'ro')


# set axis
plt.axis('equal')
plt.xlim(-4, 4)

plt.axis('equal')
plt.ylim(-4, 4)


plt.show()
