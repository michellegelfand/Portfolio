import datetime
import py_compile
import string
import traceback
import typing
import PySide6
import cv2
import numpy
from PySide6 import QtWidgets, QtGui
from PySide6.QtCore import QThread, QTimer
from PySide6.QtGui import *
from PySide6.QtWidgets import *
import json


import msg_pb2
from c_network import *  # to import their imports
'''sometimes compiler will complain about another instance of qapplication
if that happens then import specific things for example from qdarktheme import setup_theme'
instead of from qdarktheme import * which imports everthing including thier imports'''


SERVER_MICHELLE_PC = (socket.gethostbyname(socket.gethostname()), 1234)

'''w in name indicates worker thread - this thread must not touch the gui,
and communicates with signals only'''


class gui(PySide6.QtCore.QObject):  # not QThread, so this will run as main thread
    """signals must be defined only in classes inheriting from QObject!"""

    app = QtWidgets.QApplication()
    win = QtWidgets.QWidget()
    mainWin = QtWidgets.QMainWindow()  # for funcs that come with it, menus and stuff

    pattern_ip = PySide6.QtCore.QRegularExpression()
    pattern_ip.setPattern('\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}')

    valid_ip = QRegularExpressionValidator()
    valid_ip.setRegularExpression(pattern_ip)


    screenLabel = QtWidgets.QLabel()  # required, to put pixmap on
    screenPixMap = QtGui.QPixmap(640, 480)
    screenLabel.setPixmap(screenPixMap)
    screenLabel.setFixedSize(640, 480)
    timer_clockTick = QTimer()
    time_record= int
    time_pause= int
    sig_streamerSettings = PySide6.QtCore.Signal(str, int)
    sig_recorderSettings = PySide6.QtCore.Signal(int, int)
    sig_ui = PySide6.QtCore.Signal()

    textDisplay= PySide6.QtWidgets.QTextEdit()
    def __init__(self):
        super().__init__()
        self.sig_ui.connect(self.ui)

    def welcome_phase2(self):
        """we recieved the input and are setting up"""
        self.serverIp = self.input_ip.text()
        self.serverPort = int(self.input_port.text())
        self.time_record = self.input_secToRecord.value()
        self.time_pause = self.input_secToPause.value()

        self.connMsg = QMessageBox(text="Network:\nConnecting...", parent=self.mainWin)
        self.connMsg.setWindowTitle("Crystal Tracker")
        self.connMsg.setStandardButtons(QMessageBox.StandardButton.Cancel)  # remove ok button
        self.connMsg.setEscapeButton(QMessageBox.StandardButton.Cancel)


        self.connMsg.setStyleSheet("QLabel{min-width:200 px;}")  # size funcs won't work for some reason
        #self.connMsg.show()


        '''self.sig_streamerSettings.emit(self.serverIp, self.serverPort)
        self.sig_recorderSettings.emit(self.time_record,self.time_pause)'''
        print(self.serverIp, self.serverPort, self.time_record, self.time_pause)

        settings = {
            'ip': self.serverIp,
            'port': self.serverPort,
            'record on': self.time_record,
            'record off': self.time_pause,
        }

        json_object = json.dumps(settings, indent=4)
        with open('settings.json', 'w') as outfile:
            outfile.write(json_object)
            outfile.close()

        self.sig_ui.emit()  # if you call it it doesn't work I don't know why. must emit before other ones below as well
        self.sig_streamerSettings.emit(self.serverIp, self.serverPort)
        self.sig_recorderSettings.emit(self.time_record, self.time_pause)




    """this method makes inputting the ip more flashy"""
    def onTextChanged(self, text:str):
        pass
        '''if len(text)>self.prev_len and (len(text) ==2 or len(text)==4 or len(text) ==6):
            self.input_ip.setText(self.input_ip.text() + ".")
        self.prev_len = len(text)'''

    def welcome(self):

        self.prev_len = 0
        self.dialog = QDialog()
        self.lay_welcome = QFormLayout()
        form = PySide6.QtWidgets.QGroupBox()
        self.dialog.setWindowTitle("Crystal Tracker")


        self.input_ip = QLineEdit()
        self.input_ip.setCompleter(QCompleter(["10.0.0.32", "10.0.0.16"],self.input_ip))



        self.input_ip.textChanged.connect(self.onTextChanged)
        self.input_ip.setPlaceholderText("10.0.0.32")


        self.input_ip.setValidator(self.valid_ip)

        self.input_port = QLineEdit()
        self.input_port.setCompleter(QCompleter(['1234']))

        self.input_port.setValidator(QIntValidator(1000,10000))
        self.input_port.setPlaceholderText("1234")

        self.input_secToRecord = QSpinBox()
        self.input_secToPause = QSpinBox()

        self.input_secToPause.setAccelerated(True)
        self.input_secToRecord.setAccelerated(True)
        self.input_secToPause.setRange(1,3600)
        self.input_secToRecord.setRange(1,3600)



        self.lay_welcome.addRow('Server IP', self.input_ip)
        self.lay_welcome.addRow('Port', self.input_port)
        self.lay_welcome.addRow('Recording duration (seconds)', self.input_secToRecord)
        self.lay_welcome.addRow('Pause recording duration (seconds)', self.input_secToPause)
        buttonBox = QDialogButtonBox(QDialogButtonBox.StandardButton.Ok | QDialogButtonBox.StandardButton.Close)
        buttonBox.accepted.connect(self.dialog.accept)
        buttonBox.rejected.connect(self.dialog.reject)
        self.lay_welcome.addRow(buttonBox)
        self.dialog.setLayout(self.lay_welcome)
        self.dialog.accepted.connect(self.welcome_phase2)





        self.dialog.show()

        '''self.input_ip.setText("10.0.0.32")
        self.input_port.setText("1234")'''
        '''self.input_secToRecord.setValue(3)
        self.input_secToPause.setValue(3)'''
        '''emit network settings to wstreamer'''
    def slot_displayFrame(self, qImg1: QImage):
        self.screenLabel.setPixmap(QPixmap.fromImage(qImg1))
        self.screenLabel.update()
        self.screenLabel.show()

    def lightTheme(self):
        # darktheme.setup_theme("light")
        self.lightThemeSelect.setChecked(True)
        self.darkThemeSelect.setChecked(False)

    def darkTheme(self):
        '''self.clock_recording.setStyleSheet("background-color: lightblue;")
        self.clock_time.setStyleSheet("background-color: lightblue;")
        self.clock_upTime.setStyleSheet("background-color: lightblue;")'''





        self.lightThemeSelect.setChecked(False)
        self.darkThemeSelect.setChecked(True)

    def reqClose(self):
        self.app.aboutToQuit.emit()
        QThread.sleep(1)  # this gives streamer thread time to close
        self.app.exit(0)

    def ui(self):
        "windows and layout"

        self.gLayout = PySide6.QtWidgets.QGridLayout(self.win)  # only layout that allows moving widgets to coordinates,
        self.win.setLayout(self.gLayout)
        self.mainWin.setCentralWidget(self.win)
        self.win.setWindowTitle("Crystal Tracker")
        # 'g' for grid

        """text displayer"""
        #self.textDisplay = PySide6.QtWidgets.QTextEdit()
        self.textDisplay.setReadOnly(True)
        self.textDisplay.setMinimumSize(300, 300)
        self.gLayout.addWidget(self.textDisplay, 0, 0)

        """clocks and secondary layout"""
        self.hLayout = PySide6.QtWidgets.QHBoxLayout()
        self.clock_recording = self.recordingClock(4)
        self.clock_time = self.clock(PySide6.QtCore.QTime.currentTime(), 8)
        self.clock_upTime = self.clock(PySide6.QtCore.QTime(0, 0, 0), 8)
        self.clock_upTime.setFixedSize(100, 40)
        self.clock_recording.setFixedSize(100, 40)
        self.clock_time.setFixedSize(100, 40)
        self.gLayout.addLayout(self.hLayout, 400, 0)
        self.hLayout.addWidget(self.clock_time)
        self.hLayout.addWidget(self.clock_upTime)
        self.hLayout.addLayout(self.clock_recording.hLayout, Qt.AlignmentFlag.AlignRight)
        self.hLayout.addStretch(1)
        # self.hLayout.addLayout(self.recordingClock.hLayout)



        """TV"""
        self.screenPixMap.fill(PySide6.QtGui.QColor('darkGray'))
        self.screenLabel.setPixmap(self.screenPixMap)
        self.gLayout.addWidget(self.screenLabel, 0, 400)

        """menu"""
        self.menuBar = PySide6.QtWidgets.QMenuBar()
        self.viewMenu = self.menuBar.addMenu("Appearance")
        self.gLayout.setMenuBar(self.menuBar)
        self.selectTheme = PySide6.QtWidgets.QMenu("Themes")
        self.viewMenu.addMenu(self.selectTheme)
        self.lightThemeSelect = PySide6.QtGui.QAction("Light", self.win)
        self.darkThemeSelect = PySide6.QtGui.QAction("Dark", self.win)
        self.menuBar.setMouseTracking(True)
        self.lightThemeSelect.setCheckable(True)
        self.darkThemeSelect.setCheckable(True)
        self.lightThemeSelect.triggered.connect(self.lightTheme)
        self.darkThemeSelect.triggered.connect(self.darkTheme)
        self.selectTheme.addAction(self.lightThemeSelect)
        self.selectTheme.addAction(self.darkThemeSelect)
        self.menuBar.addSeparator()
        self.exit = QPushButton("exit")
        self.exit.clicked.connect(self.reqClose)
        self.app.lastWindowClosed.connect(self.reqClose)
        self.hLayout.addWidget(self.exit)

        """adjust sizes"""

        self.win.adjustSize()
        self.mainWin.adjustSize()
        self.timer_clockTick.setInterval(1000)
        self.timer_clockTick.start()











        self.timer_clockTick.timeout.connect(self.clock_time.increment)
        streamer.sig_pixmapToGui.connect(gui1.slot_displayFrame)
        streamer.sig_updateTextDisplay.connect(gui1.slot_updateTextDisplay)

        self.exit.show()
        self.screenLabel.show()
        self.clock_time.show()
        self.clock_upTime.show()
        self.clock_recording.show()
        self.win.show()
        self.mainWin.show()
        self.timer_clockTick.timeout.connect(self.clock_upTime.increment)
        self.timer_clockTick.timeout.connect(self.clock_recording.decrement)
        QTimer.singleShot(gui1.time_record * 1000, gui1.clock_recording.timeout)

    class clock(QtWidgets.QLCDNumber):
        currentTime: PySide6.QtCore.QTime

        # *args recieves any argument
        def __init__(self, startTime: PySide6.QtCore.QTime, *args):
            super().__init__(*args)
            self.currentTime = startTime
            currentTimeStr = self.currentTime.toString('hh:mm:ss')

        def increment(self):
            currentTimeStr = self.currentTime.toString('hh:mm:ss')
            self.display(currentTimeStr)
            self.currentTime = self.currentTime.addSecs(1)

    class recordingClock(QtWidgets.QLCDNumber):

        hLayout = PySide6.QtWidgets.QHBoxLayout()

        time_record: int
        time_pause: int
        currentTime = PySide6.QtCore.QTime()

        isRecording = True

        """checkbox"""
        recCheckBox = PySide6.QtWidgets.QCheckBox('Recording')
        recCheckBox.click()
        recCheckBox.setAttribute(PySide6.QtGui.Qt.WidgetAttribute.WA_TransparentForMouseEvents,
                                 True)  # unclickable, read-only

        def __init__(self, *args):
            super().__init__(*args)
            self.hLayout.addWidget(self)
            self.hLayout.addWidget(self.recCheckBox)
            self.hLayout.addStretch(1)  # cram clocks together
            # QTimer.singleShot(self.recTimeSecs * 1000, self.timeout)  moved to main func because of delay starting
            self.time_record = gui1.time_record  # simpler to get from gui than wait for recorder signal
            self.time_pause = gui1.time_pause
            self.currentTime.setHMS(0, 0, gui1.time_record)
        def decrement(self):
            currentTimeStr = self.currentTime.toString('hh:mm:ss')
            self.display(currentTimeStr)
            self.currentTime = self.currentTime.addSecs(-1)

        def timeout(self):
            if self.isRecording:
                self.currentTime.setHMS(0, 0, self.time_pause)
                QTimer.singleShot(self.time_pause * 1000, self.timeout)
            else:
                self.currentTime.setHMS(0, 0, self.time_record)
                QTimer.singleShot(self.time_record * 1000, self.timeout)

            self.isRecording = not self.isRecording  # flip boolean
            self.recCheckBox.click()

    def slot_updateTextDisplay(self, data: str):
        self.textDisplay.setText(data)


