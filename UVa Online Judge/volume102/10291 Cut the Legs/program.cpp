// Cut the Legs
// UVa ID: 10291
// Verdict: Accepted
// Submission Date: 2025-11-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

bool isStable(const vector<int>& indices, int total) {
    int nOfIndices = indices.size();
    if (nOfIndices < 3) return false;
    // 每个腿之间的夹角是 360/n 度
    // 检查任意相邻支撑腿之间的夹角是否小于180度
    for (int i = 0; i < nOfIndices; i++) {
        int current = indices[i];
        int next = indices[(i + 1) % nOfIndices];
        // 计算两个支撑腿之间的夹角（以基本夹角为单位）
        int gap = 0;
        if (next > current) gap = next - current;
        else gap = next + total - current;
        if (2 * gap >= total) return false;
    }
    return true;
}

int main() {
    int n;
    bool firstCase = true;
    while (cin >> n && n != 0) {
        if (!firstCase) cout << endl;
        firstCase = false;
        vector<int> legs(n);
        for (int i = 0; i < n; i++) cin >> legs[i];
        // 从高到低尝试所有目标高度
        set<int> heights;
        for (int leg : legs) heights.insert(leg);
        for (auto it = heights.rbegin(); it != heights.rend(); it++) {
            int targetHeight = *it;
            vector<int> supportIndices;
            for (int i = 0; i < n; i++)
                if (legs[i] >= targetHeight)
                    supportIndices.push_back(i);
            if (isStable(supportIndices, n)) {
                int totalCut = 0;
                for (int leg : legs)
                    if (leg > targetHeight)
                        totalCut += leg - targetHeight;
                cout << totalCut << '\n';
                break;
            }
        }
    }
    return 0;
}
