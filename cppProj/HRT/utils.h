template<class T>  // this template has to live in a header file
T const*  cast(char const* buf) {
    T const* ret = reinterpret_cast<T const*>(buf)->cleanup();
    return ret;
}
