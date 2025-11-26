// The Optimal Super-Highway
// UVa ID: 10744
// Verdict: Accepted
// Submission Date: 2025-11-25
// UVa Run Time: 0.150s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++)
        cin >> x[i] >> y[i];

    for (int qi = 1; qi <= q; qi++) {
        int ax, ay, bx, by;
        cin >> ax >> ay >> bx >> by;

        int dx = bx - ax, dy = by - ay;
        double len = sqrt(dx * dx + dy * dy);

        vector<double> dists(n);
        for (int i = 0; i < n; i++) {
            int vx = x[i] - ax, vy = y[i] - ay;
            dists[i] = (vx * dy - vy * dx) / len; // 有向距离
        }

        nth_element(dists.begin(), dists.begin() + n / 2, dists.end());
        double median = dists[n / 2];

        double sum = 0;
        for (double d : dists)
            sum += fabs(d - median);

        cout << "Case " << qi << ": " << (int)round(sum) << "\n";
    }

    return 0;
}
