#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

double C(double x, int N, int k, vector<double>& x_nums)
{
    double num = 1;
    for (int i = 0; i <= N; i++) {
        if (i == k)
            continue;
        num *= (x - x_nums[i]) / (x_nums[k] - x_nums[i]);
    }

    return num;
}

double L(int N, double x, vector<double>& x_nums, vector<double>& y_nums)
{
    double num = 0;
    for (int i = 0; i <= N; i++) {
        num += C(x, N, i, x_nums) * y_nums[i];
    }

    return num;
}

int main(int argc, char* argv[])
{
    fstream file(argv[1]);

    vector<double> x_nums;
    vector<double> y_nums;

    string line;
    double num;

    getline(file, line);
    stringstream stream(line);
    while (stream >> num)
    {    
        x_nums.push_back(num);
    }
    getline(file, line);
    stream.clear();

    stream.str(line);
    while (stream >> num)
    {    
        y_nums.push_back(num);
    }

    int N = x_nums.size() - 1;

    cout << "Значение полинома L(x) для x = " << stod(argv[2]);
    cout << ": " << L(N, stod(argv[2]), x_nums, y_nums) << endl;

    stream.str("");
    stream.clear();
    cout << stream.str();
    
    return 0;
}