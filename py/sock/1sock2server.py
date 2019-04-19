#!/bin/env python
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
'''Based on https://stackoverflow.com/questions/670891/is-there-a-way-for-multiple-processes-to-share-a-listening-socket
To test, telnet to the server port and you will see the response from either parent or child process-id, possibly in round-robin.

Q: are there two copies of the socket, each with its own buffers? or only one object in memory?
A: q(lsof -i :8888) shows only one so-called device.

I believe this program is unusual in that child process also runs accept() thus becoming a second listening server !
'''
