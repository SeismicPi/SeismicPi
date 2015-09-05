from __future__ import print_function
import sys

def int32(b):
	return (b[0]<<24) + (b[1]<<16) + (b[2]<<8) + b[3]

def int24(b):
	return (b[0]<<16) + (b[1]<<8) + b[2]
	
def int16(b):
	return (b[0]<<8) + b[1]

def charstr(b):
	s = ""
	for c in b:
		if c==0: break
		s += chr(c)
	return s
	
def pr(str):
	print(str, end="")
	
if len(sys.argv)<2:
	print("Usage " + sys.argv[0] + " <input file>")
	sys.exit(1)

with open(sys.argv[1], "rb") as f:
	sens_enabled = ord(f.read(1))
	num_24_enabled = 0
	num_16_enabled = 0
	for i in range(7):
		if (sens_enabled & (1<<i))>0:
			if i<4:
				num_24_enabled += 1
			else:
				num_16_enabled += 1
	sens_names = []
	for i in range(num_24_enabled + num_16_enabled):
		sens_names.append(charstr(map(ord, f.read(20))))
	pr("Time")
	lasttime = time = 0
	for name in sens_names:
		pr("," + name)
	print()
	while True:
		lasttime = time
		b = map(ord,f.read(4 + ((num_24_enabled*3) + (num_16_enabled*2))))
		if len(b)<(4 + ((num_24_enabled*3) + (num_16_enabled*2))): break
		time = int32(b[:4])
		pr(time)
		for i in range(num_24_enabled):
			pr("," + str(int24(b[(i*3) + 4:(i*3)+7])))
		for i in range(0, num_16_enabled):
			pr("," + str(int16(b[(i*2) + 4 + (num_24_enabled*3) : (i*2) + 6 + (num_24_enabled*3)])))
		print()