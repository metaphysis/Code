// Special Number
// UVa ID: 11533
// Verdict: Accepted
// Submission Date: 2026-06-05
// UVa Run Time: 0.120s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int N, X, Y, caseNum = 1;
    while (cin >> N >> X >> Y) {
        cout << "Case " << caseNum++ << ":";
        
        // 特殊处理 X = 0
        if (X == 0) {
            cout << " 0\n";
            continue;
        }
        // 特殊处理 Y = 0
        if (Y == 0) {
            cout << " No solution\n";
            continue;
        }
        
        vector<int> digits;
        digits.push_back(X);  // 个位
        long long carry = 0;
        bool found = false;
        
        // 模拟乘法过程，最多尝试 100000 次
        for (int step = 1; step <= 100000; ++step) {
            long long val = carry + (long long)digits.back() * Y;
            int newDigit = val % N;
            carry = val / N;
            digits.push_back(newDigit);
            
            // 检查是否回到起点：进位为 0 且当前位等于 X
            if (carry == 0 && newDigit == X) {
                digits.pop_back();  // 去掉重复的 X
                found = true;
                break;
            }
        }
        
        if (!found) {
            cout << " No solution\n";
            continue;
        }
        
        // 反转得到从高位到低位的顺序
        reverse(digits.begin(), digits.end());
        for (int d : digits) cout << " " << d;
        cout << "\n";
    }
    return 0;
}
