//todo: 
#include <thread>
#include <iostream>
using namespace std;

class Worker{
public:
    Worker() : _value(0) {}
    void operator()(unsigned int value);
    unsigned int get_value() {return this->_value;}
private:
    unsigned int _value;
};

void Worker::operator()(unsigned int value)
{
    this->_value = value;
}

int main()
{
    Worker worker;
    thread thread(ref(worker), 13);
    thread.join();
    unsigned int value = worker.get_value();
    cout << "value: " << value << endl;
}/*based on https://stackoverflow.com/questions/42894629/correct-use-of-functor-for-c-stl-thread
*/