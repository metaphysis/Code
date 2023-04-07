// Cosmic Cabbages
// UVa ID: 11012
// Verdict: Accepted
// Submission Date: 2023-04-08
// UVa Run Time: 0.030s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100010, INF = 0x7f7f7f7f;

struct point { int x, y, z; } ps[100010];

int sign(int i, int j) { return i & (1 << j) ? -1 : 1; }

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++) {
        int n;
        cin >> n;
        for (int i = 0, x, y, z; i < n; i++)
            cin >> ps[i].x >> ps[i].y >> ps[i].z;
        int r = 0;
        for (int i = 0; i < 8; i++) {
            int m1 = -INF, m2 = -INF;
            int r1, r2;
            for (int j = 0; j < n; j++) {
                r1 = sign(i, 0) * ps[j].x + sign(i, 1) * ps[j].y + sign(i, 2) * ps[j].z;
                r2 = -sign(i, 0) * ps[j].x + -sign(i, 1) * ps[j].y + -sign(i, 2) * ps[j].z;
                m1 = max(m1, r1);
                m2 = max(m2, r2);
            }
            r = max(r, m1 + m2);
        }
        cout << "Case #" << cs << ": ";
        cout << r << '\n';
    }
    return 0;
}
