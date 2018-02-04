#!/usr/bin/python -u
'''
TCP echo server based on https://docs.python.org/2.4/lib/socket-example.html
'''
import socket, sys,os , getopt
from datetime import datetime

def Hex(data): # a generator function
  i=0
  for c in map(ord,data):
    yield "%02x " % c
    i += 1
    if i%8==0: yield ' '

def ascii(data): # a generator function
  i=0
  for c in str(data):
    if c == '\r' :
        yield '\\r '
    elif c == '\n' :
        yield '\\n '
    elif c == '\t' :
        yield '\\t '
    elif c.isalnum():
        yield ' '+c+' '
    else:
        yield c+' '

    i += 1
    if i%8==0: yield '_'

#print ''.join(Hex("\x0a\x00")); exit(0)

def process1client(serverSock):
  conn, addr = serverSock.accept()
  print addr, 'client connected'
  while 1:
    data = conn.recv(1024)
    if not data: break
    print '[', datetime.utcnow(), "UTC] echoing ..", ''.join(Hex(data))
    print '[', datetime.utcnow(), "UTC] in ascii: ", ''.join(ascii(data))
    conn.send(data)
  conn.close()
  print addr, 'client disconnected'

def startServer(args):
  PORT = int(args[0])
  isFor1client = True

  s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  try:
    s.bind(('', PORT))
  except socket.error as e:
    if e.errno == 98: # check which process is using it
        os.system("netstat -pln |grep " + args[0])
        sys.exit(args[0]+" port is in use ..")

  s.listen(1) # backlog of 1
  while 1:
    try:
      print 'EchoServer listening on port', PORT, 'for a new client .. (Ctrl-C to kill)'
      process1client(s)
      if isFor1client:
        sys.exit('\n'+'Exiting after 1st client disconnects.')
    except KeyboardInterrupt:
      sys.exit('\n'+'Stopped by KeyboardInterrupt')

########### boilerplate ############
class Usage(Exception):
    def __init__(self, msg):
        self.msg = msg

def main(argv=None): # best practice from https://www.artima.com/weblogs/viewpost.jsp?thread=4829
  if argv is None:
        argv = sys.argv
  try:
        try:
            opts, args = getopt.getopt(argv[1:], "h", ["help"])
        except getopt.error, msg:
             raise Usage(msg) # convert the getopt exception to our custom Exception, and rethrow
        if len(args) + len(opts) == 0 :
             raise Usage("command line arg required")
  except Usage, err:
        print >>sys.stderr, err.msg
        print >>sys.stderr, "for help use --help"
        return 2
  for o, a in opts:
        if o == "-h" or o == "--help":
          print 'Usage example:', argv[0], '40493 # server port'
          return 3
  startServer(args)

if __name__== "__main__": # best practice.. make this script usable as a module
    sys.exit(main())
