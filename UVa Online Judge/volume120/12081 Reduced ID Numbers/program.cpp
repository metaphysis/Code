// Reduced ID Numbers
// UVa ID: 12081
// Verdict: Accepted
// Submission Date: 2026-05-27
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    while (N--) {
        int G;
        cin >> G;
        vector<int> sins(G);
        for (int i = 0; i < G; ++i) cin >> sins[i];
        
        int m = 1;
        while (true) {
            vector<bool> seen(m, false); // 记录模 m 的结果是否出现过
            bool ok = true;
            for (int i = 0; i < G; ++i) {
                int r = sins[i] % m;
                if (seen[r]) { ok = false; break; }
                seen[r] = true;
            }
            if (ok) break;
            ++m;
        }
        cout << m << endl;
    }
    return 0;
}
