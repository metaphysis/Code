#include <bits/stdc++.h>
using namespace std;

vector<int> getPi(const string &str) {
    int i, j;
    vector<int> pi(str.size(), 0);
    for (i = 1; i < (int)str.size(); i++) {
        j = pi[i - 1];
        while (j > 0 && str[i] != str[j])
            j = pi[j - 1];
        if (str[i] == str[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

bool solve() {
    int n, m, i, j, k, r, col, pos;
    if (!(cin >> n >> m))
        return false;
    vector<string> pat(n);
    vector<long double> pw(m + 1, 0.0L);
    vector<vector<long double>> mat(n + 1, vector<long double>(n + 2, 0.0L));
    for (i = 0; i < n; i++)
        cin >> pat[i];
    pw[0] = ldexp(1.0L, -m);
    for (i = 1; i <= m; i++)
        pw[i] = pw[i - 1] * 2.0L;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            string str = pat[i] + "#" + pat[j];
            vector<int> pi = getPi(str);
            k = pi.back();
            while (k > 0) {
                mat[i][j] += pw[k];
                k = pi[k - 1];
            }
        }
        mat[i][n] = -1.0L;
    }
    for (i = 0; i < n; i++)
        mat[n][i] = 1.0L;
    mat[n][n + 1] = 1.0L;
    for (col = 0; col <= n; col++) {
        pos = col;
        for (r = col + 1; r <= n; r++)
            if (fabsl(mat[r][col]) > fabsl(mat[pos][col]))
                pos = r;
        swap(mat[col], mat[pos]);
        for (r = col + 1; r <= n; r++) {
            long double fac = mat[r][col] / mat[col][col];
            for (j = col; j <= n + 1; j++)
                mat[r][j] -= fac * mat[col][j];
        }
    }
    vector<long double> ans(n + 1, 0.0L);
    for (i = n; i >= 0; i--) {
        ans[i] = mat[i][n + 1];
        for (j = i + 1; j <= n; j++)
            ans[i] -= mat[i][j] * ans[j];
        ans[i] /= mat[i][i];
    }
    cout << fixed << setprecision(6);
    for (i = 0; i < n; i++) {
        if (fabsl(ans[i]) < 0.0000005L)
            ans[i] = 0.0L;
        cout << ans[i] << '\n';
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (solve());
    return 0;
}
