// Tian Ji The Horse Racing
// UVa ID: 1344
// Verdict: Accepted
// Submission Date: 2025-10-20
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int n;
    while (cin >> n && n != 0) {
        vector<int> tian(n), king(n);
        for (int i = 0; i < n; i++) cin >> tian[i];
        for (int i = 0; i < n; i++) cin >> king[i];
        
        // 将双方马匹按速度从大到小排序
        sort(tian.begin(), tian.end(), greater<int>());
        sort(king.begin(), king.end(), greater<int>());
        
        // 初始化指针：tianFast/kingFast指向当前最快的马，tianSlow/kingSlow指向当前最慢的马
        int tianFast = 0, tianSlow = n - 1;
        int kingFast = 0, kingSlow = n - 1;
        int win = 0, lose = 0;  // 记录赢和输的场次
        
        // 贪心匹配过程
        while (tianFast <= tianSlow) {
            // 情况1：田忌最快的马能赢齐王最快的马
            if (tian[tianFast] > king[kingFast]) {
                win++;          // 田忌赢一场
                tianFast++;     // 双方最快的马出局
                kingFast++;
            }
            // 情况2：田忌最快的马输给齐王最快的马
            else if (tian[tianFast] < king[kingFast]) {
                lose++;         // 田忌输一场
                tianSlow--;     // 田忌用最慢的马对齐王最快的马
                kingFast++;     // 齐王最快的马出局
            }
            // 情况3：双方最快的马速度相等
            else {
                // 比较双方最慢的马
                if (tian[tianSlow] > king[kingSlow]) {
                    // 田忌最慢的马能赢齐王最慢的马
                    win++;      // 田忌赢一场
                    tianSlow--; // 双方最慢的马出局
                    kingSlow--;
                } else {
                    // 用田忌最慢的马对齐王最快的马
                    if (tian[tianSlow] < king[kingFast]) {
                        lose++; // 只有田忌最慢的马比齐王最快的马慢时才算输
                    }
                    tianSlow--; // 田忌最慢的马出局
                    kingFast++; // 齐王最快的马出局
                }
            }
        }
        
        // 计算最终收益：(赢的场次 - 输的场次) × 200
        int result = (win - lose) * 200;
        cout << result << endl;
    }
    return 0;
}
