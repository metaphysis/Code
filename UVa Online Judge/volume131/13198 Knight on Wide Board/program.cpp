// Knight on Wide Board
// UVa ID: 13198
// Verdict: Accepted
// Submission Date: 2026-09-30
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000000007LL;
const int order = 21, bitCount = 31;

struct Matrix {
    long long a[order][order];
};

long long normalize(long long value) {
    value %= mod;
    if (value < 0) value += mod;
    return value;
}

Matrix multiplyMatrix(const Matrix &left, const Matrix &right) {
    Matrix result = {};
    int i, j, k;
    for (i = 0; i < order; i++) {
        for (k = 0; k < order; k++) {
            if (left.a[i][k] == 0) continue;
            for (j = 0; j < order; j++) result.a[i][j] = (result.a[i][j] + left.a[i][k] * right.a[k][j]) % mod;
        }
    }
    return result;
}

array<long long, order> multiplyVector(const Matrix &matrix, const array<long long, order> &vector) {
    array<long long, order> result = {};
    long long sum;
    int i, j;
    for (i = 0; i < order; i++) {
        sum = 0;
        for (j = 0; j < order; j++) sum = (sum + matrix.a[i][j] * vector[j]) % mod;
        result[i] = sum;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // 分别保存生成函数分子和分母的系数
    long long numerator[23] = {0, 0, 0, 0, 0, 16, 80, -544, -1856, 8080, 9856, -50864, -64, 152576, -130816, -214272, 245760, 222208, 44544, -53248, -352256, 81920, 32768};
    long long denominator[22] = {1, -6, -64, 200, 1000, -3016, -3488, 24256, -23776, -104168, 203408, 184704, -443392, -14336, 151296, -145920, 263424, -317440, -36864, 966656, -573440, -131072};
    long long initial[23] = {}, n, m, target, exponent;
    Matrix transition = {}, powers[bitCount];
    array<long long, order> state;
    int i, j, bit;
    // 通过生成函数卷积关系计算前二十三项
    for (i = 0; i <= 22; i++) {
        initial[i] = normalize(numerator[i]);
        for (j = 1; j <= min(i, order); j++) initial[i] = normalize(initial[i] - normalize(denominator[j]) * initial[i - j] % mod);
    }
    for (i = 0; i < order; i++) transition.a[0][i] = normalize(-denominator[i + 1]);
    for (i = 1; i < order; i++) transition.a[i][i - 1] = 1;
    powers[0] = transition;
    for (i = 1; i < bitCount; i++) powers[i] = multiplyMatrix(powers[i - 1], powers[i - 1]);
    while (cin >> n >> m) {
        if (n == 1 && m == 1) {
            cout << 1 << '\n';
            continue;
        }
        if (n != 3 || m < 10 || m % 2 == 1) {
            cout << 0 << '\n';
            continue;
        }
        target = m / 2;
        if (target <= 22) {
            cout << initial[target] << '\n';
            continue;
        }
        for (i = 0; i < order; i++) state[i] = initial[22 - i];
        exponent = target - 22;
        bit = 0;
        while (exponent > 0) {
            if (exponent & 1) state = multiplyVector(powers[bit], state);
            exponent >>= 1;
            bit++;
        }
        cout << state[0] << '\n';
    }
    return 0;
}
