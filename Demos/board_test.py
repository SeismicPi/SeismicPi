import seismicpi
import time
import datetime
import calendar
import sys

if len(sys.argv)<2:
	print "Usage: " + sys.argv[0] + " <port_name>"
	sys.exit(1)

sp = seismicpi.SeismicPi(sys.argv[1])

print "Board version:", sp.get_firmware_string()

print "Sensor 1 name:", sp.get_sensor_name(1)
print "Sensor 2 name:", sp.get_sensor_name(2)
print "Sensor 3 name:", sp.get_sensor_name(3)
print "Sensor 4 name:", sp.get_sensor_name(4)

print "Sample rate:", sp.get_sample_rate()

print "File type:", sp.get_file_format()

print "Sensor 1 enabled:", sp.is_sensor_enabled(1)
print "Sensor 2 enabled:", sp.is_sensor_enabled(2)
print "Sensor 3 enabled:", sp.is_sensor_enabled(3)
print "Sensor 4 enabled:", sp.is_sensor_enabled(4)

print "Accelerometer X enabled:", sp.is_sensor_enabled(5)
print "Accelerometer Y enabled:", sp.is_sensor_enabled(6)
print "Accelerometer Z enabled:", sp.is_sensor_enabled(7)

print "Channel gains:"
print "Sensor 1: ", str(sp.get_gain(1)) + "x"
print "Sensor 2: ", str(sp.get_gain(2)) + "x"
print "Sensor 3: ", str(sp.get_gain(3)) + "x"
print "Sensor 4: ", str(sp.get_gain(4)) + "x"

print "Current sensor values:"
vals = sp.get_sensor_values()
print "Sensor 1: ", vals[0]
print "Sensor 2: ", vals[1]
print "Sensor 3: ", vals[2]
print "Sensor 4: ", vals[3]

print "Scheduling enabled:", sp.is_scheduling_enabled()

tm = datetime.datetime.utcfromtimestamp(sp.get_scheduled_start())
print "Scheduling start:", tm.strftime("%Y-%m-%d %H:%M:%S")
tm = datetime.datetime.utcfromtimestamp(sp.get_scheduled_end())
print "Scheduling end:", tm.strftime("%Y-%m-%d %H:%M:%S")

tm = datetime.datetime.utcfromtimestamp(sp.get_rtc_time())
print "RTC time:", tm.strftime("%Y-%m-%d %H:%M:%S")

#sp.reset_processor()

#print "Setting scheduling..."
#sp.set_scheduled_start(calendar.timegm((2015, 7, 26, 10, 1, 0)))
#sp.set_scheduled_end(calendar.timegm((2015, 7, 26, 10, 1, 30)))
#sp.enable_scheduling()

#print "Connecting to card..."
#if sp.initialize_card():
#	print "Card ready"
#	
#	print "Switching to CSV Format..."
#	
#	print "Logging .csv for 2 second at 5SPS..."
#	sp.set_CSV()
#	sp.set_Binary()
#	sp.set_sample_rate(5)
#	sp.start_logging()
#	time.sleep(2)
#	sp.stop_logging()
#	print "Done!"
#	
#	print "Logging .bin for 4 seconds at 1000SPS..."
#	sp.set_Binary()
#	sp.set_sample_rate(1000)
#	sp.start_logging()
#	time.sleep(4)
#	sp.stop_logging()
#	print "Done!"
#else:
#	print "Card init failed!"