// WiFi Access
// UVa ID: 12748
// Verdict: Accepted
// Submission Date: 2023-04-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct circle { int x, y, r; } cls[110];

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++) {
        cout << "Case " << cs << ":\n";
        int n, y;
        cin >> n >> y;
        for (int i = 0; i < n; i++) cin >> cls[i].x >> cls[i].y >> cls[i].r;
        for (int i = 0, yx, yy; i < y; i++) {
            cin >> yx >> yy;
            int in = 0;
            for (int j = 0; j < n; j++)
                if (cls[j].r * cls[j].r >=
                    (yx - cls[j].x) * (yx - cls[j].x) +
                        (yy - cls[j].y) * (yy - cls[j].y)) {
                    in = 1;
                    break;
                }
            cout << (in ? "Yes" : "No") << '\n';
        }
    }
    return 0;
}
