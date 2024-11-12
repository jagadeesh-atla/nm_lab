#include <bits/stdc++.h>

using namespace std;

class Integration {
public:
    vector<double> x, y;
    int n;
    function<double(double)> f;
    
    double x0, xn, h;
    
    Integration(int n, auto f, double x0, double xn) : n(n), f(f), x0(x0), xn(xn) {
        recalc();
    }
    
    void recalc() {
        h = (xn - x0) / n;
        x.resize(n + 1), y.resize(n + 1);
        
        x[0] = x0, y[0] = f(x0);
        for (int i = 1; i <= n; i++) {
            x[i] = x[i - 1] + h;
            y[i] = f(x[i]);
        }
    }
    
    void run(double x0, double xn) {
        x0 = x0, xn = xn;
        recalc(); run();
    }
    
    void run() {
        cout << "Solution by Trapizodial     : " << Trapi()   << "\n";
		cout << "Solution by Simphson's 1/3rd: " << Simp1_3() << "\n";
		cout << "Solution by Simphson's 3/8rd: " << Simp3_8() << "\n";
		cout << "-------------------------------------------------\n";
    }
    
    double Trapi() {
        double sum = 0;
        for (int i = 1; i < n; i++) sum += y[i];
        double ans = (y[0] + y[n] + 2 * sum) * h * 0.5;
        return ans;
    }
    
    double Simp1_3() { 
        double sum = 0, sum1 = 0, ans = 0;
        for (int i = 1; i < n; i++) {
            sum += y[i];
            if (i % 2 == 0) sum -= y[i], sum1 += y[i];
        }
        ans = (y[0] + y[n] + 2 * sum1 + 4 * sum) * h * 0.33333333;
        return ans;
    }
    
    double Simp3_8() {
        double sum = 0, sum1 = 0, ans = 0;
        for (int i = 1; i < n; i++) {
            sum += y[i];
            if (i % 3 == 0) sum -= y[i], sum1 += y[i];
        }
        ans = (y[0] + y[n] + 2 * sum1 + 3 * sum) * 3 * h * 0.125;
        return ans;
    }
};

int main() {
    auto ans = Integration(6, [](double x) { return 1 / (16 + x * x); }, 0, 2).run();
}