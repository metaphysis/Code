// Reliable Network
// UVa ID: 11268
// Verdict: Accepted
// Submission Date: 2026-07-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

void solveCase(int n, int m) {
    int k = m + 1;
    set<pair<int,int>> edges;
    auto addEdge = [&](int u, int v) {
        if (u > v) swap(u, v);
        if (u != v) edges.insert({u, v});
    };
    int r = k / 2;
    for (int d = 1; d <= r; ++d)
        for (int i = 0; i < n; ++i)
            addEdge(i, (i + d) % n);
    if (k % 2 == 1) {
        if (n % 2 == 0) {
            int half = n / 2;
            for (int i = 0; i < half; ++i)
                addEdge(i, (i + half) % n);
        } else {
            int s = (n - 1) / 2;
            for (int i = 0; i < s; ++i)
                addEdge(i, (i + s) % n);
            bool found = false;
            for (int v = 0; v < n - 1; ++v) {
                int a = v, b = n - 1;
                if (a > b) swap(a, b);
                if (edges.find({a, b}) == edges.end()) {
                    addEdge(v, n - 1);
                    found = true;
                    break;
                }
            }
            if (!found) addEdge(0, n - 1);
        }
    }
    cout << edges.size() << "\n";
    for (auto &p : edges)
        cout << p.first + 1 << " " << p.second + 1 << "\n";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        solveCase(n, m);
    }
    return 0;
}
