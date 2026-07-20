import sys, pickle, socket, struct

"enums"
IP = int(0)
PORT = int(1)
COMPUTER_NAME = int(2)


class c_network:

    # create my socket
    conn = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # arguments specify the socket we are creating works
    # with TCP protocol
    serverAddr = [str, int]  # IP = 0, PORT = 1
    myComputerName = socket.gethostname()  # the host name of this computer
    # example- DESKTOP-BSH6JM'''

    '''gethostbyname returns str of ip address (not used here)
    #gethostname returns str of computer name'''

    def __init__(self, serverIp: str, serverPort: int):
        self.serverAddr[PORT] = serverPort
        self.serverAddr[IP] = serverIp

        '''waits 5 sec until the connection will be closed'''
        self.conn.settimeout(5)

        isConnected = False
        while not isConnected:
            try:
                # connect between my socket and the server's socket
                self.conn.connect((self.serverAddr[IP], self.serverAddr[PORT]))
                isConnected = True
            except (socket.error, socket.timeout) as exc:
                '''exception types in the brackets are the
                types that can be caught'''
                print("socket.error: %s" % exc)

        print("Connected...")

        '''important! so we don't timeout while msgs aren't received'''
        self.conn.settimeout(None)

        self.conn.send(self.myComputerName.encode()) #send welcome msg
        print(self.conn.recv(1024).decode()) #recv welcome msg

