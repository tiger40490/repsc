/*? shared_ptr instance should be double the size of raw ptr but not here?
*/
#include <assert.h>
template<typename T> struct ControlBlock{
  ControlBlock(T* raw): _rawPtr(raw), _clubSize(1) {
    assert(raw && "Programmer error: null raw ptr passed in");
  }
  
  ~ControlBlock(){
      assert(_clubSize == 0);
      delete _rawPtr;
  }
  void inc(){ ++ this->_clubSize; } //atomic update
  void dec(){ -- this->_clubSize; }
  size_t cnt(){return _clubSize;}
private:
  T* _rawPtr; 
  size_t _clubSize;
};
template<typename T> struct ShPtr{
  //start new club
  ShPtr(T* raw): _cblock(new ControlBlock<T>(raw)) {}
  
  //join existing club
  ShPtr(ShPtr const & other): _cblock(other._cblock){
      assert(_cblock);
      _cblock->inc();
  }
  ~ShPtr(){
      _cblock->dec();
      if (_cblock->cnt() == 0) 
	    delete _cblock;//better than "delete this" in ControlBlock
  }
private: ControlBlock<T>* _cblock; //never null, always on heap
};
