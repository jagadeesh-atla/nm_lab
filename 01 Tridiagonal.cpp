#include <bits/stdc++.h>

using namespace std;

struct Equation { double a, b, c, d; };
struct Solution { double alpha, beta, x; };

int main() {
    int n; cin >> n;
    
    vector<Equation> equ(n);
    vector<Solution> sol(n);
    
    for (int i = 0; i < n; i++) {
        if (i != 0) cin >> equ[i].a;
        cin >> equ[i].b;
        if (i != n - 1) cin >> equ[i].c;
        cin >> equ[i].d;
    }
    
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
    
    for (int i = 0; i < n; i++) {
        cout << sol[i].x << ' ';
    }
    cout << '\n';
}

/*
3
3 -1 -5
-1 3 -1 7
-1 3 7
*/