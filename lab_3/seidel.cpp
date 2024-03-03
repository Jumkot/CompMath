#include <iostream>
#include <cmath>
#include <fstream>
#include <cstring>
#include <algorithm>

const int MAX_ITERATIONS = 1000;
const double EPS = 1e-6;

using namespace std;


void print_system(double** matrix,  double *values, int size)
{
    if (matrix != nullptr && values != nullptr)
    {
        cout << endl;
        cout << "Матрица:" << endl;
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                cout << matrix[i][j] << ' ';
            }
            cout << "= " << values[i] << endl;
        }
    }
}

void rsly_seidel(double** matrix,  double *values, double *x, int size)
{
    int d = 0;
    for (int i = 0; i < size; ++i)
    {
        //------------------------------------
        // Перестановка строк так, чтобы максимальные элементы оказались на главной диагонали
        //------------------------------------
        double row_max = matrix[i][d];
        for (int j = 0; j < size; ++j)
        {
            if (abs(matrix[i][j]) > abs(row_max))
            {
                for (int k = 0; k < size; ++k)
                {
                    swap(matrix[j][k], matrix[d][k]);
                }
                swap(values[j], values[d]);
            }
        }
        d++;
    }
    print_system(matrix, values, size);
    cout << endl;

    for (int i = 0; i < size; ++i)
    {
        double row_max = 0.0;
        double sum = 0.0;
        for (int j = 0; j < size; ++j)
        {
            sum += abs(matrix[i][j]);
            if (abs(row_max) < abs(matrix[i][j]))
            {
                row_max = abs(matrix[i][j]);
            }
        }
        sum -= abs(row_max);

        if ((row_max < (sum)) || (row_max == (sum))) {
            cout << "Система не сходится" << endl;
            exit(0);
        }
    }
    //------------------------------------
    // Учитываем значения x "выше", полученные в этой же итерации
    //------------------------------------
    double x_new[size];

    for (int k = 0; k < MAX_ITERATIONS; ++k)
    {
        //------------------------------------
        // Обновление итерационных значений построчно
        //------------------------------------
        for (int i = 0; i < size; ++i)
        {
            double sum1 = 0.0;
            double sum2 = 0.0;

            for (int j = 0; j < i; ++j)
            {
                sum1 += matrix[i][j] * x_new[j];
            }

            for (int j = i + 1; j < size; ++j)
            {
                sum2 += matrix[i][j] * x[j];
            }

            x_new[i] = (values[i] - sum1 - sum2) / matrix[i][i];
        }

        //------------------------------------
        // Вывод итерации и её результатов
        //------------------------------------
        cout << "Итерация " << k << ":" << endl;
        for (int j = 0; j < size; ++j)
        {
            cout << "x[" << j << "] = " << x_new[j] << endl;
        }
        cout << endl;

        //------------------------------------
        // Проверка на достижение точности
        //------------------------------------
        double error = 0.0;
        for (int i = 0; i < size; ++i)
        {
            double tmp = x_new[i] - x[i];
            error += pow(tmp, 2);
        }
        if (sqrt(error) < EPS)
        {
            break;
        }
        //------------------------------------
        // Обновление значений x для следующей итерации
        //------------------------------------
        for (int i = 0; i < size; ++i)
        {
            x[i] = x_new[i];
        }
    }
};

int main()
{
    const int size = 3;
    double** matrix = new double*[size];
    for (int i = 0; i < size; ++i)
    {
        matrix[i] = new double[size];
    }

    // matrix[0][0] = -17;
    // matrix[0][1] = 3;
    // matrix[0][2] = 5;

    // matrix[2][0] = 5;
    // matrix[2][1] = 7;
    // matrix[2][2] = -1;

    // matrix[1][0] = 1;
    // matrix[1][1] = -1;
    // matrix[1][2] = -3;

    // double *values = new double[size];
    // values[0] = 4;
    // values[2] = 16;
    // values[1] = -10;

    // matrix[0][0] = 2;
    // matrix[0][1] = -1;
    // matrix[0][2] = 5;

    // matrix[2][0] = 1;
    // matrix[2][1] = -4;
    // matrix[2][2] = 2;

    // matrix[1][0] = 5;
    // matrix[1][1] = -1;
    // matrix[1][2] = 3;

    // double *values = new double[size];
    // values[0] = 10;
    // values[2] = 20;
    // values[1] = 5;

    // double *x = new double[size];
    // x[0] = 0;
    // x[1] = 0;
    // x[2] = 0;

    matrix[0][0] = 7;
    matrix[0][1] = 4;
    matrix[0][2] = -1;

    matrix[2][0] = 2;
    matrix[2][1] = 3;
    matrix[2][2] = -6;

    matrix[1][0] = 8;
    matrix[1][1] = -10;
    matrix[1][2] = 1;

    double *values = new double[size];
    values[0] = 12;
    values[2] = -10;
    values[1] = -9;

    double *x = new double[size];
    x[0] = 0;
    x[1] = 0;
    x[2] = 0;

    print_system(matrix, values, size);

    // for (int i = 0; i < size; ++i)
    // {
    //     for (int j = 0; j < size; ++j)
    //     {
    //         cin >> matrix[i][j];
    //     }
    // }

    // for (int i = 0; i < size; ++i)
    // {
    //     for (int j = 0; j < size; ++j)
    //     {
    //         cout << matrix[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    rsly_seidel(matrix, values, x, size);

    cout << "Итоговые значения (double):" << endl;
    for (int i = 0; i < size; ++i)
    {
        cout << "x[" << i << "] = " << x[i] << endl;
    }

    return 0;
}
