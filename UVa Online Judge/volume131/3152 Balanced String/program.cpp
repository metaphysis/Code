// Balanced String
// UVa ID: 13152
// Verdict: Accepted
// Submission Date: 2026-02-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    for (int caseNum = 1; caseNum <= T; ++caseNum) {
        int N;
        cin >> N;
        vector<int> seq(N);
        map<int, int> freqMap;
        int minVal = INT_MAX, maxVal = INT_MIN;
        for (int i = 0; i < N; ++i) {
            cin >> seq[i];
            freqMap[seq[i]]++;
            if (seq[i] < minVal) minVal = seq[i];
            if (seq[i] > maxVal) maxVal = seq[i];
        }

        // 初步检查
        if (N % 2 != 0 || minVal != 0 || maxVal > N / 2) {
            cout << "Case " << caseNum << ": invalid\n";
            continue;
        }

        // 转成数组方便索引
        vector<int> freq(maxVal + 2, 0);
        for (auto &p : freqMap) {
            if (p.first > maxVal) continue;
            freq[p.first] = p.second;
        }

        // 模拟构造
        string ans;
        int cur = 0;
        int leftRemain = N / 2;
        bool valid = true;

        for (int step = 0; step < N; ++step) {
            // 尝试放 '('
            if (cur + 1 <= maxVal && freq[cur + 1] > 0 && leftRemain > 0) {
                ans.push_back('(');
                freq[cur + 1]--;
                cur++;
                leftRemain--;
            } else if (cur > 0 && freq[cur - 1] > 0) {
                // 放 ')'
                ans.push_back(')');
                freq[cur - 1]--;
                cur--;
            } else {
                valid = false;
                break;
            }
        }

        if (!valid || cur != 0) {
            cout << "Case " << caseNum << ": invalid\n";
        } else {
            cout << "Case " << caseNum << ": " << ans << "\n";
        }
    }

    return 0;
}
