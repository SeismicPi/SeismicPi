import threading
import seismicpi
import math
import time

class Accel:
	def __init__(self, portname):
		self.board = seismicpi.SeismicPi(portname)
		self.running = False
	
	def start(self, callback):
		self.running = True
		self.datathread = threading.Thread(target=self._datatask, args=(callback,))
		self.datathread.daemon = True
		self.datathread.start()
		
	def stop(self):
		self.running = False
		
	def _datatask(self, callback):
		tstart = time.time()
		tot = [0,0,0]
		cnt = 0
		while (time.time() - tstart) < 1:
			vals = self.board.get_accel_values()
			tot[0] += vals[0]
			tot[1] += vals[1]
			tot[2] += vals[2]
			cnt += 1
		calib = [tot[0]/float(cnt), tot[0]/float(cnt), tot[0]/float(cnt)]

		while self.running:
			tstart = time.time()
			tot = [0,0,0]
			cnt = 0
			while (time.time() - tstart) < 0.05:
				vals = self.board.get_accel_values()
				tot[0] += vals[0]
				tot[1] += vals[1]
				tot[2] += vals[2]
				cnt += 1
			accel = [tot[0]/float(cnt), tot[1]/float(cnt), tot[2]/float(cnt)]
			dx = accel[0] - calib[0]
			dy = accel[1] - calib[1]
			dz = accel[2] - calib[2]
			
			y2 = dy * dy
			z2 = dz * dz
			
			roll = math.atan2(dy, dz)
			pitch = math.atan2(-dx, math.sqrt(y2 + z2))
			
			callback(math.degrees(pitch), math.degrees(roll))