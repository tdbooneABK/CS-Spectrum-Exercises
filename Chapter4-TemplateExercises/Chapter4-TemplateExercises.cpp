#include <iostream>
using namespace std;

template <typename T>
T Maximum(T a, T b) {
    if (a < b) {
        return b;
    }
    else {
        return a;
    }
}

template <typename T>
class Point {
public:
    T x;
    T y;

    Point(T x, T y)
        : x(x),
        y(y)
    {
    };

    T GetLargerCoordinate() {
        if (x > y) {
            return x;
        }
        else {
            return y;
        }
    }

    T GetSmallerCoordinate() {
        if (x > y) {
            return y;
        }
        else {
            return x;
        }
    }
};

int main()
{
    int intA = 7;
    int intB = 13;
    float floatA = 3.0f;
    float floatB = 5.2f;

    cout << "Max int: " << Maximum(intA, intB) << endl;
    cout << "Max float: " << Maximum(floatA, floatB) << endl;

    Point<int> myPoint = Point<int>(4, 3);
    cout << "Max coordinate: " << myPoint.GetLargerCoordinate() << endl;
    cout << "Min coordinate: " << myPoint.GetSmallerCoordinate() << endl;
}
