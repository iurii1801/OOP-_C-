#include <iostream>
using namespace std;


class Side {
protected:
    double a; // Äëčíŕ ńňîđîíű

public:
    Side(double a) : a(a) {}
};


class Rectangle : public Side {
protected:
    double b; // Âňîđŕ˙ ńňîđîíŕ ďđ˙ěîóăîëüíčęŕ

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
    double height; // Âűńîňŕ ňóěáî÷ęč

public:
    Nightstand(double a, double b, double height) : Rectangle(a, b), height(height) {}

    double capacity() {
        // Đŕń÷¸ň âěĺńňčěîńňč
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

    // Îďđĺäĺëĺíčĺ áîëüřĺăî ďđ˙ěîóăîëüíčęŕ č ńęîëüęî đŕç ěĺíüřčé ďđ˙ěîóăîëüíčę âőîäčň â áîëüřčé
    double area1 = rect1.area();
    double area2 = rect2.area();

    if (area1 > area2) {
        cout << "Ďĺđâűé ďđ˙ěîóăîëüíčę áîëüřĺ âňîđîăî â " << area1 / area2 << " đŕç(ŕ)." << endl;
    }
    else if (area2 > area1) {
        cout << "Âňîđîé ďđ˙ěîóăîëüíčę áîëüřĺ ďĺđâîăî â " << area2 / area1 << " đŕç(ŕ)." << endl;
    }
    else {
        cout << "Ďđ˙ěîóăîëüíčęč đŕâíű." << endl;
    }

    return 0;
}
