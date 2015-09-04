from PyQt4 import QtGui, QtCore

class Ventana(QtGui.QWidget):
    def __init__(self, parent=None):
        QtGui.QWidget.__init__(self, parent)
        self.setLayout(QtGui.QVBoxLayout())
        self.lineEdit = QtGui.QLineEdit(self)
        self.button = QtGui.QPushButton('clickme', self)
        self.layout().addWidget(self.lineEdit)
        self.layout().addWidget(self.button)
        self.button.clicked.connect(self.testSleep)

    def testSleep(self):
        self.lineEdit.setText('Start')
        QtCore.QTimer.singleShot(2000, lambda: self.lineEdit.setText('End'))

    def mainLoop(self, app ):
        sys.exit( app.exec_())

if __name__ == '__main__':
    import sys
    app = QtGui.QApplication(sys.argv)
    window = Ventana()
    window.show()
    sys.exit(app.exec_())