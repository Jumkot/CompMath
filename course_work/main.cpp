#include <iostream>
#include <fstream>

#define ALPHA_E 0.999
#define ALPHA_I 0.999
#define K 0.042
#define MU 0.0188
#define BETA 0.999
#define RO 0.952
#define E0 99
#define R0 24
#define C 1

using namespace std;

int population(double S, double E, double I, double R, double D)
{
    return S + E + I + R + D;
}

double dS_dt(double N, double S, double E, double I)
{
    return -C * (ALPHA_I * S * I + ALPHA_E * S * E) / N;
}

double dE_dt(double N, double S, double E, double I)
{
    return C * (ALPHA_I * S * I + ALPHA_E * S * E) / N - (K + RO) * E;
}

double dI_dt(double E, double I)
{
    return K * E - BETA * I - MU * I;
}

double dR_dt(double E, double I)
{
    return BETA * I + RO * E;
}

double dD_dt(double I)
{
    return MU * I;
}

double euler_SEIRD(double S, double E, double I, double R, double D, int n, double h)
{
    double s = S, e = E, i = I, r = R, d = D;
    double si, ei, ii, ri, di;
    double s1, e1, i1;

    for (int k = 0; k < n; k++)
    {
        int N = population(s, e, i, r, d);

        s1 = S + h * dS_dt(N, s, e, i);
        e1 = E + h * dE_dt(N, s, e, i);
        i1 = I + h * dI_dt(e, i);
        
        s = S + (h / 2) * (dS_dt(N, S, E, I) + dS_dt(N, s1, e1, i1));
        e = E + (h / 2) * (dE_dt(N, S, E, I) + dE_dt(N, s1, e1, i1));
        i = i + (h / 2) * (dI_dt(E, I) + dI_dt(e1, i1));
        r = R + (h / 2) * (dR_dt(E, I) + dR_dt(e1, i1));
        d = D + (h / 2) * (dD_dt(I) + dD_dt(i1));
        
        S = s;
        E = e;
        I = i;
        R = r;
        D = d;
    }
    
    return K * e / 0.58;
}

int main()
{
    double h = 1;

    double S = 2798047;
    double E = E0;
    double I = 0;
    double R = R0;
    double D = 0;

    ofstream fout;
    
    fout.open("file.txt");

    for (int k = 0; k < 100; k++)
    {
        fout << euler_SEIRD(S, E, I, R, D, k, h) << endl;
    }

    fout.close();

    return 0;
}