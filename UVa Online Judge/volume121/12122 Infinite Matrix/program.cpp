#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000000007LL;
const int maxN = 205;
const int maxD = 405;
long long fac[maxD], invFac[maxD];
long long expMat[maxN][maxN], valueArr[maxN];
long long poly[maxN][maxD];
int n;

long long qPow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

void initMath() {
    fac[0] = 1;
    for (int i = 1; i < maxD; i++)
        fac[i] = fac[i - 1] * i % mod;
    invFac[maxD - 1] = qPow(fac[maxD - 1], mod - 2);
    for (int i = maxD - 1; i >= 1; i--)
        invFac[i - 1] = invFac[i] * i % mod;
}

long long combLarge(long long x, int y) {
    if (y < 0 || x < y) return 0;
    long long res = 1;
    for (int i = 0; i < y; i++)
        res = res * ((x - i) % mod + mod) % mod;
    return res * invFac[y] % mod;
}

void multiplyT(long long src[], long long dst[]) {
    memset(dst, 0, sizeof(long long) * maxD);
    for (int r = 0; r < maxD - 1; r++) {
        dst[r] = (dst[r] + src[r] * r) % mod;
        dst[r + 1] = (dst[r + 1] + src[r] * (r + 1)) % mod;
    }
}

void buildPoly() {
    memset(poly, 0, sizeof(poly));
    for (int j = 1; j <= n; j++) {
        long long diff[maxD] = {};
        for (int k = 1; k < j; k++) {
            long long cur[maxD] = {}, next[maxD];
            for (int r = 0; r < maxD; r++)
                cur[r] = poly[k][r];
            for (int e = 0; e < expMat[k][j]; e++) {
                multiplyT(cur, next);
                for (int r = 0; r < maxD; r++)
                    cur[r] = next[r];
            }
            for (int r = 0; r < maxD; r++)
                diff[r] = (diff[r] + cur[r]) % mod;
        }
        long long prevCoef[maxD] = {};
        for (int r = 0; r < maxD; r++) {
            prevCoef[r] = diff[r];
            if (r + 1 < maxD)
                prevCoef[r] = (prevCoef[r] + diff[r + 1]) % mod;
        }
        poly[j][0] = (valueArr[j] - prevCoef[0] + mod) % mod;
        for (int r = 0; r < maxD - 1; r++)
            poly[j][r + 1] = (poly[j][r + 1] + prevCoef[r]) % mod;
    }
}

long long solveQuery(int p, long long a, int b, long long c, int d) {
    long long cur[maxD] = {}, next[maxD];
    for (int j = b; j <= b + d; j++)
        for (int r = 0; r < maxD; r++)
            cur[r] = (cur[r] + poly[j][r]) % mod;
    long long shift = (1 - a) % mod;
    if (shift < 0) shift += mod;
    for (int step = 0; step < p; step++) {
        memset(next, 0, sizeof(next));
        for (int r = 0; r < maxD - 1; r++) {
            next[r] = (next[r] + cur[r] * ((r + shift) % mod)) % mod;
            next[r + 1] = (next[r + 1] + cur[r] * (r + 1)) % mod;
        }
        for (int r = 0; r < maxD; r++)
            cur[r] = next[r];
    }
    long long ans = 0;
    long long right = a + c + 1;
    for (int r = 0; r < maxD - 1; r++) {
        long long sum = (combLarge(right, r + 1) - combLarge(a, r + 1) + mod) % mod;
        ans = (ans + cur[r] * sum) % mod;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    initMath();
    int testCount;
    cin >> testCount;
    while (testCount--) {
        cin >> n;
        memset(expMat, 0, sizeof(expMat));
        for (int i = 1; i <= n; i++) {
            cin >> valueArr[i];
            for (int j = 1; j < i; j++)
                cin >> expMat[j][i];
        }
        buildPoly();
        int queryCount;
        cin >> queryCount;
        while (queryCount--) {
            int p, b, d;
            long long a, c;
            cin >> p >> a >> b >> c >> d;
            cout << solveQuery(p, a, b, c, d) << '\n';
        }
        cout << '\n';
    }
    return 0;
}
