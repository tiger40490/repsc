#include <iostream> //size_t
#include <assert.h>
template<typename T> struct ControlBlock{
  ControlBlock(T* raw): _rptr(raw), _cnt(1){  }
  ~ControlBlock(){
      assert(_cnt ==0);
      delete _rptr;
  }
  void inc(){
      //aquirelock();
      ++ this->_cnt;     
      //relLock();
  }
  void dec(){
      //aquirelock();
      -- this->_cnt;     
      //relLock();
  }
  size_t cnt(){return _cnt;}
private:
  T* _rptr; //could be null
  size_t _cnt;
};

template<typename T> struct sptr{
  //creates a new club without an existing contol block
  sptr(T * raw): _block(new ControlBlock<T>(raw)){}
  
  //join existing club
  sptr(sptr const & other):_block(other._block){
      _block->inc();
  }
  ~sptr(){
      _block->dec();
      if (_block->cnt() == 0) delete _block;
  }
private:
  ControlBlock<T>* _block;
};
