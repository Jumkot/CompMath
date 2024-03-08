#include <iostream>
#include <cmath>

using namespace std;

double f(double x) {
    
    return 1 - 0.5 * pow(x, 2) * log(x) + 0.3 * sqrt(x);
}

double chords(double a, double b, double eps) {
    double x0, x1;
    int count = 0;

    do {
        x0 = a - (f(a) * (b - a)) / (f(b) - f(a));
        x1 = b - (f(b) * (a - b)) / (f(a) - f(b));

        if (f(x0) * f(a) < 0) {
            b = x0;
        } else {
            a = x0;
        }
        if (f(x1) * f(b) < 0)
        {
            a = x1;
        } else {
            b = x1;
        }
        cout << "Итерация № " << (count++) + 1 << ": x0 = " << abs(f(x0)) << endl;
    } while (abs(f(x0)) > eps && abs(f(x1)) > eps);

    return abs(f(x0)) < eps ? x0 : x1;
}

int main() {
    //------------------------------------
    // a. b. Локализация корня и входные данные
    //------------------------------------
    double a = 1.0;
    double b = 3.0;
    double eps = 0.000001;

    //------------------------------------
    // c. Выходные данные
    //------------------------------------
    double root = chords(a, b, eps);

    cout << endl;
    cout << "Найденный корень уравнения: " << root << " с точностью " << eps << endl;

    return 0;
}