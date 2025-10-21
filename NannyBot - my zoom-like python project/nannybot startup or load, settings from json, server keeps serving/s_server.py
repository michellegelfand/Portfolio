import glob
import random
import runpy
import sys
import threading
import traceback

import PySide6.QtCore
import cv2
import time  # sleep func for testing
from PySide6 import QtWidgets, QtGui, QtCore  # for gui later

import msg_pb2

from s_network import *  # this imports their imports as well





'''to download pip-install if you'll ever need it
you need to download a file called pip.py and run it
then run pip3.10.exe (or whatever) install packagename'''

from cv2 import *  # imported from package open-cv. this is for image/video stuff
from imutils2 import *  # more image stuff

SERVER_MICHELLE_PC = (socket.gethostbyname(socket.gethostname()), 1234)


class Test(QtCore.QThread):
    testData = [int(), int(), int(), int(), str(), str(), str(), str()]

    def __init__(self):
        super().__init__()
        '''connect started signal to the slot, so it's activated in new thread when main
        thread tells this thread to start'''

    def run(self) -> None:  # this method is inherited

        print("yes he ran")
        i = 0
        songLyrics = ["you are my fire", "the one desire", "believe, when I say", "that I want it that way",
                      "but we",
                      "are two worlds apart", "I can't reach to your heart", "when you say",
                      "that I want it that way", "but we", "are two world apart", "I can't read to your heart",
                      "when you say,", "that I want it that way", "tell me why", "ain't nothing but a heartache",
                      "tell me why", "ain't nothing but a mistake", "I never wanna hear you say", "I want it that way"]
        while True:
            self.testParams = \
                [random.randint(1000, 10000), random.randint(1000, 10000), random.randint(1000, 10000),
                 random.randint(1000, 10000)]
            self.testInfo = [songLyrics[i], songLyrics[ (i+1)%(songLyrics.__len__()-1)],
                             songLyrics[(i+2)%(songLyrics.__len__()-1)],songLyrics[(i+3)%(songLyrics.__len__()-1)]]
            i += 1
            cv2.waitKey(3000)
            if i >= songLyrics.__len__()-1:
                i = 0

            PySide6.QtCore.QThread.sleep(1)
class s_server:#(QtCore.QThread):
    network: s_network
    isRunning = False
    # worker threads can use QObjects like QThread

    def __init__(self, serverIp: str, serverPort: int):
        #super().__init__()
        self.isRunning = True
        self.network = s_network(*SERVER_MICHELLE_PC)  # '* unpacks tuple. Note that tuples are read only, unlike arrays
        self.network.conn.setblocking(True)

    def run(self) -> None:  # inherited

        vid = cv2.VideoCapture(0)  # 0 to use webcam
        while self.isRunning:  # parent func
            status, frame = vid.read()

            #cv2.imshow('server',frame)

            vidMsg = msg_pb2.vidMsg()

            vidMsg.frame.frameShape.append(frame.shape[0])
            vidMsg.frame.frameShape.append(frame.shape[1])
            vidMsg.frame.frameShape.append(frame.shape[2])
            vidMsg.frame.frameBytes = frame.tobytes()

            k = 0
            while k < 4:
                vidMsg.parameters.append(test.testParams[k])
                vidMsg.info.append(test.testInfo[k])
                k += 1

            self.network.conn.sendall(vidMsg.SerializeToString())



            '''except Exception as exc:
                traceback.print_exc()'''


if __name__ == '__main__':

    test = Test()
    test.moveToThread(test)
    test.start()
    server = s_server(socket.gethostbyname(socket.gethostname()),
                          1234)
    while True:
        try:

            server.run()
        except ConnectionResetError:
            print("Disconnected. listening...")
            pass

        except:
            traceback.print_exc()  # get same data as when crashes. most importantly the stack traceback w/ line numbers
            exit()

