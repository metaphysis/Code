// Radiation
// UVa ID: 12537
// Verdict: Accepted
// Submission Date: 2025-12-25
// UVa Run Time: 0.090s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct House {
    int x, y;
    int dist1, dist2; // 到两个核电站的平方距离
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int caseNo = 1;
    int n;
    while (cin >> n && n) {
        vector<House> houses(n);
        for (int i = 0; i < n; i++) cin >> houses[i].x >> houses[i].y;

        int ax, ay, bx, by, q;
        cin >> ax >> ay >> bx >> by >> q;

        // 计算每个房子到两个核电站的平方距离
        for (int i = 0; i < n; i++) {
            int dx1 = houses[i].x - ax, dy1 = houses[i].y - ay;
            int dx2 = houses[i].x - bx, dy2 = houses[i].y - by;
            houses[i].dist1 = dx1 * dx1 + dy1 * dy1;
            houses[i].dist2 = dx2 * dx2 + dy2 * dy2;
        }

        // 按 dist1 排序，用于二分查找 A
        vector<int> dist1Sorted(n);
        for (int i = 0; i < n; i++) dist1Sorted[i] = houses[i].dist1;
        sort(dist1Sorted.begin(), dist1Sorted.end());

        // 收集所有 dist2，用于二分查找 B
        vector<int> dist2Sorted(n);
        for (int i = 0; i < n; i++) dist2Sorted[i] = houses[i].dist2;
        sort(dist2Sorted.begin(), dist2Sorted.end());

        cout << "Case " << caseNo++ << ":\n";

        while (q--) {
            int r1, r2;
            cin >> r1 >> r2;
            r1 *= r1; // 转换为平方距离
            r2 *= r2;

            // A: dist1 <= r1 的房子数
            int A = upper_bound(dist1Sorted.begin(), dist1Sorted.end(), r1) - dist1Sorted.begin();
            // B: dist2 <= r2 的房子数
            int B = upper_bound(dist2Sorted.begin(), dist2Sorted.end(), r2) - dist2Sorted.begin();

            int answer = max(0, n - A - B);
            cout << answer << "\n";
        }
    }

    return 0;
}
