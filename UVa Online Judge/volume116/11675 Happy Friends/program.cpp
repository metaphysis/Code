// Happy Friends
// UVa ID: 11675
// Verdict: Accepted
// Submission Date: 2026-04-26
// UVa Run Time: 0.060s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;

// 矩阵乘法 (方阵)
vector<vector<int>> matMul(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i)
        for (int k = 0; k < n; ++k) if (A[i][k])
            for (int j = 0; j < n; ++j)
                C[i][j] = (C[i][j] + (ll)A[i][k] * B[k][j]) % MOD;
    return C;
}

// 矩阵向量乘法
vector<int> matVecMul(const vector<vector<int>>& M, const vector<int>& v) {
    int n = M.size();
    vector<int> res(n, 0);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            res[i] = (res[i] + (ll)M[i][j] * v[j]) % MOD;
    return res;
}

// 矩阵快速幂
vector<vector<int>> matPow(vector<vector<int>> M, int e) {
    int n = M.size();
    vector<vector<int>> R(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) R[i][i] = 1;
    while (e) {
        if (e & 1) R = matMul(R, M);
        M = matMul(M, M);
        e >>= 1;
    }
    return R;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int T; cin >> T;
    for (int cs = 1; cs <= T; ++cs) {
        int N, M, K, D; cin >> N >> M >> K >> D;
        // 邻接矩阵
        vector<vector<int>> A(N, vector<int>(N, 0));
        for (int i = 0, u, v; i < M; ++i) {
            cin >> u >> v;
            A[u][v] = A[v][u] = 1;
        }
        
        // 初始状态
        vector<int> h(N, 0), inc(N, 0);
        h[K] = inc[K] = 1;
        
        // D = 0 直接输出
        if (D == 0) {
            cout << "Case " << cs << ":";
            for (int x : h) cout << ' ' << x;
            cout << '\n'; continue;
        }
        
        // 第一阶段：模拟到稳定期 (最多 N*10 天)
        int sim = min(D, N * 10);
        bool done = false;
        for (int day = 1; day <= sim; ++day) {
            vector<int> hn = h;
            // 根据 inc 计算下一天的快乐度
            for (int i = 0; i < N; ++i) if (!inc[i]) {
                ll s = 0;
                for (int j = 0; j < N; ++j) if (A[i][j]) s += h[j];
                hn[i] = (h[i] + s) % MOD;
            }
            // 计算下一天的 inc
            vector<int> incn(N, 0);
            for (int i = 0; i < N; ++i) if (hn[i] != h[i]) incn[i] = 1;
            h = hn, inc = incn;
            if (day == D) {
                cout << "Case " << cs << ":";
                for (int x : h) cout << ' ' << x;
                cout << '\n';
                done = true;
                break;
            }
        }
        if (done) continue;
        
        // 第二阶段：构造两天合并矩阵
        auto build = [&](const vector<int>& pat) {
            vector<vector<int>> T(N, vector<int>(N, 0));
            for (int i = 0; i < N; ++i) {
                T[i][i] = 1;                     // 自身保留
                if (!pat[i]) {                   // 该点今天要增长
                    for (int j = 0; j < N; ++j) if (A[i][j])
                        T[i][j] = (T[i][j] + 1) % MOD;
                }
            }
            return T;
        };
        // nxt 是 inc 取反 (明天的模式)
        vector<int> nxt(N);
        for (int i = 0; i < N; ++i) nxt[i] = 1 - inc[i];
        auto M2 = matMul(build(nxt), build(inc));  // 两天合并矩阵
        
        int rem = D - sim, pairs = rem / 2;
        h = matVecMul(matPow(M2, pairs), h);       // 应用 pairs 个两天
        if (rem & 1) {                             // 剩余奇数天，再走一步
            vector<int> hn = h;
            for (int i = 0; i < N; ++i) if (!inc[i]) {
                ll s = 0;
                for (int j = 0; j < N; ++j) if (A[i][j]) s += h[j];
                hn[i] = (h[i] + s) % MOD;
            }
            h = hn;
        }
        
        cout << "Case " << cs << ":";
        for (int x : h) cout << ' ' << x;
        cout << '\n';
    }
    return 0;
}
