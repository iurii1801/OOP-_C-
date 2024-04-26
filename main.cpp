#include <iostream>
using namespace std;


class Side {
protected:
    double a; // Длина стороны

public:
    Side(double a) : a(a) {}
};


class Rectangle : public Side {
protected:
    double b; // Вторая сторона прямоугольника

public:
    Rectangle(double a, double b) : Side(a), b(b) {}

    double area() {
        return a * b;
    }

    void showCharacteristics() {
        cout << "Rectangle: side a = " << a << ", side b = " << b << ", area = " << area() << endl;
    }
};


class Nightstand : public Rectangle {
private:
    double height; // Высота тумбочки

public:
    Nightstand(double a, double b, double height) : Rectangle(a, b), height(height) {}

    double capacity() {
        // Расчёт вместимости
        return area() * height;
    }

    void showCharacteristics() {
        cout << "Nightstand: side a = " << a << ", side b = " << b << ", height = " << height << ", capacity = " << capacity() << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    Rectangle rect1(5, 18);
    Rectangle rect2(4, 4);

    rect1.showCharacteristics();
    rect2.showCharacteristics();

    // Определение большего прямоугольника и сколько раз меньший прямоугольник входит в больший
    double area1 = rect1.area();
    double area2 = rect2.area();

    if (area1 > area2) {
        cout << "Первый прямоугольник больше второго в " << area1 / area2 << " раз(а)." << endl;
    }
    else if (area2 > area1) {
        cout << "Второй прямоугольник больше первого в " << area2 / area1 << " раз(а)." << endl;
    }
    else {
        cout << "Прямоугольники равны." << endl;
    }

    return 0;
}