class w_streamer(PySide6.QtCore.QThread):

    network: c_network
    sig_pixmapToGui = PySide6.QtCore.Signal(QImage)
    sig_updateTextDisplay = PySide6.QtCore.Signal(str)
    sig_vidLog = PySide6.QtCore.Signal(numpy.ndarray)
    sig_log = PySide6.QtCore.Signal(str)
    on = True

    def __init__(self):
        super().__init__()

    def reqClose(self):
        self.on = False

    def slot_connectAndRun(self, serverIp: str, serverPort:int):
        self.network = c_network(serverIp, serverPort)
        self.network.conn.setblocking(True)

        """"
               these signals are connected in gui thread:
               sig_pixmapToGui = PySide6.QtCore.Signal(QImage)
               sig_updateTextDisplay = PySide6.QtCore.Signal(str)
             

        thread.quit thread.exit can only be called from within thread
        those only work if thread runs on exec() event loop. wont work on endless while loop"""


        msg = b''

        while self.on:
            try:
                """msgs have different sizes depending on content
                I saw average message has about 921704 bytes
                add a bit to that amount recieved or else parsing error exception"""
                msg = self.network.conn.recv(940000)
                decrypted = msg_pb2.vidMsg()
                decrypted.ParseFromString(msg)
                frame = numpy.frombuffer(decrypted.frame.frameBytes, dtype=numpy.uint8).reshape(
                    decrypted.frame.frameShape)

                '''process the img so the gui isn't burdened'''
                im1 = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
                height1, width1, channel1 = im1.shape
                step1 = channel1 * width1
                qimg1 = PySide6.QtGui.QImage(im1.data, width1, height1, step1, PySide6.QtGui.QImage.Format_RGB888)

                # signal gui
                self.sig_pixmapToGui.emit(qimg1)
                self.sig_updateTextDisplay.emit(decrypted.info.__str__() + decrypted.parameters.__str__())

                # signal recorder
                self.sig_vidLog.emit(frame)
                self.sig_log.emit(decrypted.info.__str__() + decrypted.parameters.__str__())

                # print(decrypted.info)
                # print(decrypted.parameters)'''

                cv2.waitKey(10)
            except Exception as exc1:
                '''qthread should not be terminated from outside, and you shouldnt use "terminate" command as those can corrupt data
                and don't take into account what the thread is currently doing'''

        self.exit(0)  # we need to call this too cause theres an event loop now

    def run(self) -> None:
        gui1.sig_streamerSettings.connect(self.slot_connectAndRun)
        gui1.app.aboutToQuit.connect(self.reqClose)  # must be called in run because actual thread runs here
        print("main thread?")
        self.exec()


