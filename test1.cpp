#include <iostream>

class A {
public:
    virtual ~A() = default;
};

class B : public A {

};

int main() {
    int* a;
    std::cout << sizeof(a) << std::endl;


//    B b = B();
//    A &a = b;

//    B& c = dynamic_cast<B&>(a);



    return 0;
}