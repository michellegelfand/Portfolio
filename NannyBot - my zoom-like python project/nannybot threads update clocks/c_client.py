import time, datetime
import traceback
from typing import IO

import PySide6
import cv2
import numpy
import qdarktheme
from PySide6 import QtCore, QtWidgets, QtGui
from PySide6.QtCore import QThread, QTimer
from PySide6.QtGui import *
from cv2 import VideoWriter

from qdarktheme import *


import msg_pb2
from c_network import *  # to import their imports
from msg_pb2 import *

SERVER_MICHELLE_PC = (socket.gethostbyname(socket.gethostname()), 1234)

'''w in name indicates worker thread - this thread must not touch the gui,
and communicates with signals only'''


class wRecorder(QThread):
    recDur = 5
    pauseRecDur = 7
    logger: IO

    def __init__(self):
        super().__init__()

    def run(self) -> None:
        start = time.time()

        vidDate = datetime.datetime.now()
        vidDateStr = vidDate.__str__()
        vidStrSplit = vidDateStr.split('.')  # cut miliseconds that appear after '.' in the str
        title = vidStrSplit[0].__str__()
        title = title.replace(':', '-')  # filenames dont like ':'
        fourcc = cv2.VideoWriter_fourcc(
            *'X264')  # mp4 format. MP4V doesn't work. It has also succesfully created avi before
        out = cv2.VideoWriter(title + '.mp4', fourcc, 20.0, (640, 480))

        # color = (0, 255, 255)
        self.logger = open(title + ".txt", "a")  # 'x' means create new file, returns error if file exists
        # 'a' will create or open existing and append
        '''do not use w as it overwrites'''

        logTimeInterval = time.time() + self.recDur
        recording = True

        # if recording:
        out.write(self.frame)


class gui(PySide6.QtCore.QObject):  # not QThread, so this will run as main thread
    """signals must be defined only in classes inheriting from QObject!"""
    sig_NextFrame = PySide6.QtCore.Signal(QImage)
    app = PySide6.QtWidgets.QApplication()
    win = QtWidgets.QWidget()
    timeout = time.time() + 1000000000  # client will signal closer timeout

    def __init__(self,  sig: PySide6.QtCore.Signal(float), slot: PySide6.QtCore.Slot(float), launch: time.time):
        super().__init__()
        self.sig_newTimeout: PySide6.QtCore.Slot(float) = sig
        self.slot_newTimeout: PySide6.QtCore.Slot(float) = slot
        #self.sig_newTimeout.connect(self.slot_newTimeout)
        self.sig_newTimeout.connect(self.slot_receiveTimeout)
        self.launchTime = launch


    @QtCore.Slot(QImage)
    def slot_NextFrame(self, img):
        pass

    def ui(self):

        self.updateClocksTimer = QtCore.QTimer()
        self.updateClocksTimer.setInterval(1000)  # =1 sec

        #TEST - worker should do this, not here

        self.updateClocksTimer.timeout.connect(self.slot_updateClocks)
        self.updateClocksTimer.start()

        self.gLayout = PySide6.QtWidgets.QGridLayout(self.win)  # only layout that allows moving widgets to coordinates,
        # 'G' for grid
        self.win.setWindowTitle("Crystal Tracker")
        self.win.setLayout(self.gLayout)




        self.table = PySide6.QtWidgets.QTableWidget(10,4)
        self.table.horizontalHeader().hide()
        self.table.verticalHeader().hide()
        self.table.setVerticalScrollBarPolicy(PySide6.QtCore.Qt.ScrollBarPolicy.ScrollBarAlwaysOff)
        self.table.setHorizontalScrollBarPolicy(PySide6.QtCore.Qt.ScrollBarPolicy.ScrollBarAlwaysOff)


        '''I couldn't find a faster way to create and insert all the items'''
        i = 0
        j = 0

        while i < 10:
            while j < 4:

                self.table.setItem(i, j, QtWidgets.QTableWidgetItem('a'))
                self.table.item(i, j).setFlags(
                    PySide6.QtCore.Qt.ItemFlag.ItemIsEnabled)  # makes item read-only
                j += 1
            j = 0
            i += 1

        self.table.setAlternatingRowColors(True)

        self.recClock = PySide6.QtWidgets.QLCDNumber(4)
        self.progRunningClock = PySide6.QtWidgets.QLCDNumber(8)
        self.timeClock = PySide6.QtWidgets.QLCDNumber(8)
        self.progRunningClock.setFixedSize(100, 40)
        self.recClock.setFixedSize(100, 40)
        self.timeClock.setFixedSize(100, 40)
        self.hLayout = PySide6.QtWidgets.QHBoxLayout()
        self.hLayout.addWidget(self.timeClock)
        self.hLayout.addWidget(self.progRunningClock)
        self.hLayout.addWidget(self.recClock)
        self.hLayout.addStretch(1)  # cram clocks together

        self.gLayout.addWidget(self.table)
        self.gLayout.addLayout(self.hLayout,400,0)

        self.table.setFixedSize(400,300)
        self.table.adjustSize()
        self.win.adjustSize()


        self.table.show()
        self.win.show()




        self.app.exec()


    def slot_updateClocks(self):
        currentTime = QtCore.QTime.currentTime()
        currentTimeStr = currentTime.toString('hh:mm:ss')
        progRunningTimeStr = datetime.datetime.strftime(datetime.datetime.utcfromtimestamp(time.time() - self.launchTime), '%H:%M:%S')
        self.timeClock.display(currentTimeStr)
        self.recClock.display(numpy.ceil(self.timeout - time.time()))
        self.progRunningClock.display(progRunningTimeStr)



    def slot_receiveTimeout(self, timeout: time.time):
        self.timeout = timeout

