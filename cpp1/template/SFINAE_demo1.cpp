#include <iostream>

struct AddOrderStructWithGetter {
                        long sendTimeNS() const;
};
struct AddRefreshOrderStruct {
                        long sendTimeNS;
};
struct EmptyStruct { };

// T is pinned to the type you spell out like AddRefreshOrderStruct. Compler has no leeway.
//
// There are 3 candidate overloaded functions named func():
// U will be the same type as T if one of Candidate XX or YY gets picked by the compiler.
// Otherwise, Candidate ZZ is picked and U is unused.
// function-template-overload resolution follows SNIFAE.

template<typename T> class FieldCheck{ // a class template with a nested class template + static method templates

    template<typename A, A non_dummy_type_templ_param> class Check; // This nested class template is unreadably deep and convoluted.


    //first template arg in Check<> below can use T or U, but somehow 2nd item
    //must not use T... I guess the SFINAE rules are non-trivial.
    template<typename U> static int    func(Check<long  U::*,          &U::sendTimeNS>*);//Candidate XX: 2nd item is a field
    template<typename U> static double func(Check<long (U::*)() const, &U::sendTimeNS>*);//Candidate YY: 2nd item is a method, somehow

    template<typename U> static char   func(...); //Candidate ZZ: default overload candidate, must be a func template
  public:
    static const //if no const, we can't initialize this filed here
      size_t result = sizeof(func<T>(NULL)); // 8 means has a method; 4 means has field
};

int main() {
  std::cout << FieldCheck <AddOrderStructWithGetter>::result <<std::endl;
  std::cout << FieldCheck <AddRefreshOrderStruct>   ::result <<std::endl;
  std::cout << FieldCheck <EmptyStruct>             ::result <<std::endl;
}