class w_recorder(PySide6.QtCore.QThread):
    logger: typing.TextIO
    out: cv2.VideoWriter
    time_record: int
    time_pause: int
    isRecording: bool
    readyTxtLog = True
    readyVidLog = True
    isRecording = False
    sig_start = PySide6.QtCore.Signal()

    def __init__(self):
        super().__init__()

    def reqClose(self):
        if self.isRecording:  #program can close at first menu before files were created
            self.logger.close()  # if you don't close the txt file it doesn't save anything!
            self.out.release()
        self.exit(0)

    def slot_recvTimes(self, time_record: int, time_pause: int):

        self.time_record = time_record
        self.time_pause = time_pause
        self.sig_start.emit()


    def slot_start(self):

        self.vidDate = datetime.datetime.now()
        vidDateStr = self.vidDate.__str__()
        vidStrSplit = vidDateStr.split('.')  # cut miliseconds that appear after '.' in the str
        title = vidStrSplit[0].__str__()
        title = title.replace(':', '-')  # filenames dont like ':'
        '''fourcc = cv2.VideoWriter_fourcc(
            *'X264')  # mp4 format. MP4V doesn't work. It has also succesfully created avi before'''
        fourcc = cv2.VideoWriter_fourcc(*'XVID')
        self.out = cv2.VideoWriter(title + '.avi', fourcc, 20.0, (640, 480))

        self.logger = open(title + ".txt", "a")  # 'x' means create new file, returns error if file exists
        # 'a' will create or open existing and append
        '''do not use w as it overwrites'''
        self.isRecording = True

        gui1.app.aboutToQuit.connect(self.reqClose)
        streamer.sig_vidLog.connect(self.vidLog)
        streamer.sig_log.connect(self.log)

        QTimer.singleShot(self.time_record * 1000, self.timeout)  # right before exec to avoid delay
    def nextTxtLog(self):
        if self.isRecording:
            ''' in case called after timeout func - when we don't want to log. This check is the only reason we made this 
         function instead of connecting block_log.unblock to the timer directly'''
            self.readyTxtLog = True

    def timeout(self):
        '''signal.disconnect refuses to work. QSignalBlocker blocks signals for the entire program, not just for this thread.
        so that causes gui freezes'''
        if self.isRecording:
            self.readyTxtLog = False
            self.readyVidLog = False
            QTimer.singleShot(self.time_pause * 1000, self.timeout)
            """this is called automatically when file is close at end of program.
            calling this periodically ensures the text logged is safe incase program crashes. 
            otherwise the whole file is lost if unflushed at the very end"""
            self.logger.flush()


        else:
            self.readyTxtLog = True
            self.readyVidLog = True
            QTimer.singleShot(self.time_record * 1000, self.timeout)
        self.isRecording = not self.isRecording  # flip boolean

    def log(self, msg: str):
        if self.readyTxtLog:
            self.readyTxtLog = False
            now = datetime.datetime.now()
            self.logger.write(now.__str__() + '$'
                              + now.__sub__(self.vidDate).__str__() + '$' + msg + "\n")
            QTimer.singleShot(2000, self.nextTxtLog)

    def vidLog(self, frame: numpy.core._multiarray_umath.ndarray):
        if self.readyVidLog:
            self.out.write(frame)

    '''run sets up signals and opens files to write to, then runs event loop'''

    def run(self) -> None:
        gui1.sig_recorderSettings.connect(self.slot_recvTimes)
        gui1.app.aboutToQuit.connect(self.reqClose)
        self.sig_start.connect(self.slot_start)
        self.exec()  # to wait for signal