class wStreamer(QThread):
    network: c_network

    def __init__(self, serverIp: str, serverPort: int):
        super().__init__()
        self.network = c_network(serverIp, serverPort)

    def run(self) -> None:

        msg = b''
        self.network.conn.setblocking(True)

        while self.isRunning:  # from parent
            try:
                msg = msg[921673:]
                msg += self.network.conn.recv(921673)

                decrypted = msg_pb2.vidMsg()
                decrypted.ParseFromString(msg)
                frame = numpy.frombuffer(decrypted.frame.frameBytes, dtype=numpy.uint8).reshape(decrypted.frame.frameShape)
                cv2.imshow('',frame)
                # im1 = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
                # height1, width1, channel1 = im1.shape
                # step1 = channel1 * width1
                # qimg1 = PySide6.QtGui.QImage(im1.data, width1, height1, step1, PySide6.QtGui.QImage.Format_RGB888)

                print(decrypted)
                cv2.waitKey(10)


            except Exception as exc:
                print(exc)


class c_client(QtCore.QObject):
    launchTime = time.time()
    timeout: float

    recDur = 4
    recPauseDur = 3
    timeout = time.time() + recDur
    isRecording = True
    recTimer = QTimer()
    sig_giveGuiNewTimeout = PySide6.QtCore.Signal(float)
    slot_newTimeout = PySide6.QtCore.Slot(float)  # gui will recieve new timeout using this slot


    def __init__(self):
        super(c_client, self).__init__()
        self.recTimer.setInterval(self.recDur*1000)
        self.recTimer.timeout.connect(self.wUpdateRecTimers)
        #self.sig_giveGuiNewTimeout.connect(self.slot_newTimeout)
        self.recTimer.start()

    def wUpdateRecTimers(self):
        if self.isRecording:
            self.timeout = time.time() + self.recPauseDur
            self.recTimer.setInterval(self.recPauseDur*1000)
            self.recTimer.start()
        else:
            self.timeout = time.time() + self.recDur
            self.recTimer.setInterval(self.recDur*1000)
            self.recTimer.start()

        self.isRecording = not self.isRecording  # flip boolean
        self.sig_giveGuiNewTimeout.emit(self.timeout)

    def run(self) -> None:
        self.recTimer.setInterval(self.recDur * 1000)  # *1000 cause in milisecs
        self.recTimer.timeout.connect(self.wUpdateRecTimers())
        self.recTimer.start()


if __name__ == '__main__':
    # streamer = wStreamer(*SERVER_MICHELLE_PC)
    # streamer.run()
    client = c_client()
    gui = gui(client.sig_giveGuiNewTimeout, client.slot_newTimeout, client.launchTime)
    runWorkers = QThread(client.run())
    runWorkers.start()
    gui.ui()






