from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

from matplotlib.patches import FancyArrowPatch
from mpl_toolkits.mplot3d import proj3d

# define a 3D arrow
class Arrow3D(FancyArrowPatch):
    def __init__(self, xs, ys, zs, *args, **kwargs):
        FancyArrowPatch.__init__(self, (0,0), (0,0), *args, **kwargs)
        self._verts3d = xs, ys, zs

    def draw(self, renderer):
        xs3d, ys3d, zs3d = self._verts3d
        xs, ys, zs = proj3d.proj_transform(xs3d, ys3d, zs3d, renderer.M)
        self.set_positions((xs[0],ys[0]),(xs[1],ys[1]))
        FancyArrowPatch.draw(self, renderer)

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
normal = np.array([0,0,1])

# the coordinate of axis plane
xx = np.array([[ 1, 0 ,-1],
               [ 1, 0 ,-1],
               [ 1, 0 ,-1]])
xy = np.array([[ 1, 1, 1],
               [ 0, 0, 0],
               [-1, -1, -1]])
zero = np.array([[0, 0, 0],
                 [0, 0, 0],
                 [0, 0, 0]])

ax.set_axis_off()

# plot axis plane
ax.plot_surface(xx, xy, zero,  rstride=2, cstride=2, color='b', linewidth=0, alpha=0.3)
ax.plot_surface(xx, zero, xy,  rstride=2, cstride=2, color='b', linewidth=0, alpha=0.3)
ax.plot_surface(zero, xx, xy,  rstride=2, cstride=2, color='b', linewidth=0, alpha=0.3)

# add arrow
arrow = Arrow3D([0,0],[0,0],[-1,1], mutation_scale=20, lw=1,
        arrowstyle="<|-|>", color="k", linestyle="solid")
ax.add_artist(arrow)
# add text
ax.text(0,0,1.1, '3', fontsize=14)
ax.text(0,0,-1.1, '4', fontsize=14)

arrow = Arrow3D([0,0],[-1,1],[0,0], mutation_scale=20, lw=1,
        arrowstyle="<|-|>", color="k", linestyle="solid")
ax.add_artist(arrow)
ax.text(0, 1.1,0, '6', fontsize=14)
ax.text(0,-1.1,0, '5', fontsize=14)

arrow = Arrow3D([-1,1],[0,0],[0,0], mutation_scale=20, lw=1,
        arrowstyle="<|-|>", color="k", linestyle="solid")
ax.add_artist(arrow)
ax.text( 1.1,0,0, '1', fontsize=14)
ax.text(-1.1,0,0, '2', fontsize=14)

arrow = Arrow3D([1,-1],[0,0],[1,-1], mutation_scale=20, lw=1,
        arrowstyle="<|-|>", color='w', linestyle="dashed")
ax.add_artist(arrow)
ax.text( 1.1,0, 1.1, '10', fontsize=14)
ax.text(-1.1,0,-1.1, '9', fontsize=14)

arrow = Arrow3D([1,-1],[0,0],[-1,1], mutation_scale=20, lw=1,
        arrowstyle="<|-|>", color='w', linestyle="dashed")
ax.add_artist(arrow)
ax.text(-1.1,0, 1.1, '14', fontsize=14)
ax.text( 1.1,0,-1.1, '13', fontsize=14)

plt.show()
