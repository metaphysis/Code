// Spanning Trees in a Secure Lock Pattern
// UVa ID: 12688
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
// https://blog.csdn.net/metaphysis/article/details/163173684

#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using boost::multiprecision::cpp_int;

// Bareiss 算法计算整数矩阵的行列式（精确）
cpp_int determinantBareiss(vector<vector<cpp_int>> a) {
    int n = (int)a.size();
    if (n == 0) return 1;
    if (n == 1) return a[0][0];

    cpp_int sign = 1;
    cpp_int prev = 1; // 相当于 a[-1][-1]

    for (int k = 0; k < n - 1; ++k) {
        // 选主元，若主元为零则交换行
        if (a[k][k] == 0) {
            int swapRow = -1;
            for (int i = k + 1; i < n; ++i) {
                if (a[i][k] != 0) { swapRow = i; break; }
            }
            if (swapRow == -1) return 0; // 奇异矩阵
            std::swap(a[k], a[swapRow]);
            sign = -sign;
        }

        cpp_int pivot = a[k][k];

        // 更新子矩阵
        for (int i = k + 1; i < n; ++i) {
            for (int j = k + 1; j < n; ++j) {
                a[i][j] = (a[i][j] * pivot - a[i][k] * a[k][j]) / prev;
            }
        }
        prev = pivot;
    }

    return sign * a[n - 1][n - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    while (N--) {
        int m;
        cin >> m;
        int n = m * m;

        // 8 个方向向量
        const int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
        const int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

        vector<int> deg(n, 0);
        vector<vector<int>> adj(n);

        // 建图
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < m; ++c) {
                int id = r * m + c;
                for (int d = 0; d < 8; ++d) {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (nr >= 0 && nr < m && nc >= 0 && nc < m) {
                        int nid = nr * m + nc;
                        adj[id].push_back(nid);
                    }
                }
                deg[id] = (int)adj[id].size();
            }
        }

        // 构造拉普拉斯矩阵 L (n x n)
        vector<vector<cpp_int>> L(n, vector<cpp_int>(n, 0));
        for (int i = 0; i < n; ++i) {
            L[i][i] = deg[i];
            for (int j : adj[i]) {
                L[i][j] = -1; // 无向边，对称位置也会由对方设置
            }
        }

        // 删除最后一行一列，得到余子式矩阵 A (n-1 x n-1)
        int sz = n - 1;
        vector<vector<cpp_int>> A(sz, vector<cpp_int>(sz));
        for (int i = 0; i < sz; ++i)
            for (int j = 0; j < sz; ++j)
                A[i][j] = L[i][j];

        cpp_int ans = determinantBareiss(A);
        cout << ans << '\n';
    }

    return 0;
}
