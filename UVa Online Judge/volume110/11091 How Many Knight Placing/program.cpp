// How Many Knight Placing
// UVa ID: 11091
// Verdict: Accepted
// Submission Date: 2025-12-22
// UVa Run Time: 0.050s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MOD = 10007;
const int NUM_STATES = 15;      // C(6,2)=15
const int TOTAL_STATES = 225;   // 15*15

int colStates[NUM_STATES];      // 所有单列状态
int M[TOTAL_STATES][TOTAL_STATES];  // 转移矩阵
int v2[TOTAL_STATES];           // 初始向量（n=2）

// 生成所有列状态
void generateColumnStates() {
    int idx = 0;
    for (int i = 0; i < (1 << 6); ++i)
        if (__builtin_popcount(i) == 2) colStates[idx++] = i;
}

// 检查攻击
bool statesAttack(int stateA, int colA, int stateB, int colB) {
    int dc = colB - colA;
    if (dc < 0) dc = -dc;
    for (int r1 = 0; r1 < 6; ++r1) {
        if (!(stateA >> r1 & 1)) continue;
        for (int r2 = 0; r2 < 6; ++r2) {
            if (!(stateB >> r2 & 1)) continue;
            int dr = abs(r1 - r2);
            if (dc == 1 && dr == 2) return true;
            if (dc == 2 && dr == 1) return true;
        }
    }
    return false;
}

// 初始化转移矩阵和初始向量
void initialize() {
    generateColumnStates();
    // 初始化转移矩阵为0
    memset(M, 0, sizeof(M));
    // 构建转移矩阵
    for (int pIdx = 0; pIdx < NUM_STATES; ++pIdx) {
        for (int cIdx = 0; cIdx < NUM_STATES; ++cIdx) {
            int fromIdx = pIdx * NUM_STATES + cIdx;
            for (int nIdx = 0; nIdx < NUM_STATES; ++nIdx) {
                int toIdx = cIdx * NUM_STATES + nIdx;
                if (statesAttack(colStates[cIdx], 1, colStates[nIdx], 2)) continue;
                if (statesAttack(colStates[pIdx], 0, colStates[nIdx], 2)) continue;
                M[toIdx][fromIdx] = 1;
            }
        }
    }
    // 构建初始向量v2
    memset(v2, 0, sizeof(v2));
    for (int i = 0; i < NUM_STATES; ++i) {
        for (int j = 0; j < NUM_STATES; ++j) {
            if (!statesAttack(colStates[i], 0, colStates[j], 1)) {
                v2[i * NUM_STATES + j] = 1;
            }
        }
    }
}

// 矩阵乘法: C = A * B
void matMul(int A[TOTAL_STATES][TOTAL_STATES], int B[TOTAL_STATES][TOTAL_STATES], int C[TOTAL_STATES][TOTAL_STATES]) {
    static int temp[TOTAL_STATES][TOTAL_STATES];
    memset(temp, 0, sizeof(temp));
    for (int i = 0; i < TOTAL_STATES; ++i) {
        for (int k = 0; k < TOTAL_STATES; ++k) {
            if (A[i][k] == 0) continue;
            for (int j = 0; j < TOTAL_STATES; ++j) {
                temp[i][j] = (temp[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    memcpy(C, temp, sizeof(temp));
}

// 矩阵向量乘法: result = M * vec
void matVecMul(int mat[TOTAL_STATES][TOTAL_STATES], int vec[TOTAL_STATES], int result[TOTAL_STATES]) {
    memset(result, 0, TOTAL_STATES * sizeof(int));
    for (int i = 0; i < TOTAL_STATES; ++i) {
        if (vec[i] == 0) continue;
        for (int j = 0; j < TOTAL_STATES; ++j)
            result[j] = (result[j] + mat[j][i] * vec[i]) % MOD;
    }
}

// 矩阵快速幂: result = M^power
void matPow(int base[TOTAL_STATES][TOTAL_STATES], long long power, int result[TOTAL_STATES][TOTAL_STATES]) {
    // 初始化为单位矩阵
    memset(result, 0, sizeof(int) * TOTAL_STATES * TOTAL_STATES);
    for (int i = 0; i < TOTAL_STATES; ++i) result[i][i] = 1;
    static int temp[TOTAL_STATES][TOTAL_STATES];
    memcpy(temp, base, sizeof(temp));
    while (power > 0) {
        if (power & 1) matMul(result, temp, result);
        matMul(temp, temp, temp);
        power >>= 1;
    }
}

int main() {
    initialize();
    int T;
    scanf("%d", &T);
    while (T--) {
        long long n;
        scanf("%lld", &n);
        if (n == 1) {
            printf("%d\n", NUM_STATES % MOD);
            continue;
        }
        if (n == 2) {
            int sum = 0;
            for (int i = 0; i < TOTAL_STATES; ++i) sum = (sum + v2[i]) % MOD;
            printf("%d\n", sum);
            continue;
        }
        // n >= 3
        int MPow[TOTAL_STATES][TOTAL_STATES];
        matPow(M, n - 2, MPow);
        int result[TOTAL_STATES];
        matVecMul(MPow, v2, result);
        int ans = 0;
        for (int i = 0; i < TOTAL_STATES; ++i) ans = (ans + result[i]) % MOD;
        printf("%d\n", ans);
    }
    return 0;
}
