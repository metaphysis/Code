// High Bridge Low Bridge
// UVa ID: 12663
// Verdict: Accepted
// Submission Date: 2025-12-23
// UVa Run Time: 0.040s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;

int main() {
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    int caseNo = 1;
    int n, m, k;
    int bridgeHeight[MAXN], diff[MAXN];
    int a, b;
    while (cin >> n >> m >> k) {
        for (int i = 0; i < n; i++) {
            cin >> bridgeHeight[i];
            diff[i] = 0;
        }
        sort(bridgeHeight, bridgeHeight + n);
        int lastWaterLevel = 1; // 初始水位为1，也是第一次洪水前的b₀
        for (int i = 0; i < m; i++) {
            cin >> a >> b;
            // 本次洪水影响：高度在 (lastWaterLevel, a] 范围内的桥
            // 使用 upper_bound 找到第一个 > lastWaterLevel 的桥
            // 使用 upper_bound 找到第一个 > a 的桥，然后-1得到最后一个 ≤ a 的桥
            int left = upper_bound(bridgeHeight, bridgeHeight + n, lastWaterLevel) - bridgeHeight;
            int right = upper_bound(bridgeHeight, bridgeHeight + n, a) - bridgeHeight - 1;
            if (left <= right) {
                diff[left]++;
                diff[right + 1]--;
            }
            lastWaterLevel = b; // 更新为本次洪水结束后的水位
        }
        // 计算每座桥被淹的次数
        int currentFloodCount = 0;
        int answer = 0;
        for (int i = 0; i < n; i++) {
            currentFloodCount += diff[i];
            if (currentFloodCount >= k) answer++;
        }
        cout << "Case " << caseNo++ << ": " << answer << '\n';
    }
    return 0;
}
