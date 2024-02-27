#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;

class Rational
{
public:
    int numerator_;
    int denominator_;

    Rational(int numerator = 0, int denominator = 1) : numerator_(numerator), denominator_(denominator){};

    void add(Rational rational)
    {
        numerator_ = numerator_ * rational.denominator_ + rational.numerator_ * denominator_;
        denominator_ *= rational.denominator_;
        GCD_rat();
    }

    void sub(Rational rational)
    {
        numerator_ = numerator_ * rational.denominator_ - rational.numerator_ * denominator_;
        denominator_ *= rational.denominator_;
        GCD_rat();
    }

    void mul(Rational rational)
    {
        numerator_ *= rational.numerator_;
        denominator_ *= rational.denominator_;
        GCD_rat();
    }

    void div(Rational rational)
    {
        numerator_ *= rational.denominator_;
        denominator_ *= rational.numerator_;
        GCD_rat();
    }

    Rational abs_r() const
    {
        return Rational(abs(numerator_), abs(denominator_));
    }

    void neg()
    {
        numerator_ = -numerator_;
    }

    void inv()
    {
        swap(numerator_, denominator_);
    }

    void GCD_rat()
    {
        int gcd_r = __gcd(numerator_, denominator_);
        numerator_ = numerator_ / gcd_r;
        denominator_ = denominator_ / gcd_r;
    }

    double to_double() const
    {
        return numerator_ / (double)denominator_;
    }

    Rational &operator+=(const Rational &r_num)
    {
        this->add(r_num);
        return *this;
    }
    Rational &operator+=(int num)
    {
        this->add(Rational(num));
        return *this;
    }

    Rational &operator-=(const Rational &r_num)
    {
        this->sub(r_num);
        return *this;
    }
    Rational &operator-=(int num)
    {
        this->sub(Rational(num));
        return *this;
    }

    Rational &operator*=(const Rational &r_num)
    {
        this->mul(r_num);
        return *this;
    }
    Rational &operator*=(int num)
    {
        this->mul(Rational(num));
        return *this;
    }

    Rational &operator/=(const Rational &r_num)
    {
        this->div(r_num);
        return *this;
    }
    Rational &operator/=(int num)
    {
        this->div(Rational(num));
        return *this;
    }

    Rational operator-() const
    {
        Rational new_num(this->numerator_, this->denominator_);
        new_num.neg();
        return new_num;
    }
    Rational operator+() const
    {
        Rational new_num(this->numerator_, this->denominator_);
        return new_num;
    }

    bool operator==(Rational const &b) const
    {
        return ((this->numerator_ * b.denominator_) == (b.numerator_ * this->denominator_));
    }
    bool operator==(int b) const
    {
        return (this->numerator_ == ((double)b * this->denominator_));
    }

    bool operator!=(Rational const &b) const
    {
        return !(*this == b);
    }
    bool operator!=(int b) const
    {
        Rational rat_b(b);
        return !(*this == rat_b);
    }

    bool operator<(Rational const &b) const
    {
        return ((this->numerator_ / this->denominator_) < (b.numerator_ / b.denominator_));
    }
    bool operator<(int b) const
    {
        return ((this->numerator_ / this->denominator_) < ((double)b));
    }

    bool operator>(Rational const &b) const
    {
        return (b < *this);
    }
    bool operator>(int b) const
    {
        Rational rat_b(b);
        return (rat_b < *this);
    }
};

Rational operator+(Rational n1, Rational n2)
{
    return n1 += n2;
}
Rational operator-(Rational n1, Rational n2)
{
    return n1 -= n2;
}
Rational operator*(Rational n1, Rational n2)
{
    return n1 *= n2;
}
Rational operator/(Rational n1, Rational n2)
{
    return n1 /= n2;
}

class System
{
public:
    Rational **matrix;
    Rational *values;
    int size;

    System()
    {
        try
        {
            string file_path;
            cin >> file_path;
            ifstream file(file_path);
            if (!file.is_open())
            {
                throw runtime_error("Невозможно открыть файл: " + file_path);
            }

            int matrix_size = 0;
            file >> matrix_size;

            size = matrix_size;
            matrix = new Rational *[size];
            for (int i = 0; i < size; ++i)
            {
                matrix[i] = new Rational[size];
            }
            values = new Rational[size];

            char ch;
            for (int i = 0; i < size; ++i)
            {
                for (int j = 0; j < size; ++j)
                {
                    string elem;
                    while (file.get(ch) && (ch != ' '))
                    {
                        elem += ch;
                    }

                    bool flag_elem = false;
                    string elem_num;
                    string elem_den;
                    for (int k = 0; k < strlen(elem.c_str()); ++k)
                    {
                        if (elem[k] == '/')
                        {
                            flag_elem = true;
                            continue;
                        }
                        if (!flag_elem)
                        {
                            elem_num += elem[k];
                        }
                        else
                        {
                            elem_den += elem[k];
                        }
                    }
                    matrix[i][j].numerator_ = atoi(elem_num.c_str());
                    matrix[i][j].denominator_ = atoi(elem_den.c_str());
                }

                while (file.get(ch) && !(isdigit(ch)) && !(ch == '-'))
                {
                    continue;
                }

                string answer;
                answer += ch;
                while (file.get(ch) && (ch != ' '))
                {
                    answer += ch;
                }

                bool flag_answer = false;
                string answer_num;
                string answer_den;
                for (int k = 0; k < strlen(answer.c_str()); ++k)
                {
                    if (answer[k] == '/')
                    {
                        flag_answer = true;
                        continue;
                    }
                    if (!flag_answer)
                    {
                        answer_num += answer[k];
                    }
                    else if (isdigit(answer[k]))
                    {
                        answer_den += answer[k];
                    }
                }
                values[i].numerator_ = atoi(answer_num.c_str());
                values[i].denominator_ = atoi(answer_den.c_str());
            }

            file.close();
        }
        catch (const exception &e)
        {
            cerr << "Ошибка чтения файла: " << e.what() << endl;
        }
    }

