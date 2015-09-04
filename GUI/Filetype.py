class Filetype:

	def __init__(self):
		self.type = "NOT_SET"

	def indicate(self):
		assert(False), "File type not set!"

	def getTypeString(self):
		return self.typeName

class Binary(Filetype):
	def __init__(self, comm):
		self.typeName = "Binary"
		self.comm = comm

	def indicate(self):
		self.comm.send([0x08])


class CSV(Filetype):
	def __init__(self, comm):
		self.typeName = "CSV"
		self.comm = comm

	def indicate(self):
		self.comm.send([0x09])