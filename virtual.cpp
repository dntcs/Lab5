#include <iostream>
using namespace std;


class Figure {
    public:

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

        void draw() {
            cout << "Circle\n";
        }
    
    ~Circle() {
        cout << "~Circle\n";
    }
};

int main() {
    Circle circle;
    Figure* figure = &circle;

    circle.draw();
    figure->draw();
    circle.show();

    Figure* figure2 = new Circle;
    delete figure2;
    return 0;
}