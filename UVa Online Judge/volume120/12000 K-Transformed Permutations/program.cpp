// K-Transformed Permutations
// UVa ID: 12000
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.010s
// https://blog.csdn.net/metaphysis/article/details/163173613

#include <bits/stdc++.h>
using namespace std;

const int MOD = 73405;
const int MAXLOG = 60; // 2^60 > 1e9

// 矩阵乘法 (A * B)
vector<vector<int>> matMul(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k) {
            if (A[i][k] == 0) continue;
            long long aik = A[i][k];
            for (int j = 0; j < n; ++j) {
                C[i][j] = (C[i][j] + aik * B[k][j]) % MOD;
            }
        }
    }
    return C;
}

// 向量乘矩阵 (v_new = M * v)
vector<int> vecMul(const vector<vector<int>>& M, const vector<int>& v) {
    int n = M.size();
    vector<int> res(n, 0);
    for (int i = 0; i < n; ++i) {
        long long sum = 0;
        for (int j = 0; j < n; ++j) {
            sum += 1LL * M[i][j] * v[j];
            if (sum >= (1LL << 62)) sum %= MOD; // 防止溢出
        }
        res[i] = sum % MOD;
    }
    return res;
}

// 构建普通矩阵 M 和特殊矩阵 Ms，并将 M 的二进制幂存入 powM
void buildMatrices(int K, vector<vector<int>>& M, vector<vector<int>>& Ms,
                   vector<vector<vector<int>>>& powM) {
    int width = 2 * K + 1;
    int S = 1 << width;
    int full = S - 1;
    M.assign(S, vector<int>(S, 0));
    Ms.assign(S, vector<int>(S, 0));
    for (int old = 0; old < S; ++old) {
        // ---------- 普通矩阵 (新增位为0) ----------
        if ((old & 1) == 0) { // 必须选位0
            int newMask = old >> 1; // 右移，最高位补0
            M[newMask][old] = (M[newMask][old] + 1) % MOD;
        } else { // 位0已放置，可选其他未放置位
            for (int b = 1; b <= 2 * K; ++b) {
                if (((old >> b) & 1) == 0) {
                    int newMask = (old >> 1) | (1 << (b - 1));
                    M[newMask][old] = (M[newMask][old] + 1) % MOD;
                }
            }
        }
        // ---------- 特殊矩阵 (新增位为1) ----------
        if ((old & 1) == 0) {
            int newMask = (old >> 1) | (1 << (2 * K)); // 最高位置1
            Ms[newMask][old] = (Ms[newMask][old] + 1) % MOD;
        } else {
            for (int b = 1; b <= 2 * K; ++b) {
                if (((old >> b) & 1) == 0) {
                    int newMask = (old >> 1) | (1 << (2 * K)) | (1 << (b - 1));
                    Ms[newMask][old] = (Ms[newMask][old] + 1) % MOD;
                }
            }
        }
    }
    // 预处理 M 的二进制幂
    powM.clear();
    powM.push_back(M);
    for (int i = 1; i < MAXLOG; ++i) {
        powM.push_back(matMul(powM[i - 1], powM[i - 1]));
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    // 预存所有 K 的矩阵幂 (最多4种)
    vector<vector<vector<vector<int>>>> allPow(4);
    vector<vector<vector<int>>> allSpecial(4);
    for (int k = 0; k <= 3; ++k) {
        vector<vector<int>> M, Ms;
        buildMatrices(k, M, Ms, allPow[k]);
        allSpecial[k] = Ms;
    }
    for (int tc = 1; tc <= T; ++tc) {
        long long n;
        int K;
        cin >> n >> K;
        int width = 2 * K + 1;
        int S = 1 << width;
        int fullMask = S - 1;
        // 初始状态
        int initMask = 0;
        for (int t = 0; t < width; ++t) {
            int num = 1 - K + t; // 数字 (1-K) + t
            if (num < 1 || num > n) {
                initMask |= (1 << t);
            }
        }
        vector<int> v(S, 0);
        v[initMask] = 1;
        // 普通步数 p = max(0, n - K - 1)
        long long p = n - K - 1;
        if (p < 0) p = 0;
        // 用二进制幂乘以向量
        int bit = 0;
        while (p > 0) {
            if (p & 1) {
                v = vecMul(allPow[K][bit], v);
            }
            p >>= 1;
            ++bit;
        }
        // 特殊步数 s = min(n, K+1)
        long long s = min(n, (long long)K + 1);
        for (long long i = 0; i < s; ++i) {
            v = vecMul(allSpecial[K], v);
        }
        int ans = v[fullMask] % MOD;
        cout << "Case " << tc << ": " << ans << '\n';
    }
    return 0;
}