'''
Signal list: 
sorted as:

recieving thread:
sender | signal name

gui:
 
w_streamer | updateTextDisplay
w_streamer | pixmapToGui 
gui timers | in clocks



to add:
w_recorder
w_recorder | logFrame
we_recorder | logText 

*QTimer can only be used in the main thread that does app.exec, and can only signal itself
===============================
general adds:
server sends disconnect msg?
client sends disconnect msg?


'''

if __name__ == '__main__':

    import os  # for test access dir


    origfolder = 'C:\\Users\matan\\OneDrive\\Desktop\\Crystal Tracker\\client'
    test = os.listdir(origfolder)

    for item in test:
        if item.endswith(".avi"):
            os.remove(os.path.join(origfolder, item))
        if item.endswith(".txt"):
            os.remove(os.path.join(origfolder, item))
    try:
        gui1 = gui()
        streamer = w_streamer()
        recorder = w_recorder()
        streamer.start()  # when closing app: finished with code 0. streamer does not!
        streamer.moveToThread(streamer)
        recorder.start()

        '''checking if restart'''
        if os.path.isfile('settings.json'):
            with open('settings.json', 'r') as openfile:
                json_object = json.load(openfile)
                if gui.valid_ip.validate(json_object['ip'],0):  # does file exist & is ip valid
                    gui1.time_record = json_object['record on']
                    gui1.time_pause = json_object['record off']
                    gui1.ui()
                    gui1.sig_streamerSettings.emit(json_object['ip'], json_object['port'])
                    gui1.sig_recorderSettings.emit(json_object['record on'], json_object['record off'])
                else:
                    gui1.welcome()
                openfile.close()
        else:
            print("no file")
            gui1.welcome()

        sys.exit(gui1.app.exec())


    except py_compile.PyCompileError as exc:  # not compiling (exceptions fuck up showing this when caught)
        print(exc)
        traceback.print_tb(exc.__traceback__)  # to show line!
    except Exception as exc:  # not compiling (exceptions fuck up showing this when caught)
        print(exc)
        traceback.print_tb(exc.__traceback__)  # to show line!
