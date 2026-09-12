#include <bits/stdc++.h>
using namespace std;

int solve() {
    string city, edge;
    int n, s, p;
    while (cin >> city) {
        if (city == "TheEnd")
            break;
        cin >> n >> s >> p;
        vector<int> adj(n, 0);
        for (int i = 0; i < p; i++) {
            cin >> edge;
            int u = edge[0] - 'A', v = edge[1] - 'A';
            adj[u] |= 1 << v;
            adj[v] |= 1 << u;
        }
        long long ans = 0;
        int total = 1 << n;
        for (int mask = 0; mask < total; mask++) {
            if (__builtin_popcount(mask) != s)
                continue;
            bool ok = true;
            for (int v = 0; v < n; v++) {
                if (mask & (1 << v))
                    continue;
                if (__builtin_popcount(adj[v] & mask) >= 2) {
                    ok = false;
                    break;
                }
            }
            if (ok)
                ans++;
        }
        cout << city << '\n' << ans << '\n';
    }
    cout << "TheEnd\n";
    return 0;
}

int main() {
    return solve();
}
