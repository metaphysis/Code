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
const int order = 21;
const int bitCount = 31;

struct Matrix {
    long long value[order][order];
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
            if (left.value[i][k] == 0) continue;
            for (j = 0; j < order; j++) result.value[i][j] = (result.value[i][j] + left.value[i][k] * right.value[k][j]) % mod;
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
        for (j = 0; j < order; j++) sum = (sum + matrix.value[i][j] * vector[j]) % mod;
        result[i] = sum;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long firstValue[23] = {0, 0, 0, 0, 0, 16, 176, 1536, 15424, 147728, 1448416, 14060048, 136947616, 1332257856, 12965578752, 126169362176, 1227776129152, 11947846468608, 116266505653888, 1131418872918784, 11010065269439104, 107141489725900544, 1042616896632882688};
    long long coefficient[21] = {6, 64, -200, -1000, 3016, 3488, -24256, 23776, 104168, -203408, -184704, 443392, 14336, -151296, 145920, -263424, 317440, 36864, -966656, 573440, 131072};
    Matrix transition = {}, powers[bitCount];
    array<long long, order> state;
    long long n, m, index, exponent;
    int i, bit;
    for (i = 0; i < order; i++) transition.value[0][i] = normalize(coefficient[i]);
    for (i = 1; i < order; i++) transition.value[i][i - 1] = 1;
    powers[0] = transition;
    for (i = 1; i < bitCount; i++) powers[i] = multiplyMatrix(powers[i - 1], powers[i - 1]);
    while (cin >> n >> m) {
        if (n == 1 && m == 1) {
            cout << 1 << '\n';
            continue;
        }
        if (n != 3 || m % 2 == 1) {
            cout << 0 << '\n';
            continue;
        }
        index = m / 2;
        if (index <= 22) {
            cout << firstValue[index] % mod << '\n';
            continue;
        }
        for (i = 0; i < order; i++) state[i] = firstValue[22 - i] % mod;
        exponent = index - 22;
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
