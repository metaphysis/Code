// The Lost Gift
// UVa ID: 10889
// Verdict: Accepted
// Submission Date: 2025-11-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int r, b;
    while (cin >> r >> b && (r || b)) {
        long long delta = 1 + 8LL * r;
        long long sqrtDelta = sqrt(delta);
        if (sqrtDelta * sqrtDelta != delta) {
            cout << "No. of red balls invalid" << endl;
            continue;
        }
        vector<int> possibleLost;
        // 第一种情况: D = (-1 + sqrtDelta)/2
        if ((-1 + sqrtDelta) % 2 == 0) {
            long long d = (-1 + sqrtDelta) / 2;
            long long totalBlack = r - d;
            if (totalBlack > 0 && b >= ceil(0.7 * totalBlack) && b <= totalBlack) {
                possibleLost.push_back(totalBlack - b);
            }
        }
        // 第二种情况: D = (-1 - sqrtDelta)/2
        if ((-1 - sqrtDelta) % 2 == 0) {
            long long d = (-1 - sqrtDelta) / 2;
            long long totalBlack = r - d;
            if (totalBlack > 0 && b >= ceil(0.7 * totalBlack) && b <= totalBlack) {
                possibleLost.push_back(totalBlack - b);
            }
        }
        if (possibleLost.empty()) {
            cout << "No. of black balls invalid" << endl;
        } else {
            sort(possibleLost.begin(), possibleLost.end());
            for (size_t i = 0; i < possibleLost.size(); i++) {
                if (i > 0) cout << " ";
                cout << possibleLost[i];
            }
            cout << endl;
        }
    }
    return 0;
}
