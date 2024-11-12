#include <bits/stdc++.h>

using namespace std;

int main() {
    double h = 0.1;
    
    auto RK = [h](double x0, double y0, double x, auto f) {
        while (x0 < x) {
            double K1 = h * f(x0, y0);
            double K2 = h * f(x0 + h / 2.0, y0 + K1 / 2.0);
            double K3 = h * f(x0 + h / 2.0, y0 + K2 / 2.0);
            double K4 = h * f(x0 + h, y0 + K3);
            
            double K  = (K1 + 2.0 * (K2 + K3) + K4) / 6.0;
            
            cout << fixed << setprecision(6);
            cout << x0 + h << " : " << y0 + K << "\n";
            
            x0 += h, y0 += K;
        }
    };
    
    cout << "Runge Kutta Method: \n"; RK(0, 1, 0.2, [](double x, double y){ return x + y * y; });
    
    auto Euler = [h](double x0, double y0, double x, auto f) {
        while (x0 < x) {
            double K = h * f(x0, y0);
            
            cout << fixed << setprecision(6);
            cout << x0 + h << " : " << y0 + K << "\n";
            
            x0 += h, y0 += K;
        }
    };
    
    cout << "Euler Method: \n"; Euler(0, 1, 0.2, [](double x, double y){ return x + y * y; });

    auto Modif_Euler = [h](double x0, double y0, double x, auto f) {
        while (x0 < x) {
            double y_i = y0 + h * f(x0, y0);
            double y_prev;
            
            do {
                y_prev = y_i;
                double mean_slope = (f(x0, y0) + f(x0 + h, y_i)) / 2.0;
                y_i = y0 + h * mean_slope;
                
                cout << y_i << ' ';
            } while (abs(y_i - y_prev) >= 1e-6);
            
            x0 += h, y0 = y_i;
            
            cout << "\nx : " << x0 << "; y : " << y0 << "\n";
            cout << "-----------------------------------\n";
        }
    };
    
    cout << "Modif_Euler: \n"; Modif_Euler(0, 1, 0.2, [](double x, double y){ return x + y * y; });
}