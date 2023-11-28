# requires python3
import io
from contextlib import contextmanager, redirect_stdout

trap = io.StringIO()

@contextmanager
def suppress_stdout():
  with redirect_stdout(trap):
    yield

if __name__ == '__main__':
  with suppress_stdout():
    print 'trapped content'
  print '------ intercepted and trapped content ------\n',trap.getValue()
