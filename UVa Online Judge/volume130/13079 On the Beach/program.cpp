// On the Beach
// UVa ID: 13079
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 0.010s

#include <bits/stdc++.h>
using namespace std;

struct Build {
    int west, east;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n && n) {
        vector<Build> builds(n);
        for (int i = 0; i < n; i++)
            cin >> builds[i].west >> builds[i].east;
        sort(builds.begin(), builds.end(), [](const Build &a, const Build &b) {
            return a.east < b.east;
        });
        int ans = 0, last = -1;
        for (const Build &build : builds) {
            if (build.west > last) {
                ans++;
                last = build.east - 1;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
