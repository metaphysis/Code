// Pixel Art
// UVa ID: 13171
// Verdict: Accepted
// Submission Date: 2025-11-15
// UVa Run Time: 0.030s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int m, y, c;
        string s;
        cin >> m >> y >> c >> s;
        
        for (char pixel : s) {
            switch (pixel) {
                case 'M': m--; break;
                case 'Y': y--; break;
                case 'C': c--; break;
                case 'R': m--; y--; break;
                case 'G': y--; c--; break;
                case 'V': m--; c--; break;
                case 'B': m--; y--; c--; break;
                case 'W': break;
            }
            if (m < 0 || y < 0 || c < 0) break;
        }
        
        if (m < 0 || y < 0 || c < 0) {
            cout << "NO\n";
        } else {
            cout << "YES " << m << " " << y << " " << c << "\n";
        }
    }
    return 0;
}
