import sys
from PyQt4 import QtCore, QtGui


class Widget(QtGui.QWidget):

    def __init__(self):
        super(Widget, self).__init__()

        self.resize(300,200)
        layout = QtGui.QVBoxLayout(self)

        self.label = QtGui.QLabel("Some sample text")
        font = self.label.font()
        font.setPointSize(20)
        self.label.setFont(font)
        layout.addWidget(self.label)

        self.button = QtGui.QPushButton("Start", self)
        layout.addWidget(self.button)

        self.animation = anim = QtCore.QPropertyAnimation(self, "color", self)
        anim.setDuration(250)
        anim.setLoopCount(2)
        anim.setStartValue(self.color)
        anim.setEndValue(self.color)
        anim.setKeyValueAt(0.5, QtGui.QColor(0,255,0))

        self.button.clicked.connect(anim.start)

    def getColor(self):
        return self.label.palette().text()

    def setColor(self, color):
        palette = self.label.palette()
        palette.setColor(self.label.foregroundRole(), color)
        self.label.setPalette(palette)

    color = QtCore.Property(QtGui.QColor, getColor, setColor)


if __name__ == "__main__":
    app = QtGui.QApplication([])
    w = Widget()
    w.show()
    app.exec_()