// Swap Space
// UVa ID: 1747
// Verdict: Accepted
// Submission Date: 2025-11-20
// UVa Run Time: 0.510s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Drive {
    long long a, b;
};

int main() {
    int n;
    while (cin >> n) {
        vector<Drive> drives(n);
        for (int i = 0; i < n; i++) {
            cin >> drives[i].a >> drives[i].b;
        }
        
        // 分离两类硬盘：新容量≥旧容量 vs 新容量<旧容量
        vector<Drive> gain, loss;
        for (const auto& drive : drives) {
            if (drive.b >= drive.a) {
                gain.push_back(drive);
            } else {
                loss.push_back(drive);
            }
        }
        
        // 增益硬盘按旧容量升序，损耗硬盘按新容量降序
        sort(gain.begin(), gain.end(), [](const Drive& d1, const Drive& d2) {
            return d1.a < d2.a;
        });
        sort(loss.begin(), loss.end(), [](const Drive& d1, const Drive& d2) {
            return d1.b > d2.b;
        });
        
        // 合并处理顺序：先处理增益硬盘，再处理损耗硬盘
        vector<Drive> orderedDrives;
        orderedDrives.insert(orderedDrives.end(), gain.begin(), gain.end());
        orderedDrives.insert(orderedDrives.end(), loss.begin(), loss.end());
        
        long long currentSpace = 0;
        long long extraNeeded = 0;
        
        for (const auto& drive : orderedDrives) {
            if (drive.a > currentSpace) {
                extraNeeded += drive.a - currentSpace;
                currentSpace = drive.a;
            }
            currentSpace += drive.b - drive.a;
        }
        
        cout << extraNeeded << endl;
    }
    return 0;
}
