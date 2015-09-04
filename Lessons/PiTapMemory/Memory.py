import sys
from PyQt4 import QtCore, QtGui, uic
from collections import deque
from PyQt4.QtCore import *
from PyQt4.QtGui import *
import random
import time

form_class = uic.loadUiType("Memory.ui")[0]

class MyWidget(QtGui.QMainWindow, form_class):
	def __init__(self, parent = None):
		QtGui.QMainWindow.__init__(self, parent)
		self.setupUi(self)
		self.play_button.clicked.connect(self.play_handle)

	def play_handle(self, fodder = False, numButtons = 3, speed=3, itr=5):
		gen_Order = deque(maxlen = itr)
		for i in xrange(itr):
			nextIn = random.randint(1, numButtons)
			gen_Order.append(nextIn)
			self.button_one.setWindowOpacity(.5)
			#QTimer.singleShot(1000, self.button_one.setWindowOpacity(1))
			#time.sleep(1.0/speed)

		print " "
		gameOver = False


		def lose():
			print "You Lose"
		def win():
			print "You Win"

		def button_one_handle():
			if(1 != gen_Order.popleft()):
				lose()
				return 
			elif(not gen_Order):
				win()
				return
		def button_two_handle():
			if(2 != gen_Order.popleft()):
				lose()
				return 
			elif(not gen_Order):
				win()
				return
		def button_three_handle():
			if(3 != gen_Order.popleft()):
				lose()
				return 
			elif(not gen_Order):
				win()
				return

		self.button_one.clicked.connect(button_one_handle)
		self.button_two.clicked.connect(button_two_handle)
		self.button_three.clicked.connect(button_three_handle)

		return
		

app = QtGui.QApplication(sys.argv)
myWidget = MyWidget(None)
myWidget.show()
app.exec_()

