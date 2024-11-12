#include <bits/stdc++.h>

using namespace std;

double det(vector<vector<double>> mat) {
    int n = mat.size();
    if (n == 1) return mat[0][0];
    if (n == 2) return mat[0][0] * mat[1][1] - mat[1][0] * mat[0][1];
    
    double ans = 0;
    for (int x = 0; x < n; ++x) {
        vector sub_mat(n - 1, vector(n - 1, 0.0));
        
        for (int i = 1, s_i = 0, i < n; i++, s_i++) {
            for (int j = 0, s_j = 0; j < n; j++) {
                if (j == x) continue;
                sub_mat[s_i][s_j++] = mat[i][j];
                s_j += 1;
            }
        }
        
        ans += pow(-1, x) * mat[0][x] * det(sub_mat);
    }
    
    return ans;
}

int main() {
    return 0;
}