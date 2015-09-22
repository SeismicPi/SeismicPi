from pyqtgraph.Qt import QtGui, QtCore
import pyqtgraph as pg
from collections import deque
import threading
import time
import seismicpi


INPUT_CHANNEL_1 = 1
INPUT_CHANNEL_2 = 2
INPUT_CHANNEL_3 = 3
INPUT_CHANNEL_4 = 4
ACCEL_X = 5
ACCEL_Y = 6
ACCEL_Z = 7

SENSOR_DATA_BUFFER_LENGTH = 2000

class SensorChannel:
	def __init__(self, source, name=None):
		assert source >=1 and source <= 7, "Sensor source is invalid!"
		self.source = source
		self.name = name or "Channel %d" % (source)
		self.data = deque(maxlen=SENSOR_DATA_BUFFER_LENGTH)
		self.transform_function = lambda x: x
		self.plot = None
		if source >= ACCEL_X:
			self.set_range(0, 65536) # 16-bit accelerometer (unsigned)
		else:
			self.set_range(-8388608, 8388608) # 24-bit signed sensor input
	
	def _update_value(self, newVal):
		self.raw_value = newVal
		self.data.append(self.transform_function(newVal))
		
	def set_range(self, min_y, max_y):
		self.min_y = min_y
		self.max_y = max_y
		if self.plot:
			self.plot.setYRange(min_y, max_y)
	
	def set_transform_function(self, func):
		self.transform_function = lambda x: func(x)
	
	def set_name(self, name):
		self.name = name
		
	def get_raw_value(self):
		return self.raw_value
	
	def get_value(self):
		return self.transform_function(self.raw_value)


class SensorDisplay:
	
	def __init__(self, comport, displayTime = 2):
		global SENSOR_DATA_BUFFER_LENGTH
		#input is the maxDisplayTime in seconds
		self.numSensors = 0

		self.board = seismicpi.SeismicPi(comport)

		SENSOR_DATA_BUFFER_LENGTH = displayTime * 1000
		self.qx = deque(maxlen=SENSOR_DATA_BUFFER_LENGTH)

		self.app = QtGui.QApplication([])
		self.win = pg.GraphicsWindow(title = "Sensor Plots")
		self.win.resize(1000, 800)
		
		self.renderLock = False
		
		self.read_sensors = False
		self.read_accel = False
		
		self.pen_colors = ['r', 'g', 'b', 'y']
		
		self.sensors = []
		
		self.paused = False

		pg.setConfigOptions(antialias = False)

	def pause(self):
		self.paused = True
	
	def resume(self):
		self.paused = False
	
	def add(self, sensor):
		assert sensor, "Sensor is None!"
		if self.numSensors == 2:
			self.win.nextRow()
		
		plot = self.win.addPlot(title = sensor.name)
		plot.setYRange(sensor.min_y, sensor.max_y)
		self.sensors.append(sensor)
		sensor.plot = plot
		sensor.curve = plot.plot(pen=self.pen_colors[self.numSensors])
		if sensor.source >= ACCEL_X:
			self.read_accel = True
		else:
			self.read_sensors = True
		
		self.numSensors += 1
	
	def update(self):
		for sensor in self.sensors:
			if not self.renderLock:
				sensor.curve.setData(self.qx, sensor.data)

	def getNext(self):
		ptr = 0
		while True:
			time.sleep(.0001)
			if not self.paused:
				if self.read_sensors:
					self.sensor_values = self.board.get_sensor_values()
				if self.read_accel:
					self.accel_values = self.board.get_accel_values()
				self.renderLock = True
				for sensor in self.sensors:
					if sensor.source >= ACCEL_X:
						val = self.accel_values[sensor.source - ACCEL_X]
					else:
						val = self.sensor_values[sensor.source - INPUT_CHANNEL_1]
					sensor._update_value(val)
				self.qx.append(ptr)
				self.renderLock = False
				ptr+=1

	def runPlot(self):
		self.input_Thread = threading.Thread(target = self.getNext)
		self.input_Thread.daemon = True
		self.input_Thread.start()

		self.timer = QtCore.QTimer()
		self.timer.timeout.connect(self.update)
		self.timer.start()

		import sys
		if (sys.flags.interactive != 1) or not hasattr(QtCore, 'PYQT_VERSION'):
			QtGui.QApplication.instance().exec_()