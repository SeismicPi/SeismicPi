import sys, os

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
	
if len(sys.argv)<3:
	print("Usage " + sys.argv[0] + " <input file> <output file>")
	sys.exit(1)

inputsize = os.path.getsize(sys.argv[1])
	
with open(sys.argv[1], "rb") as i:
	with open(sys.argv[2], "w") as o:
		
		sens_enabled = ord(i.read(1))
		num_24_enabled = 0
		num_16_enabled = 0
		
		for x in range(7):
			if (sens_enabled & (1<<x))>0:
				if x<4:
					num_24_enabled += 1
				else:
					num_16_enabled += 1
		
		sens_names = []
		
		for x in range(num_24_enabled + num_16_enabled):
			sens_names.append(charstr(bytearray(i.read(20))))
		
		o.write("Time")
		for name in sens_names:
			o.write(",\"" + name + "\"")
		o.write("\n")
		
		recordsize = 4 + ((num_24_enabled*3) + (num_16_enabled*2))
		numrecords = (inputsize - i.tell()) / recordsize
		numread = 0
		time = 0
		while True:
			b = bytearray(i.read(recordsize))
			if len(b) < recordsize: break
			time = int32(b[:4])
			o.write(str(time))
			for x in range(num_24_enabled):
				o.write("," + str(int24(b[(x*3) + 4:(x*3)+7])))
			for x in range(0, num_16_enabled):
				o.write("," + str(int16(b[(x*2) + 4 + (num_24_enabled*3) : (x*2) + 6 + (num_24_enabled*3)])))
			o.write("\n")
			numread += 1
			if numread % 1000 == 0:
				print("Read %s of %s records [%.2f%%]" % (numread, numrecords, ((numread*100.0) / numrecords)))
		
		print("Done!")
