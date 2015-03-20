# add library
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

from matplotlib.patches import FancyArrowPatch
from mpl_toolkits.mplot3d import proj3d

#####################################################################
# define a 3D arrow class
# Matplotlib_2 : 1251
# set_positions: 1254
class Arrow3D(FancyArrowPatch):
    def __init__(self, xs, ys, zs, *args, **kwargs):
        FancyArrowPatch.__init__(self, (0,0), (0,0), *args, **kwargs)
        self._verts3d = xs, ys, zs

    # proj3d Matplotlib_2:P572
    def draw(self, renderer):
        xs3d, ys3d, zs3d = self._verts3d
        xs, ys, zs = proj3d.proj_transform(xs3d, ys3d, zs3d, renderer.M)
        self.set_positions((xs[0],ys[0]),(xs[1],ys[1]))
        FancyArrowPatch.draw(self, renderer)

#####################################################################
# create a figure
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

#####################################################################
# the coordinate of axis plane
x1 = np.array([[1, 0, -1],[1, 0, -1],[1, 0, -1]])
y1 = np.array([[1, 1, 1],[0, 0, 0],[-1, -1, -1]])
z1 = np.array([[0, 0, 0],[0, 0, 0],[0, 0, 0]])

# plot axis plane
ax.plot_surface(x1, y1, z1,  rstride=2, cstride=2, color='b', linewidth=0, alpha=0.5)

#####################################################################
# the coordinate of side plane
x2 = np.array([[1, 1, 1],[0.5, 0.5, 0.5],[0, 0 ,0]])
y2 = np.array([[-1, 0, 1],[-0.5, 0, 0.5],[0, 0, 0]])
z2 = np.array([[0, 0, 0],[np.sqrt(2)/2, np.sqrt(2)/2, np.sqrt(2)/2],[np.sqrt(2), np.sqrt(2), np.sqrt(2)]])

# surface four sides
ax.plot_surface(x2, y2, z2,  rstride=2, cstride=2, color='b', linewidth=0, alpha=0.5)

ax.plot_surface(y2, x2, z2,  rstride=2, cstride=2, color='b', linewidth=0, alpha=0.5)

ax.plot_surface(-x2, y2, z2,  rstride=2, cstride=2, color='b', linewidth=0, alpha=0.5)

ax.plot_surface(-x2, -y2, z2,  rstride=2, cstride=2, color='b', linewidth=0, alpha=0.5)

#####################################################################
x3 = np.array([[0, 1, 2],
                [0.5, 1, 1.5],
                [1, 1, 1]])
y3 = np.array([[0, 0, 0],
                [-0.5, -0.5, -0.5],
                [-1, -1, -1]])
z3 = np.array([[np.sqrt(2), np.sqrt(2), np.sqrt(2)],
                [np.sqrt(2)/2, np.sqrt(2)/2, np.sqrt(2)/2],
                [0, 0, 0]])

ax.plot_surface(x3, y3, z3,  rstride=2, cstride=2, color='r', linewidth=0, alpha=0.5)

ax.plot_surface(x3, -y3, z3,  rstride=2, cstride=2, color='r', linewidth=0, alpha=0.5)

x4 = np.array([[1, 1, 1],
                [1.5, 1.5, 1.5],
                [2, 2, 2]])
y4 = np.array([[-1, 0, 1],
                [-0.5, 0, 0.5],
                [0, 0, 0]])
z4 = np.array([[0, 0, 0],
                [np.sqrt(2)/2, np.sqrt(2)/2, np.sqrt(2)/2],
                [np.sqrt(2), np.sqrt(2), np.sqrt(2)]])

ax.plot_surface(x4, y4, z4,  rstride=2, cstride=2, color='r', linewidth=0, alpha=0.5)
####################################################################
# set axis off
ax.set_axis_off()

# zoom the axis
zoomCoefficient = 2
ax.set_xlim(-zoomCoefficient, zoomCoefficient, True, False)
ax.set_ylim(-zoomCoefficient, zoomCoefficient, True, False)
ax.set_zlim(-zoomCoefficient, zoomCoefficient, True, False)
####################################################################
# plot coordinate axis
coordinate = 3
# add line with arrow - Coordinate axis: axis X
arrow = Arrow3D([-coordinate,coordinate],[0,0],[0,0], mutation_scale=20, lw=1, arrowstyle="-|>", color="k", linestyle="solid")
ax.add_artist(arrow)
# add text Coordinate axis text: axis X
ax.text( coordinate,0,0, 'X', fontsize=14)

# add line with arrow - Coordinate axis: axis Y
arrow = Arrow3D([0,0],[-coordinate,coordinate],[0,0], mutation_scale=20, lw=1, arrowstyle="-|>", color="k", linestyle="solid")
ax.add_artist(arrow)
# add text Coordinate axis text: axis Y
ax.text(0, coordinate,0, 'Y', fontsize=14)

# add line with arrow - Coordinate axis: axis Z
arrow = Arrow3D([0,0],[0,0],[-coordinate,coordinate], mutation_scale=20, lw=1, arrowstyle="-|>", color="k", linestyle="solid")
ax.add_artist(arrow)
# add text Coordinate axis text: axis Z
ax.text(0,0,coordinate, 'Z', fontsize=14)

#####################################################################
# show the figure
plt.show()
