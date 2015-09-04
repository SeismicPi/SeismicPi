class Sensor:

	def __init__(self):
		#Default Settings

		self.name = "Sensor"
		self.toLog = False
		self.sampleRate = 100

		self.displayFunction = lambda x: x

	def start_logging(self):
		self.toLog = True

	def stop_logging(self):
		self.toLog = False

	def set_name(self, newName):
		assert(isinstance(newName, str)), "The name must be a String!"
		self.name = newName

	def setVoltageFunction(self, newFunc):
		self.displayFunction = lambda x: newFunc(x)

	def get_raw(self):
		byteArray = self.spi.xfer([0x01])
		byteArray = self.spi.xfer([0xff]*8)
		return (byteArray[2*index] << 8) + byteArray[2*index+1]

	def get_cook(self):
		return self.displayFunction(this.get_raw())

