#include <iostream>
#include <memory>
#include <utility>
#include <windows.h>

using namespace std;

class Base {
public:
    Base() {
        cout << "Base() без параметров\n";
    }

    ~Base() {
        cout << "~Base()\n";
    }
};

unique_ptr<Base> makeBaseUnique() {
    return make_unique<Base>();
}

void takeUnique(unique_ptr<Base> ptr) {
    cout << "Внутри takeUnique\n";
}

shared_ptr<Base> makeBaseShared() {
    return make_shared<Base>();
}

void takeShared(shared_ptr<Base> ptr) {
    cout << "Внутри takeShared, владельцев: " << ptr.use_count() << '\n';
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    cout << "Обычный локальный объект\n";
    {
        Base local;
        cout << "Внутри блока\n";
    }
    cout << "После блока\n\n";

    cout << "unique_ptr\n";
    {
        unique_ptr<Base> ptr = makeBaseUnique();

        cout << "Перед вызовом takeUnique\n";
        takeUnique(move(ptr));
        cout << "После вызова takeUnique\n";

        if (ptr == nullptr) {
            cout << "Указатель в main пуст\n";
        }
    }

    cout << "\nshared_ptr\n";
    {
        shared_ptr<Base> first = makeBaseShared();
        cout << "После создания, владельцев: " << first.use_count() << '\n';

        {
            shared_ptr<Base> second = first;
            cout << "После копирования указателя, владельцев: " << first.use_count() << '\n';

            takeShared(second);
            cout << "После вызова takeShared, владельцев: " << first.use_count() << '\n';
        }

        cout << "Внутренний блок завершился, владельцев: " << first.use_count() << '\n';
    }
    cout << "\nВнешний блок завершился\n";

    return 0;
}