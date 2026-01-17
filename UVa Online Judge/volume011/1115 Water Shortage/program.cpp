// Water Shortage
// UVa ID: 1115
// Verdict: Accepted
// Submission Date: 2026-01-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Cistern {
    double base;    // 基底高度
    double height;  // 高度
    double width;   // 宽度
    double depth;   // 深度
};

int main() {
    int testCases;
    cin >> testCases;
    for (int t = 0; t < testCases; ++t) {
        if (t > 0) cout << '\n'; // 测试用例之间输出空行
        int n;
        cin >> n;
        vector<Cistern> ctns(n);
        double maxHeight = 0.0;
        double totalVolume = 0.0;
        // 读取每个水箱信息并计算总容量和最大可能水位
        for (int i = 0; i < n; ++i) {
            cin >> ctns[i].base >> ctns[i].height >> ctns[i].width >> ctns[i].depth;
            totalVolume += ctns[i].height * ctns[i].width * ctns[i].depth;
            maxHeight = max(maxHeight, ctns[i].base + ctns[i].height);
        }
        double waterVolume;
        cin >> waterVolume;
        // 检查是否溢出
        if (waterVolume > totalVolume) {
            cout << "OVERFLOW" << endl;
            continue;
        }
        // 二分查找水位高度
        double left = 0.0, right = maxHeight;
        while (right - left > 1e-6) {
            double mid = (left + right) / 2;
            double volume = 0.0;
            // 计算当前水位 mid 下的总水量
            for (int i = 0; i < n; ++i) {
                if (mid <= ctns[i].base)
                    continue; // 水位低于水箱底部
                double h = min(ctns[i].height, mid - ctns[i].base);
                volume += h * ctns[i].width * ctns[i].depth;
            }
            if (volume < waterVolume) left = mid;
            else right = mid;
        }
        // 输出结果，保留两位小数（截断）
        cout << fixed << setprecision(2) << left << '\n';
    }
    return 0;
}
