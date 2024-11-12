#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

const int N = 4;
const double TOLERANCE = 1e-3;
const int MAX_ITERATIONS = 10000;
const double H = 1;

double f(double x, double y) { return 10 * (x * x + y * y + 10); }

void printGrid(const vector<vector<double>>& grid) {
    for (const auto& row : grid) {
        for (const auto& val : row) {
            cout << setw(10) << val << " ";
        }
        cout << endl;
    }
    
    cout << "-----------------------------------\n";
}

vector<vector<double>> solveLaplaceJacobi(vector<vector<double>> grid) {
    vector<vector<double>> newGrid(N, vector<double>(N, 0));
    int iterations = 0;
    double maxDiff;

    do {
        iterations++;
        maxDiff = 0.0;

        for (int i = 1; i < N - 1; ++i) {
            for (int j = 1; j < N - 1; ++j) {
                newGrid[i][j] = H * H * f(i, j) * 0.25 + 0.25 * (grid[i + 1][j] + grid[i - 1][j] +
                                         grid[i][j + 1] + grid[i][j - 1]);
            }
        }

        for (int i = 1; i < N - 1; ++i) {
            for (int j = 1; j < N - 1; ++j) {
                maxDiff = max(maxDiff, abs(newGrid[i][j] - grid[i][j]));
                grid[i][j] = newGrid[i][j];
            }
        }

        if (iterations >= MAX_ITERATIONS) break;

    } while (maxDiff > TOLERANCE);
    
    cout << "No of Iterations : " << iterations << "\n";

    return grid;
}

void solveLaplaceGaussSeidel(vector<vector<double>>& grid) {
    int iterations = 0;
    double maxDiff;

    do {
        iterations++;
        maxDiff = 0.0;

        for (int i = 1; i < N - 1; ++i) {
            for (int j = 1; j < N - 1; ++j) {
                double oldValue = grid[i][j];
                grid[i][j] = H * H * f(i, j) * 0.25 + 0.25 * (grid[i + 1][j] + grid[i - 1][j] +
                                     grid[i][j + 1] + grid[i][j - 1]);
                maxDiff = max(maxDiff, abs(grid[i][j] - oldValue));
            }
        }

        if (iterations >= MAX_ITERATIONS) break;

    } while (maxDiff > TOLERANCE);
    
    cout << "No of Iterations : " << iterations << "\n";
}

int main() {
    vector<vector<double>> grid(N, vector<double>(N, 0));

	for (int i = 1; i < N - 1; i++) for (int j = 1; j < N - 1; ++j)
		grid[i][j] = f(i, j);

    cout << "Initial Grid:" << endl;
    printGrid(grid);

    auto jacobi = solveLaplaceJacobi(grid);
    cout << "Jacobi Method:" << endl;
    printGrid(jacobi);

    solveLaplaceGaussSeidel(grid);
    cout << "Gauss-Seidel Method:" << endl;
    printGrid(grid);

    return 0;
}
