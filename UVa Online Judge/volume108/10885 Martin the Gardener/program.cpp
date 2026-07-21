// Martin the Gardener
// UVa ID: 10885
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int c = 1105;
    int cSq = c * c;
    vector<pair<int,int>> pts;
    for (int a = 1; a < c; ++a) {
        int rem = cSq - a * a;
        int b = (int)sqrt(rem);
        if (b * b == rem && b > a) pts.emplace_back(b * b - a * a, 2 * a * b);
    }
    for (auto &p : pts) cout << p.first << " " << p.second << "\n";
    return 0;
}
