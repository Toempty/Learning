from matplotlib.patches import Ellipse, Circle
import matplotlib.pyplot as plt

###########################################################
# define a function to draw a quadrangle
def drawQuadrangle(p1, p2, p3, p4, cl = 'b', lw = 1, ls = '-'):
    plt.plot([p1[0], p2[0]], [p1[1], p2[1]], color = cl, linewidth = lw, linestyle = ls)
    plt.plot([p2[0], p3[0]], [p2[1], p3[1]], color = cl, linewidth = lw, linestyle = ls)
    plt.plot([p3[0], p4[0]], [p3[1], p4[1]], color = cl, linewidth = lw, linestyle = ls)
    plt.plot([p4[0], p1[0]], [p4[1], p1[1]], color = cl, linewidth = lw, linestyle = ls)


###########################################################
fig = plt.figure()
ax = fig.add_subplot(111)

###########################################################
# plot quadrangle
squareSize = 2;
p1 = [-squareSize, 0]
p2 = [0, squareSize]
p3 = [squareSize, 0]
p4 = [0, -squareSize]

drawQuadrangle(p1, p2, p3, p4, cl = 'b', lw = 2, ls = '-')

###########################################################
# plot other lines
plt.plot([p1[0], -3*squareSize], [p1[1], 2*squareSize], color = 'r', linewidth = 2, linestyle = '-.')
plt.plot([p1[0], -3*squareSize], [p1[1], -2*squareSize], color = 'r', linewidth = 2, linestyle = '-.')

plt.plot([p2[0], 2*squareSize], [p2[1], 3*squareSize], color = 'r', linewidth = 2, linestyle = '-.')
plt.plot([p2[0], -2*squareSize], [p2[1], 3*squareSize], color = 'r', linewidth = 2, linestyle = '-.')

plt.plot([p3[0], 3*squareSize], [p3[1], 2*squareSize], color = 'r', linewidth = 2, linestyle = '-.')
plt.plot([p3[0], 3*squareSize], [p3[1], -2*squareSize], color = 'r', linewidth = 2, linestyle = '-.')

plt.plot([p4[0], 2*squareSize], [p4[1], -3*squareSize], color = 'r', linewidth = 2, linestyle = '-.')
plt.plot([p4[0], -2*squareSize], [p4[1], -3*squareSize], color = 'r', linewidth = 2, linestyle = '-.')

###########################################################
# plot circle
x, y = 2*squareSize, 2*squareSize # center
cir1 = Circle(xy = (x, y), radius = squareSize / 2, alpha = 0.5, color = 'green')
ax.add_patch(cir1)
ax.plot(x, y, 'ro') # plot center

x, y = -2*squareSize, 2*squareSize # center
cir1 = Circle(xy = (x, y), radius = squareSize / 2, alpha = 0.5, color = 'green')
ax.add_patch(cir1)
ax.plot(x, y, 'ro') # plot center

x, y = 2*squareSize, -2*squareSize # center
cir1 = Circle(xy = (x, y), radius = squareSize / 2, alpha = 0.5, color = 'green')
ax.add_patch(cir1)
ax.plot(x, y, 'ro') # plot center

x, y = -2*squareSize, -2*squareSize # center
cir1 = Circle(xy = (x, y), radius = squareSize / 2, alpha = 0.5, color = 'green')
ax.add_patch(cir1)
ax.plot(x, y, 'ro') # plot center

###########################################################
# set axis
axisSize = 8;
plt.axis('equal')
plt.xlim(-axisSize, axisSize)

plt.axis('equal')
plt.ylim(-axisSize, axisSize)

# set x, y free in side
ax.spines['right'].set_color('none')
ax.spines['top'].set_color('none')

# set x in center
ax.xaxis.set_ticks_position('bottom')
ax.spines['bottom'].set_position(('data',0))

#set y in center
ax.yaxis.set_ticks_position('left')
ax.spines['left'].set_position(('data',0))

# set ticklabel
ax.set_yticklabels([''])
ax.set_xticklabels([''])

###########################################################
plt.show()
