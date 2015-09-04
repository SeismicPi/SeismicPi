import SensDisLib as s
import time
from collections import deque

sensor = s.SensorDisplay()

#We want to see a total of 17 peaks, for 16 time differences


buff16 = deque(maxlen = 16)
currentSum = 0.0

def addValue(i):
	global currentSum
	global buff16

	if(len(buff16) == 16):
		currentSum -= buff16[0]

	buff16.append(i)
	currentSum += i;
	return currentSum/len(buff16)


	
sensor.add_sensor_one("Heartbeat")
sensor.setVoltageFunction_sensor(1, addValue)
sensor.setYRange_sensor_one(1800, 2200)
sensor.runPlot()

numPeaks = 0
lastTime = 0
maxIteration = 8
threshold = 2040
timeDifferences = []

lastVoltage = 0
thisVoltage = 0
while(numPeaks < maxIteration):
	time.sleep(.05)
	lastVoltage = thisVoltage
	thisVoltage = sensor.get_sensor(1);
	if(lastVoltage < threshold and thisVoltage > threshold):
		print numPeaks
		if(numPeaks > 0):
			timeDifferences.append(time.time() - lastTime)
			lastTime = time.time()
			numPeaks+=1
		else:
			lastTime = time.time()
			numPeaks+=1

totalSum = 0.0
for i in timeDifferences:
	totalSum += i

totalSum = totalSum/len(timeDifferences)
print timeDifferences
print totalSum;

