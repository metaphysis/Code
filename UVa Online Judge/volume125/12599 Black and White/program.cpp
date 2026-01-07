// Black and White
// UVa ID: 12599
// Verdict: Accepted
// Submission Date: 2026-01-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        string s;
        cin >> s;
        // 检查是否不可解
        if (s.front() != 'B' || s.back() != 'W') {
            cout << "IMPOSSIBLE\n";
            continue;
        }
        // 检查是否前面全是B，后面全是W
        bool allBThenAllW = true;
        int n = s.length();
        int left = 0, right = n - 1;
        while (s[left] == 'B') left++;
        while (s[right] == 'W') right--;
        // 一次操作
        if (left > right) {
            cout << "1\n" << n;
            for (int i = 1; i <= n; i++) cout << ' ' << i;
            cout << '\n';
            continue;
        }
        // 两次操作
        cout << "2\n";
        vector<int> op1;
        int lastW = n - 1;
        for (int i = 1; i < lastW; i++)
            if (s[i] == 'B')
                op1.push_back(i + 1);
        op1.push_back(n);
        cout << op1.size();
        for (int idx : op1) cout << ' ' << idx;
        cout << '\n';
        vector<int> op2;
        op2.push_back(1);
        for (int i = 1; i < n - 1; i++)
            if (s[i] == 'W')
                op2.push_back(i + 1);
        cout << op2.size();
        for (int idx : op2) cout << ' ' << idx;
        cout << '\n';
    }
    
    return 0;
}
