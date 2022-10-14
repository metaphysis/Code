// Teletransport
// UVa ID: 12796
// Verdict: Accepted
// Submission Date: 2022-10-09
// UVa Run Time: 0.370s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MOD = 10000;

struct matrix {
    int v[110][110], row, column;
    matrix(int n, int m, int dc = 0) {
        memset(v, 0, sizeof(v));
        row = n, column = m;
        for (int i = 1; i <= row && i <= column; i++) v[i][i] = dc;
    }
    matrix operator*(const matrix &x) const {
        matrix r(row, x.column);
        for (int i = 1; i <= row; i++) {
            for (int k = 1; k <= column; k++) {
                if (v[i][k])
                    for (int j = 1; j <= x.column; j++) {
                        r.v[i][j] += v[i][k] * x.v[k][j];
                        r.v[i][j] %= MOD;
                    }
            }
        }
        return r;
    }
    matrix operator^(const int &n) const {
        matrix r(row, column, 1), x = *this;
        int y = n;
        while (y) {
            if (y & 1) r = r * x;
            x = x * x;
            y >>= 1;
        }
        return r;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int N, L, S, T;
    while (cin >> N >> L) {
        cin >> S >> T;
        matrix m(N, N);
        for (int i = 1; i <= N; i++)
            for (int j = 1, p; j <= 4; j++) {
                cin >> p;
                m.v[i][p]++;
            }
        matrix r = m ^ L;
        cout << r.v[S][T] << '\n';
    }
    return 0;
}
