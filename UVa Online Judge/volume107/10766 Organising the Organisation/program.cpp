// Organising the Organisation
// UVa ID: 10766
// Verdict: Accepted
// Submission Date: 2025-10-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// 使用辗转相除法的高斯消元计算整数行列式
ll det(vector<vector<ll>> matrix) {
    int n = matrix.size();
    ll res = 1;
    
    for (int i = 0; i < n; i++) {
        // 寻找主元
        int pivot = i;
        for (int j = i + 1; j < n; j++) {
            if (abs(matrix[j][i]) > abs(matrix[pivot][i])) {
                pivot = j;
            }
        }
        if (pivot != i) {
            swap(matrix[i], matrix[pivot]);
            res = -res;
        }
        
        if (matrix[i][i] == 0) {
            return 0;
        }
        
        // 消去下方行
        for (int j = i + 1; j < n; j++) {
            while (matrix[j][i] != 0) {
                // 使用辗转相除法
                ll ratio = matrix[j][i] / matrix[i][i];
                for (int k = i; k < n; k++) {
                    matrix[j][k] -= ratio * matrix[i][k];
                }
                
                if (matrix[j][i] != 0) {
                    swap(matrix[i], matrix[j]);
                    res = -res;
                }
            }
        }
        
        res *= matrix[i][i];
    }
    
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    while (cin >> n >> m >> k) {
        vector<vector<bool>> forbidden(n, vector<bool>(n, false));
        
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            forbidden[a][b] = true;
            forbidden[b][a] = true;
        }

        // 构建拉普拉斯矩阵
        vector<vector<ll>> L(n, vector<ll>(n, 0));
        for (int i = 0; i < n; i++) {
            int deg = 0;
            for (int j = 0; j < n; j++) {
                if (i != j && !forbidden[i][j]) {
                    L[i][j] = -1;
                    deg++;
                }
            }
            L[i][i] = deg;
        }

        // 删除第 k-1 行和列
        if (n == 1) {
            cout << "1\n";
            continue;
        }
        
        vector<vector<ll>> minor;
        for (int i = 0; i < n; i++) {
            if (i == k - 1) continue;
            vector<ll> row;
            for (int j = 0; j < n; j++) {
                if (j == k - 1) continue;
                row.push_back(L[i][j]);
            }
            minor.push_back(row);
        }

        ll ans = det(minor);
        cout << ans << "\n";
    }

    return 0;
}
