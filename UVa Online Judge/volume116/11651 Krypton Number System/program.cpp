// Krypton Number System
// UVa ID: 11651
// Verdict: Accepted
// Submission Date: 2026-01-14
// UVa Run Time: 0.690s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 使用 unsigned int，运算溢出时自动实现对 2^32 取模
typedef unsigned int uint;

// 矩阵结构体，用于矩阵快速幂
struct Matrix {
    int n; // 矩阵维度
    vector<vector<uint>> m; // 矩阵数据
    Matrix(int sz = 0): n(sz), m(sz, vector<uint>(sz, 0)) {}

    // 矩阵乘法
    Matrix operator*(const Matrix& b) const {
        Matrix r(n);
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                if (m[i][k]) { // 稀疏性优化，跳过0值
                    for (int j = 0; j < n; j++) {
                        r.m[i][j] += m[i][k] * b.m[k][j];
                    }
                }
            }
        }
        return r;
    }
};

// 矩阵快速幂，计算 a^p
Matrix matPow(Matrix a, int p) {
    Matrix r(a.n);
    // 初始化为单位矩阵
    for (int i = 0; i < a.n; i++) r.m[i][i] = 1;
    while (p) {
        if (p & 1) r = r * a;
        a = a * a;
        p >>= 1;
    }
    return r;
}

int main() {
    int T, base, score;
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        scanf("%d%d", &base, &score);

        // maxSq 是相邻数字差值的最大平方
        int maxSq = (base - 1) * (base - 1);
        // 状态向量长度 L = base * maxSq
        int L = base * maxSq;

        // ---------- 1. 构造转移矩阵 M (L x L) ----------
        Matrix M(L);
        // 索引规则: idx = last * maxSq + offset
        // V_s[idx] 存储 dp[s - offset][last]
        for (int last = 0; last < base; last++) {
            for (int prev = 0; prev < base; prev++) {
                if (last == prev) continue; // 相邻数字不能相同
                int d = (last - prev) * (last - prev); // 分数增量
                // 遍历所有偏移量 offset
                for (int offset = 0; offset < maxSq; offset++) {
                    if (offset == 0) {
                        // 计算新的 dp[s][last]
                        // 它依赖于旧的 dp[s-d][prev]，该值位于 V_{s-1} 的特定位置
                        int fromRow = prev * maxSq + (d - 1); // V_{s-1} 中的源索引
                        int toCol = last * maxSq + 0;         // V_s 中的目标索引
                        M.m[fromRow][toCol] = 1;
                    } else {
                        // 平移历史数据：V_s[last,offset] = V_{s-1}[last, offset-1]
                        int shiftFrom = last * maxSq + (offset - 1);
                        int shiftTo = last * maxSq + offset;
                        M.m[shiftFrom][shiftTo] = 1;
                    }
                }
            }
        }

        // ---------- 2. 构造初始向量 V0 ----------
        // V0 对应 s=0 时的状态向量
        vector<uint> V0(L, 0);
        // 初始化：dp[0][last] = 1 (last != 0)
        for (int last = 1; last < base; last++) {
            int idx = last * maxSq + 0; // offset = 0
            V0[idx] = 1;
        }

        // ---------- 3. 计算 V_score = M^score * V0 ----------
        Matrix Mp = matPow(M, score);
        vector<uint> Vscore(L, 0);
        // 模拟矩阵 Mp 与列向量 V0 的乘法，结果存入 Vscore
        for (int i = 0; i < L; i++) {
            if (V0[i] == 0) continue; // 优化：跳过0值
            for (int j = 0; j < L; j++) {
                Vscore[j] += V0[i] * Mp.m[i][j];
            }
        }

        // ---------- 4. 提取答案 ----------
        // 答案 = sum_{last=0}^{base-1} dp[score][last]
        // dp[score][last] 存储在 Vscore 中索引为 (last * maxSq + 0) 的位置
        uint ans = 0;
        for (int last = 0; last < base; last++) {
            int idx = last * maxSq + 0;
            ans += Vscore[idx];
        }
        printf("Case %d: %u\n", tc, ans);
    }
    return 0;
}
