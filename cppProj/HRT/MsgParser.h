#pragma once

//should move to MsgParser.h:
struct AbstractMsg{}; // not in use now

struct MsgParser{
  size_t const msgSz; // should be a private field with a getter
  virtual char parse(char *buf) = 0; //no buffer len needed .. guaranteed to be sufficient
protected:
  MsgParser(size_t sz): msgSz(sz){}
};
