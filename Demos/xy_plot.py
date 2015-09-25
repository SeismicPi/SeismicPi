from pyqtgraph.Qt import QtGui, QtCore
import pyqtgraph as pg
from collections import deque
import threading
import time
import seismicpi
import sys

if len(sys.argv)<2:
	print "Usage: " + sys.argv[0] + " <port_name> [<persistence (samples), default=800>]"
	sys.exit(1)

if len(sys.argv)>=3:
	maxlen = int(sys.argv[2])
else:
	maxlen = 800

def accel_to_g(val):
	return (val-32768)/16384.0

board = seismicpi.SeismicPi(sys.argv[1])

xdata = deque(maxlen=maxlen)
ydata = deque(maxlen=maxlen)

app = QtGui.QApplication([])
win = pg.GraphicsWindow(title = "Sensor Plots")
win.resize(1000, 800)

pg.setConfigOptions(antialias = False)

plot = win.addPlot()
plot.setYRange(-0.4,0.4)
plot.setXRange(-0.4,0.4)
curve = plot.plot(pen='r')

def getNext():
	global xdata, ydata
	while True:
		time.sleep(.0001)
		vals = board.get_accel_values()
		xdata.append(accel_to_g(vals[0]))
		ydata.append(accel_to_g(vals[1]))

def update():
	curve.setData(xdata, ydata)

input_Thread = threading.Thread(target = getNext)
input_Thread.daemon = True
input_Thread.start()

timer = QtCore.QTimer()
timer.timeout.connect(update)
timer.start()

if (sys.flags.interactive != 1) or not hasattr(QtCore, 'PYQT_VERSION'):
	QtGui.QApplication.instance().exec_()