import time, datetime
import traceback
from typing import IO

import PySide6
import cv2
import numpy
from PySide6.QtCore import QThread
from PySide6.QtGui import *
from cv2 import VideoWriter

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
                #frame = numpy.frombuffer(decrypted.frame.frameBytes, dtype=numpy.uint8).reshape(decrypted.frame.frameShape)

                #im1 = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
                #height1, width1, channel1 = im1.shape
                #step1 = channel1 * width1
                #qimg1 = PySide6.QtGui.QImage(im1.data, width1, height1, step1, PySide6.QtGui.QImage.Format_RGB888)

                print(decrypted)
                cv2.waitKey(10)


            except Exception as exc:
                print(exc)





class c_client(QThread):
    def __init__(self):
        super().__init__()

    def run(self) -> None:
        pass


if __name__ == '__main__':
    streamer = wStreamer(*SERVER_MICHELLE_PC)
    streamer.run()