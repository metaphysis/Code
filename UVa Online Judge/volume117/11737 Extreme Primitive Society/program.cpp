// Extreme Primitive Society
// UVa ID: 11737
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, caseNo = 1;
    while (cin >> n) {
        bool hasW[101] = {false}, hasH[101] = {false};
        bool hasSquare = false;
        for (int i = 0; i < n; ++i) {
            int w, h;
            cin >> w >> h;
            hasW[w] = true;
            hasH[h] = true;
            if (w == h) hasSquare = true;
        }
        int ans;
        if (hasSquare) ans = 0;
        else {
            int minDiff = 100; // 最大差值不超过99
            for (int w = 1; w <= 100; ++w) if (hasW[w])
                for (int h = 1; h <= 100; ++h) if (hasH[h])
                    minDiff = min(minDiff, abs(w - h));
            // 需要至少1代，且每代最多缩减差值2
            ans = max(1, (minDiff + 1) / 2); // ceil(minDiff/2)
        }
        cout << "Case " << caseNo++ << " : " << ans << '\n';
    }
    return 0;
}
