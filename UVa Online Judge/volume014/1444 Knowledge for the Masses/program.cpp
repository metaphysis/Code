#include <bits/stdc++.h>
using namespace std;

const int inf = 0x3f3f3f3f;

void solveRow(int l, vector<unsigned long long>& ans) {
    int n, now, pos, opos;
    cin >> n;
    vector<int> a(n), b(n + 1), cost(l, inf);
    for (int i = 0; i < n; i++) cin >> a[i];
    now = 0, pos = 0, b[0] = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) {
            now++;
            b[now] = b[now - 1];
            cost[pos] = 0;
            pos++;
        } else {
            opos = pos;
            pos += a[i];
            b[now]++;
            for (int c = pos - 1, d = now - 1; c >= opos && d >= 0; c--, d--) cost[c] = b[now] - b[d];
        }
    }
    now = 0, pos = l - 1, b[0] = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] == 0) {
            now++;
            b[now] = b[now - 1];
            cost[pos] = 0;
            pos--;
        } else {
            opos = pos;
            pos -= a[i];
            b[now]++;
            for (int c = pos + 1, d = now - 1; c <= opos && d >= 0; c++, d--) cost[c] = min(cost[c], b[now] - b[d]);
        }
    }
    for (int i = 0; i < l; i++) ans[i] += cost[i];
}

void solve() {
    int r, l;
    cin >> r >> l;
    vector<unsigned long long> ans(l, 0);
    for (int i = 0; i < r; i++) solveRow(l, ans);
    unsigned long long best = ULLONG_MAX;
    for (int i = 0; i < l; i++) best = min(best, ans[i]);
    cout << best << '\n';
    for (int i = 0; i < l; i++)
        if (ans[i] == best) cout << i << ' ';
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int z;
    cin >> z;
    while (z--) solve();
    return 0;
}
