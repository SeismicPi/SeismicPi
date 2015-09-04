import re

def fileToDic(configFile):
	
	def isAlphaNumUnder(s):
		return s.isalpha() or s == '_' or s.isdigit()

	keyValueDict = {}

	for line in configFile:
		if(line[0] == '#'):
			pass
		else:
			foundKey = False
			foundSeparator = False
			foundValue = False
			lineKey = ""
			lineValue = ""

			for currentChar in line:
				if(not foundKey):
					if(not isAlphaNumUnder(currentChar)):
						pass
					else:
						foundKey = True
						lineKey = lineKey + currentChar
				else:
					if(not foundSeparator):
						if(not isAlphaNumUnder(currentChar)):
							foundSeparator = True
						else:
							lineKey = lineKey + currentChar
					else:
						if(not foundValue):
							if(not isAlphaNumUnder(currentChar)):
								pass
							else:
								foundValue = True
								lineValue = lineValue + currentChar
						else:
							if(not currentChar == '\n' and not currentChar == '\r'):
								lineValue = lineValue + currentChar
			if(foundKey and foundSeparator and foundValue):
				keyValueDict[lineKey] = lineValue

	configFile.close()
	return keyValueDict


configFile = open('config.txt', 'r');





