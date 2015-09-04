import seismicpi
import sys
import datetime
import calendar

if len(sys.argv)<2:
	print "Usage: " + sys.argv[0] + " <port name>"
	sys.exit(1)

board = seismicpi.SeismicPi(sys.argv[1])

print
print "Current board time:", datetime.datetime.utcfromtimestamp(board.get_rtc_time())
print
print "Current computer time:", datetime.datetime.now()
print
print "Update board to computer time? (y/n)",

line = sys.stdin.readline()

if line.strip() == "y":
	print "Setting board time..."
	val = calendar.timegm(datetime.datetime.now().timetuple())
	board.set_rtc_time(val)
	print "Done!"
else:
	print "Aborting..."