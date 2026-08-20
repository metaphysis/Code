#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<string> mat;
vector<int> used, sta, rem, ans;

bool dfs(int dep) {
    if (dep == m) return true;
    for (int col = 0; col < m; ++col) {
        if (used[col]) continue;
        bool ok = true;
        for (int row = 0; row < n; ++row) {
            int bit = mat[row][col] - '0';
            if (sta[row] == 2 && bit == 1) {
                ok = false;
                break;
            }
            if (sta[row] == 1 && bit == 0 && rem[row] - bit > 0) {
                ok = false;
                break;
            }
            if (sta[row] == 2 && rem[row] - bit > 0) {
                ok = false;
                break;
            }
        }
        if (!ok) continue;
        vector<int> oldSta = sta, oldRem = rem;
        for (int row = 0; row < n; ++row) {
            int bit = mat[row][col] - '0';
            rem[row] -= bit;
            if (sta[row] == 0 && bit == 1) sta[row] = 1;
            else if (sta[row] == 1 && bit == 0) sta[row] = 2;
        }
        used[col] = 1;
        ans.push_back(col);
        if (dfs(dep + 1)) return true;
        ans.pop_back();
        used[col] = 0;
        sta = oldSta;
        rem = oldRem;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCase;
    cin >> testCase;
    for (int tc = 0; tc < testCase; ++tc) {
        cin >> n >> m;
        mat.resize(n);
        for (int i = 0; i < n; ++i) cin >> mat[i];
        used.assign(m, 0);
        sta.assign(n, 0);
        rem.assign(n, 0);
        ans.clear();
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                rem[i] += mat[i][j] - '0';
        used[0] = 1;
        ans.push_back(0);
        for (int i = 0; i < n; ++i) {
            int bit = mat[i][0] - '0';
            rem[i] -= bit;
            if (bit == 1) sta[i] = 1;
        }
        dfs(1);
        if (tc > 0) cout << '\n';
        for (int col : ans) cout << col << '\n';
    }
    return 0;
}
