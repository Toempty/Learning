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
# define a function to draw a 3D plane
def PlaneDraw(p1, p2, p3, p4, rstriden = 2, cstriden = 2, colorn = 'b', linewidthn = 0, alphan = 0.5):
    x = np.array([[p1[0], (p1[0] + p2[0])*0.5, p2[0]],
                  [(p1[0] + p4[0])*0.5, (p1[0] + p4[0] + p2[0] + p3[0])*0.25, (p2[0] + p3[0])*0.5],
                  [p4[0], (p3[0] + p4[0])*0.5, p3[0]]])
    y = np.array([[p1[1], (p1[1] + p2[1])*0.5, p2[1]],
                  [(p1[1] + p4[1])*0.5, (p1[1] + p3[1] + p2[1] + p4[1])*0.25, (p2[1] + p3[1])*0.5],
                  [p4[1], (p3[1] + p4[1])*0.5, p3[1]]])
    z = np.array([[p1[2], (p1[2] + p2[2])*0.5, p2[2]],
                  [(p1[2] + p4[2])*0.5, (p1[2] + p3[2] + p2[2] + p4[2])*0.25, (p2[2] + p3[2])*0.5],
                  [p4[2], (p3[2] + p4[2])*0.5, p3[2]]])

    # plot axis plane
    ax.plot_surface(x, y, z,  rstride=rstriden, cstride=cstriden, color=colorn, linewidth=linewidthn, alpha=alphan)

#####################################################################
# create a figure
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

#####################################################################
sqrt2 = np.sqrt(2)
pointA = [1, 1, 0]
pointB = [-1, 1, 0]
pointC = [-1, -1, 0]
pointD = [1, -1, 0]
pointP = [0, 0, sqrt2]
pointE = [2, 0, sqrt2]
pointF = [(pointP[0] + pointD[0])*0.5,
          (pointP[1] + pointD[1])*0.5,
          (pointP[2] + pointD[2])*0.5]
#####################################################################
# the pyramid
PlaneDraw(pointD, pointA, pointB, pointC)

# the four side planes
PlaneDraw(pointD, pointA, pointP, pointP)
PlaneDraw(pointB, pointA, pointP, pointP)
PlaneDraw(pointB, pointC, pointP, pointP)
PlaneDraw(pointD, pointC, pointP, pointP)

#####################################################################
# the tetrahedron
PlaneDraw(pointP, pointE, pointD, pointD, colorn = 'w')
PlaneDraw(pointP, pointE, pointA, pointA, colorn = 'w')
PlaneDraw(pointD, pointA, pointE, pointE, colorn = 'w')

####################################################################
# set axis off
ax.set_axis_off()

# zoom the axis
zoomCoefficient = 1.5
ax.set_xlim(-zoomCoefficient, zoomCoefficient, True, False)
ax.set_ylim(-zoomCoefficient, zoomCoefficient, True, False)
ax.set_zlim(-zoomCoefficient, zoomCoefficient, True, False)
####################################################################
# plot coordinate axis
coordinate = 2.5
# add line with arrow - Coordinate axis: axis X
arrow = Arrow3D([-coordinate,coordinate],[0,0],[0,0], mutation_scale=20, lw=1, arrowstyle="-|>", color="k", linestyle="solid")
ax.add_artist(arrow)

# add line with arrow - Coordinate axis: axis Y
arrow = Arrow3D([0,0],[-coordinate,coordinate],[0,0], mutation_scale=20, lw=1, arrowstyle="-|>", color="k", linestyle="solid")
ax.add_artist(arrow)

# add line with arrow - Coordinate axis: axis Z
arrow = Arrow3D([0,0],[0,0],[-coordinate,coordinate], mutation_scale=20, lw=1, arrowstyle="-|>", color="k", linestyle="solid")
ax.add_artist(arrow)

# add line
arrow = Arrow3D([pointC[0], pointF[0]],
                [pointC[1], pointF[1]],
                [pointC[2], pointF[2]],
                mutation_scale=20, lw=2, arrowstyle="-", color="r", linestyle="solid")
ax.add_artist(arrow)

# add line
arrow = Arrow3D([pointE[0], pointF[0]],
                [pointE[1], pointF[1]],
                [pointE[2], pointF[2]],
                mutation_scale=20, lw=2, arrowstyle="-", color="r", linestyle="solid")
ax.add_artist(arrow)

# add line
arrow = Arrow3D([pointA[0], pointF[0]],
                [pointA[1], pointF[1]],
                [pointA[2], pointF[2]],
                mutation_scale=20, lw=2, arrowstyle="-", color="r", linestyle="solid")
ax.add_artist(arrow)
#####################################################################
# add text Coordinate axis text: axis X
ax.text( coordinate,0,0, 'X', fontsize=14)
# add text Coordinate axis text: axis Y
ax.text(0, coordinate,0, 'Y', fontsize=14)
# add text Coordinate axis text: axis Z
ax.text(0,0,coordinate, 'Z', fontsize=14)

# add text : pointA
ax.text(pointA[0]*1.1, pointA[1]*1.1, pointA[2]*1.1, 'A', fontsize=14)
# add text : pointB
ax.text(pointB[0]*1.1, pointB[1]*1.1, pointB[2]*1.1, 'B', fontsize=14)
# add text : pointC
ax.text(pointC[0]*1.1, pointC[1]*1.1, pointC[2]*1.1, 'C', fontsize=14)
# add text : pointD
ax.text(pointD[0]*1.1, pointD[1]*1.1, pointD[2]*1.1, 'D', fontsize=14)
# add text : pointP
ax.text(pointP[0]*1.1, pointP[1]*1.1, pointP[2]*1.1, 'P', fontsize=14)
# add text : pointE
ax.text(pointE[0]*1.1, pointE[1]*1.1, pointE[2]*1.1, 'E', fontsize=14)
# add text : pointF
ax.text(pointF[0]*1.1, pointF[1]*1.1, pointF[2]*1.1, 'F', fontsize=14)
#####################################################################
# show the figure
plt.show()
