// Probability Through Experiments
// UVa ID: 12535
// Verdict: Accepted
// Submission Date: 2026-06-24
// UVa Run Time: 0.090s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, r, caseNo = 1;
    while (cin >> n >> r && (n || r)) {
        vector<int> angles(n);
        for (int i = 0; i < n; ++i) {
            double theta;
            cin >> theta;
            angles[i] = (int)(theta * 1000.0 + 0.5); // 转换为整数，避免浮点误差
        }
        sort(angles.begin(), angles.end());

        // 双倍数组，用于滑动窗口统计小于180°的点数
        vector<int> doubled(2 * n);
        for (int i = 0; i < n; ++i) {
            doubled[i] = angles[i];
            doubled[i + n] = angles[i] + 360000;
        }

        long long obtuse = 0; // 钝角三角形数
        int p = 0;
        for (int i = 0; i < n; ++i) {
            if (p < i) p = i;
            while (p + 1 < i + n && doubled[p + 1] - angles[i] < 180000)
                ++p;
            long long cnt = p - i; // 严格小于180°的点数
            obtuse += cnt * (cnt - 1) / 2;
        }

        // 统计对径点对数（直径数）
        unordered_set<int> angSet(angles.begin(), angles.end());
        long long diameterPairs = 0;
        for (int x : angles) {
            if (x < 180000 && angSet.count(x + 180000))
                ++diameterPairs;
        }

        long long total = 1LL * n * (n - 1) * (n - 2) / 6;
        long long right = diameterPairs * (n - 2); // 直角三角形数
        long long acute = total - obtuse - right;

        cout << "Case " << caseNo << ": " << acute << "\n";
        ++caseNo;
    }
    return 0;
}
