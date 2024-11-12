#include <bits/stdc++.h>

using namespace std;

struct Point {
    double x, y;
    Point(double a = 0, double b = 0) : x(a), y(b) {}
    Point operator+(Point& b) { return Point(x + b.x, y + b.y); }
    static double abs(Point& a, Point &b) {
        double dx = a.x - b.x, dy = a.y - b.y;
        return dx * dx + dy * dy;
    }
};
// using Point;

struct Matrix {
    int n;
    vector<vector<double>> mat;

    Matrix(int _n) : n(_n) { mat.assign(n, vector<double>(n, 0.0)); }
    Matrix(const vector<vector<double>>& _mat) : n(_mat.size()), mat(_mat) {}
    double& at(int i, int j) { return mat[i][j]; }

    Matrix operator*(Matrix& oth) {
        Matrix result(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                    result.at(i, j) += mat[i][k] * oth.at(k, j);
        return result;
    }

    double det() {
        double det = 1.0;
        auto a = mat;

        for (int i = 0; i < n; i++) {
            int pivot = i;
            for (int j = i + 1; j < n; j++) {
                if (abs(a[j][i]) > abs(a[pivot][i])) pivot = j;
            }

            if (abs(a[pivot][i]) < 1e-9) return 0;  // Singular matrix

            if (pivot != i) {
                swap(a[i], a[pivot]);
                det *= -1;
            }

            det *= a[i][i];
            for (int j = i + 1; j < n; j++) {
                double factor = a[j][i] / a[i][i];
                for (int k = i + 1; k < n; k++) {
                    a[j][k] -= factor * a[i][k];
                }
            }
        }

        return det;
    }

    Matrix inverse() {
        Matrix inv(n);
        auto a = mat;

        // Initialize inv as the identity matrix
        for (int i = 0; i < n; i++) inv.at(i, i) = 1.0;

        // Perform Gaussian elimination
        for (int i = 0; i < n; i++) {
            int pivot = i;
            for (int j = i + 1; j < n; j++) {
                if (abs(a[j][i]) > abs(a[pivot][i])) pivot = j;
            }

            if (abs(a[pivot][i]) < 1e-9) throw runtime_error("Matrix is singular and cannot be inverted");

            if (pivot != i) {
                swap(a[i], a[pivot]);
                swap(inv.mat[i], inv.mat[pivot]);
            }

            double pivot_val = a[i][i];
            for (int j = 0; j < n; j++) {
                a[i][j] /= pivot_val;
                inv.at(i, j) /= pivot_val;
            }

            for (int j = 0; j < n; j++) {
                if (j == i) continue;
                double factor = a[j][i];
                for (int k = 0; k < n; k++) {
                    a[j][k] -= factor * a[i][k];
                    inv.at(j, k) -= factor * inv.at(i, k);
                }
            }
        }

        return inv;
    }
    
    void print() const {
        for (auto &row : mat) {
            for (auto &val : row) cout << setw(10) << setprecision(4) << val << ' ';
            cout << endl;
        }
    }
};
// using Matrix;

class NR {
public:
	function<double(Point)> f, g, dfx, dfy, dgx, dgy;
	double e;
	Point x0;

	NR() {}
	
	void run() {
		
		int iters = 0;
		
		Point p = x0, p_p;
		
		do{
			p_p = p;
			
			iters += 1;
			
			double d  = Matrix({{dfx(p_p), dfy(p_p)}, {dgx(p_p), dgy(p_p)}}).det();
			double dx = Matrix({{f(p_p), dfy(p_p)}, {g(p_p), dgy(p_p)}}).det();
			double dy = Matrix({{dfx(p_p), f(p_p)}, {dgx(p_p), g(p_p)}}).det();
			
			Point inc(-dx / d, -dy / d);
			
			p = p_p + inc;			
		} while (Point::abs(p, p_p) > e and iters < 300);
		
		cout << "Solution is " << fixed << p.x << " " << p.y << endl;	
		cout << "In " << iters << " Iterations.\n";	
	}
	
};

int main(void) {
	NR s;
	
	s.x0 = {0, 0};
	s.e = 0.0001;
	s.f = [](Point a) {
		double x = a.x, y = a.y;
		return x * x + y - 11;
	};
	
	s.g = [](Point a) {
		double x = a.x, y = a.y;
		return y * y + x - 7;
	};
	
	s.dfx = [](Point a) {
		double x = a.x, y = a.y;
		return 2 * x;
	};
	
	s.dfy = [](Point a) {
		double x = a.x, y = a.y;
		return 1;
	};
	
	s.dgx = [](Point a) {
		double x = a.x, y = a.y;
		return 1;
	};
	
	s.dgy = [](Point a) {
		double x = a.x, y = a.y;
		return 2 * y;
	};
	
	s.run();	
}