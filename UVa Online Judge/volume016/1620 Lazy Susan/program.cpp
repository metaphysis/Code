// Lazy Susan
// UVa ID: 1620
// Verdict: Accepted
// Submission Date: 2025-10-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        int marbleCount; cin >> marbleCount;
        vector<int> marbleSequence(marbleCount);
        // 读取弹珠序列
        for (int i = 0; i < marbleCount; ++i) cin >> marbleSequence[i];
        // 计算逆序数
        int inversionCount = 0;
        for (int i = 0; i < marbleCount; ++i)
            for (int j = i + 1; j < marbleCount; ++j)
                if (marbleSequence[i] > marbleSequence[j])
                    inversionCount++;
        // 应用判定条件：N 为偶数或逆序数为偶数
        if (marbleCount % 2 == 0 || inversionCount % 2 == 0) cout << "possible\n";
        else cout << "impossible\n";
    }
    return 0;
}
