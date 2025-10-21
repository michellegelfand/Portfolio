import socket

#"enums"
import socketserver

IP = 0
PORT = 1
COMPUTER_NAME = 2


'''purposefully no exception catching here. I want the server module to catch them so I can see them'''


class s_network:

    '''This socket is used to listen for clients.
       Arguments specify TCP protocol'''
    listen: socket.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    '''This socket is created after a connection to the client is made.
       Communication is done through it'''
    conn = socket.socket

    '''it will receive str, int, str'''
    serverAddr = [str(''), int(), str()]

    '''This is a tuple we receive from socket.accept()
    IP = 0, PORT = 1'''
    clientAddr = (str, int)

    '''init function sets up our socket and connects the client'''
    def __init__(self, serverIp: str, serverPort: int):
        super().__init__()
        self.serverAddr[IP] = serverIp
        self.serverAddr[PORT] = serverPort
        self.serverAddr[COMPUTER_NAME] = socket.gethostname()
        '''gethostbyname returns str of ip address (not used here)
        gethostname returns str of computer name'''

        listen: socket.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        self.listen.bind((serverIp,serverPort))
        print("listen")
        self.listen.listen(1) #argument tells it to stop listening after 1 client connects
        print("after")
        self.conn, self.clientAddr = self.listen.accept() #self.clientAddr is info you can print as done below
        print("accept")
        self.conn.setsockopt(socket.SOL_SOCKET,socket.SO_KEEPALIVE,1)
        helloMsg = str("Client: ('" + str(self.clientAddr[0]) + "'," + str(self.clientAddr[1])+')\n')
        helloMsg += str("Server: " + str(socket.socket.getsockname(self.listen)))
        print(helloMsg)
        print(self.conn.recv(1024).decode(), "has connected")
        self.conn.send(helloMsg.encode())


