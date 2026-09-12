#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000000000LL;
const int maxS = 136;

struct Matrix {
    long long a[maxS][maxS];
};

int n, lim, cnt;
int trans[256][256], id[256], rep[256];
vector<int> state;

int revMask(int x) {
    int y = 0;
    for (int i = 0; i < n; i++)
        if (x & (1 << i)) y |= 1 << (n - i - 1);
    return y;
}

void dfsFill(int in, int used, int out) {
    int p = 0;
    while (p < n && (used & (1 << p))) p++;
    if (p == n) {
        trans[in][out]++;
        return;
    }
    dfsFill(in, used | (1 << p), out);
    dfsFill(in, used | (1 << p), out | (1 << p));
    if (p + 1 < n && !(used & (1 << (p + 1))))
        dfsFill(in, used | (1 << p) | (1 << (p + 1)), out);
}

Matrix mul(const Matrix &x, const Matrix &y) {
    Matrix z = {}, t = {};
    for (int i = 0; i < cnt; i++)
        for (int j = 0; j < cnt; j++)
            t.a[j][i] = y.a[i][j];
    for (int i = 0; i < cnt; i++) {
        for (int j = 0; j < cnt; j++) {
            __int128 sum = 0;
            for (int k = 0; k < cnt; k++)
                sum += (__int128)x.a[i][k] * t.a[j][k];
            z.a[i][j] = (long long)(sum % mod);
        }
    }
    return z;
}

Matrix power(Matrix x, long long p) {
    Matrix ans = {};
    for (int i = 0; i < cnt; i++) ans.a[i][i] = 1;
    while (p > 0) {
        if (p & 1) ans = mul(ans, x);
        x = mul(x, x);
        p >>= 1;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long m;
    while (cin >> n >> m) {
        lim = 1 << n;
        memset(trans, 0, sizeof(trans));
        memset(id, -1, sizeof(id));
        state.clear();
        for (int s = 0; s < lim; s++)
            dfsFill(s, s, 0);
        cnt = 0;
        for (int s = 0; s < lim; s++) {
            int r = revMask(s);
            rep[s] = min(s, r);
            if (rep[s] == s) {
                id[s] = cnt++;
                state.push_back(s);
            }
        }
        for (int s = 0; s < lim; s++)
            id[s] = id[rep[s]];
        Matrix base = {};
        for (int i = 0; i < cnt; i++) {
            int x = state[i];
            for (int j = 0; j < cnt; j++) {
                int y = state[j], ry = revMask(y);
                base.a[i][j] = trans[x][y];
                if (ry != y) base.a[i][j] += trans[x][ry];
                base.a[i][j] %= mod;
            }
        }
        Matrix ans = power(base, m);
        cout << ans.a[id[0]][id[0]] << '\n';
    }
    return 0;
}
