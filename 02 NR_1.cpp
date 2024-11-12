#include <bits/stdc++.h>

using namespace std;

class NR {
private:
    function<double(double)> f, df;
    double x0, e;
    
public:
    NR(function<double(double)> _f, function<double(double)> _df, double _x0, double _e) {
        f = _f, df = _df, x0 = _x0, e = _e;
    }
    
    void run() {
        int iters = 1;
        
        double x = x0, x_p;
        do {
            iters += 1;
            
            x_p = x;
            
            if (df(x_p) < 1e-6) break; 
            
            x = x_p - f(x_p) / df(x_p);
        } while (abs(x_p - x) > e);
        
        cout << fixed << x << '\n';
    }
};

int main() {
    NR prob1(
        [](double x) { return pow(x, 3) + 5 * x - 3; },
        [](double x) { return 3 * pow(x, 2) + 5; },
        0, 1e-6);
        
    prob1.run();
}