    ~System()
    {
        for (int i = 0; i < size; ++i)
        {
            delete[] matrix[i];
        }
        delete[] matrix;
        delete[] values;
        matrix = nullptr;
        values = nullptr;
    }

    void print_system()
    {
        if (matrix != nullptr && values != nullptr)
        {
            cout << endl;
            cout << "Матрица:" << endl;
            for (int i = 0; i < size; ++i)
            {
                for (int j = 0; j < size; ++j)
                {
                    cout << matrix[i][j].numerator_ << '/' << matrix[i][j].denominator_ << ' ';
                }
                cout << "= " << values[i].numerator_ << '/' << values[i].denominator_ << endl;
            }
        }
    }

    void print_double()
    {
        if (matrix != nullptr && values != nullptr)
        {
            cout << endl;
            for (int i = 0; i < size; ++i)
            {
                for (int j = 0; j < size; ++j)
                {
                    cout << matrix[i][j].to_double() << ' ';
                }
                cout << "= " << values[i].to_double() << endl;
            }
        }
    }

    void rang_count()
    {
        int rang_s = size;
        int rang_v = size;
        for (int i = 0; i < size; ++i)
        {
            int count = 0;
            for (int j = 0; j < size; ++j)
            {
                if (matrix[i][j].to_double() != 0)
                {
                    count++;
                }
            }
            if (count == 0)
            {
                rang_s--;
            }
            if (values[i].to_double() == 0)
            {
                rang_v--;
            }
        }
        if (rang_s != rang_v)
        {
            cout << "Система не имеет решений" << endl;
            exit(0);
        }
        else if (rang_s != size)
        {
            cout << "Система имеет бесконечное множество решений" << endl;
            exit(0);
        }
    }

    void rsly_gauss()
    {
        int i_max, i, j, k;
        Rational matrix_max, c;

        //------------------------
        // Прямой ход
        //------------------------
        for (k = 0; k < size; k++)
        {
            //------------------------
            // Поиск максимального элемента по абсолютной величине
            //------------------------
            i_max = k;
            matrix_max = matrix[k][k].abs_r();
            for (i = k + 1; i < size; i++)
            {
                if (matrix[i][k].abs_r() > matrix_max.abs_r())
                {
                    matrix_max = matrix[i][k].abs_r();
                    i_max = i;
                }
            }

            //------------------------------------
            // Перестановка строк k и i_max
            //------------------------------------
            if (k != i_max)
            {
                for (j = k; j < size; j++)
                {
                    swap(matrix[k][j], matrix[i_max][j]);
                }
                swap(values[k], values[i_max]);
            }
            print_system();

            //------------------------------------
            // Приведение к единичному диагональному виду
            //------------------------------------
            c = matrix[k][k];
            for (j = 0; j < size; j++)
            {
                matrix[k][j] /= c;
            }
            values[k] /= c;

            for (i = k + 1; i < size; i++)
            {
                c = matrix[i][k];
                for (j = 0; j < size; j++)
                {
                    matrix[i][j] -= c * matrix[k][j];
                }
                values[i] -= c * values[k];
                print_system();
                rang_count();
            }
        }
        print_system();
        //--------------------------
        // Обратный ход
        //--------------------------
        for (i = size - 2; i >= 0; i--)
        {
            for (j = i + 1; j < size; j++)
            {
                values[i] -= matrix[i][j] * values[j];
            }
        }
    }
};

int main()
{
    System gauss;
    gauss.print_system();

    gauss.rsly_gauss();

    cout << endl;
    for (int i = 0; i < gauss.size; ++i)
    {
        for (int j = 0; j < gauss.size; ++j)
        {
            cout << gauss.matrix[i][j].to_double() << ' ';
        }
        cout << "= " << gauss.values[i].to_double() << endl;
    }

    gauss.print_double();

    gauss.print_system();

    return 0;
}