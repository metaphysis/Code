// Nested Squares
// UVa ID: 12115
// Verdict: Accepted
// Submission Date: 2025-12-
// UVa Run Time: 0.040s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int numCases;
    cin >> numCases;
    for (int caseNo = 1; caseNo <= numCases; caseNo++) {
        string s;
        int q;
        cin >> s >> q;
        int n = 2 * s.length() - 1; // 正方形边长
        
        cout << "Square " << caseNo << ":\n";
        for (int queryNo = 1; queryNo <= q; queryNo++) {
            int r1, c1, r2, c2;
            cin >> r1 >> c1 >> r2 >> c2;
            cout << "Query " << queryNo << ":\n";
            
            for (int r = r1; r <= r2; r++) {
                for (int c = c1; c <= c2; c++) {
                    // 计算到四个边界的最小距离
                    int distUp = r - 1;
                    int distDown = n - r;
                    int distLeft = c - 1;
                    int distRight = n - c;
                    int level = min(min(distUp, distDown), min(distLeft, distRight));
                    cout << s[level];
                }
                cout << "\n";
            }
        }
        cout << "\n";
    }
    return 0;
}
