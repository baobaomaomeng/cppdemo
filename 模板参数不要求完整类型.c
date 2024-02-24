#include <iostream>
#include <typeinfo>

template<typename T>
class A {
public:
    int x;
    void name_father() {
        T temp{.xx=10};
        std::cout << temp.x << "\n";
        std::cout << typeid(T).name() << "\n";
        (static_cast<T*>(this))->name_son();
        return;
    }
};

class B : public A<B> {
public:
    int xx;
    void name_son(){
       std::cout << "sb\n";
    }
};

int main() {
    B f;
    f.name_father();
    return 0;
}
