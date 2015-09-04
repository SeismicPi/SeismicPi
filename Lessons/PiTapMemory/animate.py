#!/usr/bin/env python
#-*- coding:utf-8 -*-

from PyQt4 import QtCore, QtGui

class StateSwitchEvent(QtCore.QEvent):
    StateSwitchType = QtCore.QEvent.User + 256

    def __init__(self, rand=0):
        super(StateSwitchEvent, self).__init__(StateSwitchEvent.StateSwitchType)

        self.m_rand = rand

    def rand(self):
        return self.m_rand

class StateSwitchTransition(QtCore.QAbstractTransition):
    def __init__(self, rand):
        super(StateSwitchTransition, self).__init__()

        self.m_rand = rand

    def eventTest(self, event):
        return (event.type() == StateSwitchEvent.StateSwitchType and
                event.rand() == self.m_rand)

    def onTransition(self, event):
        pass


class StateSwitcher(QtCore.QState):
    def __init__(self, machine):
        super(StateSwitcher, self).__init__(machine)

        self.m_stateCount = 0
        self.m_lastIndex = 1

    def onEntry(self, event):
        self.m_lastIndex = 1 if self.m_lastIndex >= self.m_stateCount else self.m_lastIndex + 1
        self.machine().postEvent(StateSwitchEvent(self.m_lastIndex))

    def addState(self, state, animation):
        self.m_stateCount += 1

        trans = StateSwitchTransition(self.m_stateCount)
        trans.setTargetState(state)
        trans.addAnimation(animation)

        self.addTransition(trans)


def createGeometryState(w1, rect1, w2, rect2, w3, rect3, w4, rect4, w5, rect5, w6, rect6, parent):
    result = QtCore.QState(parent)

    result.assignProperty(w1, 'geometry', rect1)
    result.assignProperty(w1, 'geometry', rect1)
    result.assignProperty(w2, 'geometry', rect2)
    result.assignProperty(w3, 'geometry', rect3)
    result.assignProperty(w4, 'geometry', rect4)
    result.assignProperty(w5, 'geometry', rect5)
    result.assignProperty(w6, 'geometry', rect6)

    return result

@QtCore.pyqtSlot()
def on_pushButtonStart_clicked():
    lastItem = None
    lowestY  = None
    for item in scene.items():
        itemY = item.pos().y()
        if lastItem == None or itemY <= lowestY:
            lowestY = itemY
            lastItem = item

    for item in scene.items():
        if item != lastItem:
            lastItem.stackBefore(item)

    timer.start()

