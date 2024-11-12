#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

const int N = 4;
const double TOLERANCE = 1e-3;
const int MAX_ITERATIONS = 10000;

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
                newGrid[i][j] = 0.25 * (grid[i + 1][j] + grid[i - 1][j] +
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
                grid[i][j] = 0.25 * (grid[i + 1][j] + grid[i - 1][j] +
                                     grid[i][j + 1] + grid[i][j - 1]);
                maxDiff = max(maxDiff, abs(grid[i][j] - oldValue));
            }
        }

        if (iterations >= MAX_ITERATIONS) break;

    } while (maxDiff > TOLERANCE);
}

int main() {
    vector<vector<double>> grid(N, vector<double>(N, 0));

    grid[0][0] = 1000; grid[0][1] = 1000; grid[0][2] = 1000; grid[0][3] = 1000;
    grid[1][0] = 2000; grid[1][3] = 500; 
    grid[2][0] = 2000; grid[2][3] = 0; 
    grid[3][0] = 1000; grid[3][1] = 500; grid[3][2] = 0; grid[3][3] = 0;

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
