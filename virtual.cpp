#include <iostream>
#include <string>
using namespace std;


class Figure {
    public:
        virtual string classname() {
            return string("Figure");
        }

        virtual bool isA(string name) {
            if (name == "Figure") {
                return true;
            } else return false;
        }

        virtual void draw() {
            cout << "Figure\n";
        }

        void show() {
            draw();
        }

    virtual ~Figure() {
                cout << "~Figure\n";
    }

};

class Circle: public Figure {
    public:
        string classname() {
            return string("Circle");
        }

        virtual bool isA(string name) {
            if (name == "Circle") {
                return true;
            } else return Figure::isA(name);
        }

        void draw() {
            cout << "Circle\n";
        }
    
    ~Circle() {
        cout << "~Circle\n";
    }
};

int main() {
    Figure circle;
    Figure* figure = &circle;

    cout << figure->isA("Circle") << '\n';
    cout << figure->isA("Figure") << '\n';
    cout << (figure->classname() == "Figure") << '\n';

    if (figure->isA("Circle")) {
        Circle* circlePtr = static_cast<Circle*>(figure);
        circlePtr->draw();
    }

    Circle* circlePtr = dynamic_cast<Circle*>(figure);
    if (circlePtr != nullptr) {
        circlePtr->draw();
    }

    return 0;
}