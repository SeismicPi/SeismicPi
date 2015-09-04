import sys
from PyQt4.QtCore import *
from PyQt4.QtGui import *
import time


from collections import deque
import random
class Game(QWidget):
	def __init__(self, numButtons = 3, speed = 1, difficulty = 3):
		super(Game,self).__init__()
		self.numButtons = numButtons;
		self.speed = speed;
		self.difficulty = difficulty;

		self.buttonEnable = False

		self.score = 0
		self.level = [(4,3), (4,4), (4,5), (5,4), (5,5), (5,6), (6, 5), (6,6), (6,6), (7,6)]

		self.initUI()

	def initUI(self):
		self.buttons = []
		self.hbox = QHBoxLayout()

		for ind in xrange(self.numButtons):
			self.buttons.append(QPushButton(self))
			self.buttons[ind].setMinimumHeight(60);
			self.hbox.addWidget(self.buttons[ind])
			self.buttons[ind].clicked.connect(self.buttonClicked)

		self.resize(80000, 0)
		self.setLayout(self.hbox)
		self.setWindowTitle("Memory")
		self.show()
		self.activateWindow()

	def start(self):
		self.gen_Order = deque(maxlen = self.difficulty)
		self.difficulty_count = self.difficulty
		self.currentButton = None
		self.nextIn = None
		self.buttonEnable = False
		self.getNext()

	def getNext(self):
		if self.difficulty_count != self.difficulty:
			self.currentButton.setStyleSheet("")
		if self.difficulty_count == 0:
			self.buttonEnable = True
			return
		else:
			QSound.play("pop.wav")
			genIn = random.randint(1,self.numButtons)
			while genIn == self.nextIn:
					genIn = random.randint(1,self.numButtons)

			self.nextIn = genIn

			self.gen_Order.append(self.nextIn)
			self.currentButton = self.buttons[self.nextIn-1]

			self.currentButton.setStyleSheet("background: yellow")

			QTimer.singleShot(1000/self.speed, self.getNext)
			self.difficulty_count = self.difficulty_count-1


	def buttonClicked(self):
		if self.buttonEnable:
			sender = self.sender()
			value = self.buttons.index(sender)+1
			reply = None
			if(value != self.gen_Order.popleft()):
				self.buttonEnable = False
				QSound.play("wrong.wav")
				reply = QMessageBox.warning(self, 'Message', 
				"Sorry, that's incorrect! \nYour score was: " + str(self.score))
				self.close()

			else:
				QSound.play("correct.wav");

			if(not self.gen_Order):
				self.buttonEnable = True
				self.score = self.score + 1
				reply = QMessageBox.question(self, 'Message', 
				"Your score is: " + str(self.score) + "\n Continue?", QMessageBox.Yes | 
				QMessageBox.No, QMessageBox.Yes)



			if reply == QMessageBox.Yes:
				(self.speed, self.difficulty) = self.level[self.score%10]

				if self.score % 10 == 0:
					self.buttons.append(QPushButton(self))
					self.buttons[self.numButtons].clicked.connect(self.buttonClicked)
					self.buttons[numButtons].setMinimumHeight(60);
					self.hbox.addWidget(self.buttons[self.numButtons])
					self.numButtons = self.numButtons + 1
					
					QTimer.singleShot(500, self.start)
				else:
					self.start()

	def keyPressEvent(self, e):
		if e.key() == Qt.Key_Space:
			self.start()

def main():
	app = QApplication(sys.argv)
	game = Game(3,3,3)
	sys.exit(app.exec_())

if __name__ == '__main__':
	main()