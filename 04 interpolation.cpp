#include <bits/stdc++.h>

using namespace std;

struct Point { 
    double x, y;
    Point(double _x = 0, double _y = 0) : x(_x), y(_y) {}
};

class Interpolation {
public:
    int n; vector<Point> values;
    
    Interpolation(vector<Point> values) : n(values.size()), values(values) {}
    
    double f(double x) {
        double ans = 0;
        
        for (int i = 0; i < n; i++) {
            auto [xi, yi] = values[i];
            double num = 1, dem = 1;
            
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                auto [xj, _] = values[j];
                num *= (x - xj);
                dem *= (xi - xj);
            }
            
            ans += (num * yi) / dem;
        }
        
        return ans;
    }
};


int main() {
    int n; cin >> n;
    
    vector<Point> points(n);
    for (auto& [x, y] : points) cin >> x >> y;
    
    Interpolation solver(points);
    
    int x; cin >> x;
    cout << solver.f(x) << '\n';
}

/*
4
0 1
1 2.25
2 3.75
3 4.25
1.25

6
1980 440
1985 510
1990 525
1995 571
2000 500
2005 600
1998

4
5 12
6 13
9 14
11 16
10
*/