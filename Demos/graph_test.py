from SensDisLib import *
import time
import sys

if len(sys.argv)<2:
	print "Usage: " + sys.argv[0] + " <port name>"
	sys.exit(1)

def accel_to_g(val):
	return (val-32768)/16384.0

sd = SensorDisplay(sys.argv[1])

geophone_1 = SensorChannel(INPUT_CHANNEL_1, "Geophone 1")
sd.add(geophone_1)

accel_x = SensorChannel(ACCEL_X, "X-Acceleration")
sd.add(accel_x)

accel_y = SensorChannel(ACCEL_Y, "Y-Acceleration")
sd.add(accel_y)

accel_z = SensorChannel(ACCEL_Z, "Z-Acceleration")
accel_z.set_transform_function(accel_to_g)
accel_z.set_range(-2, 2)
sd.add(accel_z)

sd.runPlot()