#include <iostream>
#include <cmath>

using namespace std;

double f1(double x) {
    return pow(x, 2);
}

double f2(double x) {
    return x * sin(pow(x, 2));
}

double int_trap(double a, double b, double eps) {
    int n = 1;
    double h = (b - a) / n;
    double int_prev = 0.0;
    double int_curr = h * (f1(a) + f1(b)) / 2.0;

    while (abs(int_curr - int_prev) > eps) {
        int_prev = int_curr;
        double sum = 0.0;

        for (int i = 1; i <= n; i++) {
            double x = a + i * h;
            sum += f1(x);
        }

        int_curr = (int_prev + h * sum) / 2.0;
        n *= 2;
        h /= 2.0;
    }

    cout << "n = " << n << endl;

    return int_curr;
}

int main() {
    double a, b, eps;

    a = 1;
    b = 3;
    eps = 1e-6;

    cout << "a = " << a << ", b = " << b << ", eps = " << eps << endl;
    cout << "Значение интеграла: " << int_trap(a, b, eps) << endl;

    return 0;
}
