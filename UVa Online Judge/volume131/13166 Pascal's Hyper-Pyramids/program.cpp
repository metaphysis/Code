#include <bits/stdc++.h>
using namespace std;

int dim, total;
vector<int> cur;
set<long long> ans;

long long getComb(int n, int k) {
    long long res = 1;
    int i;
    k = min(k, n - k);
    for (i = 1; i <= k; ++i)
        res = (long long)((__int128)res * (n - k + i) / i);
    return res;
}

long long getValue() {
    __int128 val = 1;
    int rem = total, i;
    for (i = 0; i < dim; ++i) {
        val *= getComb(rem, cur[i]);
        rem -= cur[i];
    }
    return (long long)val;
}

void dfs(int pos, int rem, int lim) {
    if (pos == dim) {
        if (rem == 0) ans.insert(getValue());
        return;
    }
    int left = dim - pos - 1, x;
    for (x = min(lim, rem); x >= 0; --x) {
        if (rem - x > x * left) continue;
        cur[pos] = x;
        dfs(pos + 1, rem - x, x);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int height;
    while (cin >> dim >> height) {
        total = height - 1;
        cur.assign(dim, 0);
        ans.clear();
        dfs(0, total, total);
        for (long long value : ans)
            cout << value << '\n';
    }
    return 0;
}
