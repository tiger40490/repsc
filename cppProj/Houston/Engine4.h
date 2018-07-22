#ifndef E4_H
#define E4_H 1
#include <AbstractEngine.h>

/* This (unimplemented) engine is based on vector of vectors, up to 4 levels deep.

Motivation is to support sparse array, where  Engine3 would waste too much memory. Vector of vector can be staggered..

The Outermost layer (Layer 1) has 26 elements, each a poitner to a growable vector. Therefore there are 26 Level-2 vectors. 

Each Level-2 vector holds 1 to 26 elements, each a pointer to a Level-3 vector.

Each Level-3 vector holds 1 to 26 elements, each a pointer to a Level-4 vector.

Each Level-4 vector holds 1 to 26 elements, each a pointer to a PerSymbol object.

Q: Why four-levels? 
A: It supports 4-character symbols. If 5 or more levels deep, the code would be messy we would need refactor but still doable

Each vector, once instantiated, would reserve 26 slots. Therefore, these vectors never need reallocation.

The promised space-saving is due to on-demand allocation. If there's no symbol name starting with ab**, then the Level-2 vector corresponding to "ab**" is never created. Note there may exist a Level-2 vector for "aa**" and another Level-2 vector for "ac**". Between them there's a null pointer. In Engine3, that null pointer would be 26 x 26 = 676 null pointers.

Engine4 is guaranteed to have constant-time read and update by index. Insertion has average constant time due to on-demand vector instantiation. 
*/
class Engine4: public AbstractEngine {  
};
#endif
