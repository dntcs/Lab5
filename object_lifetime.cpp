#include <iostream>
#include <windows.h>
using namespace std;

class Base {
    public:
        Base() {
            cout << "Base() без параметров\n";
        }

        Base(Base& other) {
            cout << "Base() копирования\n";
        }
        Base(Base* other) {
            cout << "Base() с указателем\n";
        }

    ~Base() {
        cout << "~Base()\n";
    }
};

class Desc: public Base {
    public:
        Desc() {
            cout << "Desc() без параметров\n";
        }
        Desc(Desc& other) {
            cout << "Desc() копирования\n";
        }
        Desc(Desc* other) {
            cout << "Desc() с указателем\n";
        }

    ~Desc() {
        cout << "~Desc()\n";
    }
};

void fun1(Base obj) {
    cout << "fun1 по значению" << '\n';
};

void fun2(Base* obj) {
    cout << "fun2 по указателю на объект" << '\n';
};

void fun3(Base& obj) {
    cout << "fun3 по ссылке" << '\n';
};

Base returnLocalValue() {
    Base local;
    return local;
}
Base* returnLocalPtr() {
    static Base local;
    return &local;
}
Base& returnLocalRef() {
    static Base local;
    return local;
}
Base* returnHeapPtr() {
    return new Base;
}
Base& returnHeapRef() {
    Base* ptr = new Base;
    return *ptr;
}
Base returnHeapValue() {
    Base* ptr = new Base;
    Base result(*ptr);
    delete ptr;
    return result;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    Base obj;
    Base fromPtr(&obj);
    Desc child;
    Desc copy(child);
    Desc fromChildPtr(&child);

    cout << "\nПередаём объект Base в функции\n";

    fun1(obj);
    fun2(&obj);
    fun3(obj);
    
    cout << "\nПередаём объект Desc в функции\n";

    fun1(child);
    fun2(&child);
    fun3(child);


    
    Base* ptr = returnLocalPtr();
    Base* ptr2 = returnLocalPtr();
    Base& ref = returnLocalRef();
    Base* heapPtr = returnHeapPtr();
    Base& heapRef = returnHeapRef();
    Base heapValue = returnHeapValue();

    cout << (ptr == ptr2) << '\n'; // проверка адреса

    cout << "Перед delete\n";
    delete heapPtr;
    delete &heapRef;
    cout << "После delete\n";

    Base returned = returnLocalValue();
    cout << "\nУничтожение объектов\n";
    return 0;
}