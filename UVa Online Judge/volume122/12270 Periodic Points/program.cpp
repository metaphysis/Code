#include <bits/stdc++.h>
using namespace std;

const int MaxM = 85;
int m, n, modVal;
int fVal[MaxM];

struct Matrix {
    int a[MaxM][MaxM];
    Matrix() {
        memset(a, 0, sizeof(a));
    }
};

Matrix multiply(const Matrix &x, const Matrix &y) {
    Matrix z;
    for (int i = 0; i < m; i++)
        for (int k = 0; k < m; k++)
            if (x.a[i][k])
                for (int j = 0; j < m; j++)
                    z.a[i][j] = (z.a[i][j] + (long long)x.a[i][k] * y.a[k][j]) % modVal;
    return z;
}

Matrix power(Matrix base, int exp) {
    Matrix ret;
    for (int i = 0; i < m; i++)
        ret.a[i][i] = 1 % modVal;
    while (exp) {
        if (exp & 1) ret = multiply(ret, base);
        base = multiply(base, base);
        exp >>= 1;
    }
    return ret;
}

bool isInfinity() {
    for (int start = 0; start < m; start++) {
        int cur = start, sign = 1;
        bool ok = true;
        for (int step = 0; step < n; step++) {
            int slope = fVal[cur + 1] - fVal[cur];
            if (abs(slope) != 1) {
                ok = false;
                break;
            }
            sign *= slope;
            if (slope == 1) cur = fVal[cur];
            else cur = fVal[cur + 1];
        }
        if (ok && cur == start && sign == 1) return true;
    }
    return false;
}

int getVertexValue(int start) {
    int cur = start;
    for (int step = 0; step < n; step++)
        cur = fVal[cur];
    return cur;
}

int getSideCount(int vertex) {
    int cnt = 0;
    for (int firstSide = -1; firstSide <= 1; firstSide += 2) {
        int edge = firstSide == -1 ? vertex - 1 : vertex;
        if (edge < 0 || edge >= m) continue;
        int slope = fVal[edge + 1] - fVal[edge];
        if (slope == 0) continue;
        int cur = vertex, side = firstSide;
        bool ok = true;
        for (int step = 0; step < n; step++) {
            int nowEdge = side == -1 ? cur - 1 : cur;
            if (nowEdge < 0 || nowEdge >= m) {
                ok = false;
                break;
            }
            int nowSlope = fVal[nowEdge + 1] - fVal[nowEdge];
            if (nowSlope == 0) {
                ok = false;
                break;
            }
            int nextSide = nowSlope * side > 0 ? 1 : -1;
            cur = fVal[cur];
            side = nextSide;
        }
        if (ok && cur == vertex && side == firstSide) cnt++;
    }
    return cnt;
}

int solve() {
    Matrix trans;
    for (int i = 0; i < m; i++) {
        int left = min(fVal[i], fVal[i + 1]);
        int right = max(fVal[i], fVal[i + 1]);
        for (int j = left; j < right; j++)
            trans.a[i][j] = 1 % modVal;
    }
    if (isInfinity()) {
        cout << "Infinity\n";
        return 0;
    }
    Matrix result = power(trans, n);
    int ans = 0;
    for (int i = 0; i < m; i++)
        ans = (ans + result.a[i][i]) % modVal;
    for (int vertex = 0; vertex <= m; vertex++)
        if (getVertexValue(vertex) == vertex)
            ans = (ans + 1 - getSideCount(vertex)) % modVal;
    if (ans < 0) ans += modVal;
    cout << ans << '\n';
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> m && m) {
        for (int i = 0; i <= m; i++)
            cin >> fVal[i];
        cin >> n >> modVal;
        solve();
    }
    return 0;
}