if __name__ == '__main__':
    import sys

    app = QtGui.QApplication(sys.argv)

    button1 = QtGui.QPushButton()
    button1.setFixedSize(QtCore.QSize(50, 50))
    button1.setText("#1")

    button2 = QtGui.QPushButton()
    button2.setFixedSize(QtCore.QSize(50, 50))
    button2.setText("#2")

    button3 = QtGui.QPushButton()
    button3.setFixedSize(QtCore.QSize(50, 50))
    button3.setText("#3")

    button4 = QtGui.QPushButton()
    button4.setFixedSize(QtCore.QSize(50, 50))
    button4.setText("#4")

    button5 = QtGui.QPushButton()
    button5.setFixedSize(QtCore.QSize(50, 50))
    button5.setText("#5")

    button6 = QtGui.QPushButton()
    button6.setFixedSize(QtCore.QSize(50, 50))
    button6.setText("#6")

    scene = QtGui.QGraphicsScene(0, 0, 50, 300)
    scene.addWidget(button1)
    scene.addWidget(button2)
    scene.addWidget(button3)
    scene.addWidget(button4)
    scene.addWidget(button5)
    scene.addWidget(button6)

    timer = QtCore.QTimer()
    timer.setInterval(0)
    timer.setSingleShot(True)

    group = QtCore.QState()

    state1 = createGeometryState(
        button1, QtCore.QRect(0, 0, 50, 50),
        button2, QtCore.QRect(0, 50, 50, 50),
        button3, QtCore.QRect(0, 100, 50, 50),
        button4, QtCore.QRect(0, 150, 50, 50), 
        button5, QtCore.QRect(0, 200, 50, 50), 
        button6, QtCore.QRect(0, 250, 50, 50), 
        group
        )

    state2 = createGeometryState(
        button2, QtCore.QRect(0, 0, 50, 50),
        button3, QtCore.QRect(0, 50, 50, 50),
        button4, QtCore.QRect(0, 100, 50, 50),
        button5, QtCore.QRect(0, 150, 50, 50),
        button6, QtCore.QRect(0, 200, 50, 50), 
        button1, QtCore.QRect(0, 250, 50, 50),
        group
        )

    state3 = createGeometryState(
        button3, QtCore.QRect(0, 0, 50, 50),
        button4, QtCore.QRect(0, 50, 50, 50),
        button5, QtCore.QRect(0, 100, 50, 50),
        button6, QtCore.QRect(0, 150, 50, 50), 
        button1, QtCore.QRect(0, 200, 50, 50),
        button2, QtCore.QRect(0, 250, 50, 50),
        group
    )

    state4 = createGeometryState(
        button4, QtCore.QRect(0, 0, 50, 50),
        button5, QtCore.QRect(0, 50, 50, 50),
        button6, QtCore.QRect(0, 100, 50, 50), 
        button1, QtCore.QRect(0, 150, 50, 50),
        button2, QtCore.QRect(0, 200, 50, 50),
        button3, QtCore.QRect(0, 250, 50, 50),
        group
    )

    state5 = createGeometryState(
        button5, QtCore.QRect(0, 0, 50, 50),
        button6, QtCore.QRect(0, 50, 50, 50), 
        button1, QtCore.QRect(0, 100, 50, 50),
        button2, QtCore.QRect(0, 150, 50, 50),
        button3, QtCore.QRect(0, 200, 50, 50),
        button4, QtCore.QRect(0, 250, 50, 50),
        group
    )

    state6 = createGeometryState(
        button6, QtCore.QRect(0, 0, 50, 50),
        button1, QtCore.QRect(0, 50, 50, 50), 
        button2, QtCore.QRect(0, 100, 50, 50),
        button3, QtCore.QRect(0, 150, 50, 50),
        button4, QtCore.QRect(0, 200, 50, 50),
        button5, QtCore.QRect(0, 250, 50, 50),
        group
    )

    animationGroup = QtCore.QParallelAnimationGroup()

    anim = QtCore.QPropertyAnimation(button6, 'geometry')
    anim.setDuration(1111)
    anim.setEasingCurve(QtCore.QEasingCurve.OutElastic)
    animationGroup.addAnimation(anim)

    anim = QtCore.QPropertyAnimation(button5, 'geometry')
    anim.setDuration(1111)
    anim.setEasingCurve(QtCore.QEasingCurve.OutElastic)
    animationGroup.addAnimation(anim)

    anim = QtCore.QPropertyAnimation(button4, 'geometry')
    anim.setDuration(1111)
    anim.setEasingCurve(QtCore.QEasingCurve.OutElastic)
    animationGroup.addAnimation(anim)

    anim = QtCore.QPropertyAnimation(button3, 'geometry')
    anim.setDuration(1111)
    anim.setEasingCurve(QtCore.QEasingCurve.OutElastic)
    animationGroup.addAnimation(anim)

    anim = QtCore.QPropertyAnimation(button2, 'geometry')
    anim.setDuration(1111)
    anim.setEasingCurve(QtCore.QEasingCurve.OutElastic)
    animationGroup.addAnimation(anim)

    anim = QtCore.QPropertyAnimation(button1, 'geometry')
    anim.setDuration(1111)
    anim.setEasingCurve(QtCore.QEasingCurve.OutElastic)
    animationGroup.addAnimation(anim)

    machine = QtCore.QStateMachine()

    stateSwitcher = StateSwitcher(machine)
    stateSwitcher.addState(state1, animationGroup)
    stateSwitcher.addState(state2, animationGroup)
    stateSwitcher.addState(state3, animationGroup)
    stateSwitcher.addState(state4, animationGroup)
    stateSwitcher.addState(state5, animationGroup)
    stateSwitcher.addState(state6, animationGroup)

    group.addTransition(timer.timeout, stateSwitcher)
    group.setInitialState(state1)

    machine.addState(group)
    machine.setInitialState(group)
    machine.start()

    view = QtGui.QGraphicsView(scene)
    view.setAlignment(QtCore.Qt.AlignLeft | QtCore.Qt.AlignTop)
    view.setHorizontalScrollBarPolicy(QtCore.Qt.ScrollBarAlwaysOff)
    view.setVerticalScrollBarPolicy(QtCore.Qt.ScrollBarAlwaysOff)
    view.setFixedSize(50, 150)

    window = QtGui.QWidget()

    pushButtonStart = QtGui.QPushButton(window)
    pushButtonStart.setText("Start")
    pushButtonStart.clicked.connect(on_pushButtonStart_clicked)    

    layoutVertical = QtGui.QVBoxLayout(window)
    layoutVertical.addWidget(view)
    layoutVertical.addWidget(pushButtonStart)

    window.show()
    window.resize(333, 150)

    sys.exit(app.exec_())