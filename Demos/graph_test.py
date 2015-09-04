import SensDisLib
import time
import sys

if len(sys.argv)<2:
	print "Usage: " + sys.argv[0] + " <port name>"
	sys.exit(1)

def to16bit(x):
	return x >> 8
	
sd = SensDisLib.SensorDisplay(sys.argv[1])
sd.add_sensor_one("Geophone 1")
sd.add_sensor_two("S2")
sd.add_sensor_three("S3")
sd.add_sensor_four("S4")

#sd.setYRange_sensor_one(0, 65536)
#sd.setYRange_sensor_two(0, 65536)
#sd.setYRange_sensor_three(0, 65536)
#sd.setYRange_sensor_four(0, 65536)

sd.setYRange_sensor_one(-32768, 32768)
sd.setYRange_sensor_two(-32768, 32768)
sd.setYRange_sensor_three(-32768, 32768)
sd.setYRange_sensor_four(-32768, 32768)

sd.setVoltageFunction_sensor(1, to16bit)
sd.setVoltageFunction_sensor(2, to16bit)
sd.setVoltageFunction_sensor(3, to16bit)
sd.setVoltageFunction_sensor(4, to16bit)

sd.runPlot()