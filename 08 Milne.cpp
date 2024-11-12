#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100;
double x[MAX_N], y[MAX_N];

const int pres = 12;
const double eps = pow(10, -pres);
const double h = 0.5;

inline double f(double x, double y) { return (x + y) / 2.0; }
inline double f(int i) { return f(x[i], y[i]); }

double milne(int i) {
    x[i + 1] = x[i] + h;
    y[i + 1] = y[i - 3] + (4 * h / 3.0) * (2 * f(i - 2) - f(i - 1) + 2 * f(i));
    
    double y_c = 0;
    cout << "Iterations: ";
    int cnt = 1;
    do {
        cout << cnt++ << ' ';
        
        y_c = y[i - 1] + (h / 3.0) * (f(i - 1) + 4 * f(i) + f(i + 1));
        if (abs(y_c - y[i + 1]) < eps) break;
        y[i + 1] = y_c;
    } while(1);
    
    cout << '\n';
    return y[i + 1];
}

int main() {
    cout << "RK\n";
    
    auto RK = [](double x0, double y0) {
        x[0] = x0, y[0] = y0;
        for (int i = 1; i <= 3; i++) {
            double K1 = h * f(x0, y0);
            double K2 = h * f(x0 + h / 2.0, y0 + K1 / 2.0);
            double K3 = h * f(x0 + h / 2.0, y0 + K2 / 2.0);
            double K4 = h * f(x0 + h, y0 + K3);
            
            double K  = (K1 + 2.0 * (K2 + K3) + K4) / 6.0;
            
            x0 += h, y0 += K;
            x[i] = x0, y[i] = y0;
        }
    };
    
    RK(0, 2);
    milne(3);
    
    cout << fixed << setprecision(pres);
    for (int i = 0; i < 5; ++i) cout << x[i] << " : " << y[i] << '\n';
}