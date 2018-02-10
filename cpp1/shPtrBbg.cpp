#include <assert.h>
template<typename T> struct ControlBlock{
  ControlBlock(T* raw): _rawPtr(raw), _clubSize(1) {}
  ~ControlBlock(){
      assert(_clubSize ==0);
      delete _rawPtr;
  }
  void inc(){
      //aquirelock();
      ++ this->_clubSize;     
      //relLock();
  }
  void dec(){
      //aquirelock();
      -- this->_clubSize;     
      //relLock();
  }
  size_t cnt(){return _clubSize;}
private:
  T* _rawPtr; //could be null
  size_t _clubSize;
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
