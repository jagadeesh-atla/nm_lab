#include <bits/stdc++.h>

using namespace std;

double f(double x, double y) {
    return 1 / (x +  y);
}

double a = 1, b = 2, c = 1, d = 2;
const int n = 6, m = 6;

double h = (b - a) / n;
double k = (d - c) / m;

double table[n + 10][m + 10];

enum Values {
    CORNER, EDGE, CENTER, REST
};

int coeff(int i, int j) {
    if (i == 0 or i == n) {
        if (j == 0 or j == m) return CORNER;
        else return EDGE;
    }
    return REST;
}

double trapi() {
    double ans = 0;
    
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            switch(coeff(i, j)) {
                case CORNER: ans += 1 * table[i][j]; break;
                case EDGE  : ans += 2 * table[i][j]; break;
                case REST  : ans += 4 * table[i][j]; break;
                default    : break;
            }
        }
    }
    
    ans *= h * k;
    ans *= 0.25;
    return ans;
}

double simp1_3() {
    double ans = 0;
    
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            switch(coeff(i, j)) {
                case CORNER: ans += 1  * table[i][j]; break;
                case EDGE  : {
                    if (i % 2 and j % 2) ans += 2 * table[i][j];
                    else ans += 4 * table[i][j];
                    break;
                }
                case REST  : {
                    if (i % 2 and j % 2) ans += 4 * table[i][j];
                    else if (i % 2 == 0 and j % 2 == 0) ans += 16 * table[i][j];
                    else ans += 8 * table[i][j];
                    break;
                }
                default    : break;
            }
        }
    }
    
    ans *= h * k;
    ans /= 9.0;
    return ans;
}

double simp3_8() {
    double ans = 0;
    
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            switch(coeff(i, j)) {
                case CORNER: ans += 1 * table[i][j]; break;
                case EDGE  : {
                    if (i % 3 == 0 or j % 3 == 0) ans += 3 * table[i][j];
                    else ans += 2 * table[i][j];
                    break;
                }
                case REST  : {
                    if (i % 3 == 0 and j % 3 == 0) ans += 27 * table[i][j];
                    else if (i % 3 == 0 or j % 3 == 0) ans += 6 * table[i][j];
                    else ans += 4 * table[i][j];
                    break;
                }
                default    : break;
            }
        }
    }
    
    ans *= 9 * h * k;
    ans /= 64.0;
    return ans;
}

int main() {
    for (int i = 0; i <= n; i++) for (int j = 0; j <= m; j++) 
        table[i][j] = f(a + i * h, c + j * k);
    
    cout << trapi()   << "\n";
    cout << simp1_3() << "\n";
    cout << simp3_8() << "\n";
}
