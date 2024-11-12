/*

c = 1 dx = 1/3 dt = 1/36 => alpha = 1/4
u(0, t) = 0, u(1, t) = 0. u(x, 0) = 1;

For j = 0:
	10u11 - u21 = 7;
	-u11  + 10u21 = 7;
	
For j = 1:
	10u12 - u22   = 6u11 + u21;
	-u12  + 10u22 = u11 + 6u21;
*/

#include <bits/stdc++.h>
using namespace std;

struct Equation { 
    double a, b, c, d; 
};

struct Solution { 
    double alpha, beta, x; 
};

vector<double> solve_tri_diag(const vector<Equation>& equ) {
    int n = equ.size();
    vector<Solution> sol(n);
    
    // for (auto [a, b, c, d] : equ) 
        // { cout << a << ' ' << b << ' ' << c << ' ' << d << '\n'; }
    
    sol[0].alpha = equ[0].b;
    sol[0].beta  = equ[0].d / equ[0].b;
    
    for (int i = 1; i < n; i++) {
        sol[i].alpha = equ[i].b - (equ[i].a * equ[i - 1].c) / sol[i - 1].alpha;
        sol[i].beta  = (equ[i].d - equ[i].a * sol[i - 1].beta) / sol[i].alpha;
    }
    
    sol[n - 1].x = sol[n - 1].beta;
    for (int i = n - 2; i >= 0; i--) {
        sol[i].x = sol[i].beta - (equ[i].c * sol[i + 1].x) / sol[i].alpha;
    }
    
    vector<double> x;
    for (const auto& s : sol) {
        x.push_back(s.x);
    }
    
    return x;
}

const double c = 1.0;           // Heat equation constant
const double L = 1.0;           // Length of the rod
const double h = 1.0 / 3.0;     // Spatial step size
const double k = 1.0 / 36.0;    // Time step size
const int n = L / h + 1;        // Number of spatial points
const int m = 10;               // Number of time steps
const double alpha = c * k / (h * h);  // Stability factor

vector<double> u;

void print(int step) {
    cout << fixed << setprecision(3);
    cout << "Step " << setw(2) << step << ": ";
    for (double x : u) cout << x << ' ';
    cout << "\n";
}

int main() {
    u.assign(n, 1.0); // Initial temperature distribution across the rod
    u[0] = u[n - 1] = 0; // Boundary conditions

    vector<Equation> equ(n - 2, { -alpha / 2.0, 1.0 + alpha, -alpha / 2.0, 0 });

    print(0); // Print initial condition
    
    for (int j = 1; j <= m; ++j) {
        for (int i = 1; i < n - 1; ++i) {
            equ[i - 1].d = (1.0 - alpha) * u[i] + (alpha / 2.0) * (u[i + 1] + u[i - 1]);
        }

        auto x = solve_tri_diag(equ);
        for (size_t i = 0; i < x.size(); i++) u[1 + i] = x[i];
        u[0] = u[n - 1] = 0; // Re-apply boundary conditions after solving
        
        print(j); // Print the solution at each time step
    }
    
    return 0;
}
