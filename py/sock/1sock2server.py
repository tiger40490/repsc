#!/bin/env python
'''
To test, telnet to the server port and you will see the response from either parent or child process-id

Q: are there two copies of the socket, each with its own buffers? or only one object in memory?
I think lsof would show only one object.
'''
import socket
import os

def main():
    serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serversocket.bind(("127.0.0.1", 8888))
    serversocket.listen(0)

    # Child Process
    if os.fork() == 0:
        accept_conn("child", serversocket)

    accept_conn("parent", serversocket)

def accept_conn(message, s):
    message += "#pid=" + str(os.getpid())
    while True:
        c, addr = s.accept()
        print 'Got connection in   %s' % message
        c.send('Thank you for your connecting to   %s\n' % message)
        c.close()

if __name__ == "__main__":
    main()
