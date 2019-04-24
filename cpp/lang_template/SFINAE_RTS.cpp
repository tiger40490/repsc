#include <iostream>

struct AddOrderStructWithGetter {
                        long sendTimeNS() const;
};
struct AddRefreshOrderStruct {
                        long sendTimeNS;
};
struct EmptyStruct { };

// Three layers of templates
// 1) FieldCheck is a shell, slightly simpler than the other two.
// 2) Checker is a nested class template ... deep and convoluted.
// 3) func() is a group of 3 overloaded-static-member-function-templates.
// * They use the Checker class.
// * Overload resolution follows SNIFAE.
//
// T is pinned to the type you spell out, like AddRefreshOrderStruct. Compler has no leeway.
//
// Compiler will pick one of the 3 candidate functions named func():
// U will be the same type as T if Candidate XX or YY gets picked by the compiler.
// Otherwise, Candidate ZZ is picked and U is unused.

template<typename T> class FieldCheck{ // a class template with a nested class template + static method templates

    template<typename A, A non_dummy_type_templ_param> class Checker;

    //first template arg in Check<> below can use T or U, but somehow 2nd item
    //must not use T... I guess the SFINAE rules are non-trivial.
    template<typename U> static int    func(Checker<long  U::*,          &U::sendTimeNS>*);//Candidate XX: 2nd item is a field
    template<typename U> static double func(Checker<long (U::*)() const, &U::sendTimeNS>*);//Candidate YY: 2nd item is a method, somehow


    template<typename U> static char   func(...); //Candidate ZZ: default overload candidate, must be a func template
  public:
    static const //if no const, we can't initialize this field here
      size_t result = sizeof(func<T>(NULL)); // 8 means T has method; 4 means T has field
};

int main() {
  std::cout << FieldCheck <AddOrderStructWithGetter>::result <<std::endl;
  std::cout << FieldCheck <AddRefreshOrderStruct>   ::result <<std::endl;
  std::cout << FieldCheck <EmptyStruct>             ::result <<std::endl;
}
