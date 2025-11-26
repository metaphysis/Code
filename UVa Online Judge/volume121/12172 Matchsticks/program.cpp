// Matchsticks
// UVa ID: 12172
// Verdict: Accepted
// Submission Date: 2025-11-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 每个数字0-9所需的火柴棍数量
vector<int> cost = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

// 获取使用n根火柴棍能组成的最小数字
string getMinNumber(int n) {
    // dp[i]表示使用i根火柴棍能组成的最小数字
    vector<string> minSticks(n + 1, "#");
    minSticks[0] = "";
    
    for (int i = 1; i <= n; i++) {
        for (int d = 0; d <= 9; d++) {
            if (i - cost[d] >= 0 && minSticks[i - cost[d]] != "#") {
                // 避免前导零：当minSticks[i-cost[d]]为空时，不能加0
                if (minSticks[i - cost[d]] == "" && d == 0) continue;
                
                string newNum = minSticks[i - cost[d]] + to_string(d);
                
                // 更新最小数字：先比较位数，位数相同再比较数值
                if (minSticks[i] == "#" || 
                    newNum.length() < minSticks[i].length() || 
                    (newNum.length() == minSticks[i].length() && newNum < minSticks[i])) {
                    minSticks[i] = newNum;
                }
            }
        }
    }
    return minSticks[n];
}

// 获取使用n根火柴棍能组成的最大数字
string getMaxNumber(int n) {
    // 偶数：全部用1（2根火柴棍）
    if (n % 2 == 0) return string(n / 2, '1');
    // 奇数：先用3根组成7，剩下的用1
    else return "7" + string((n - 3) / 2, '1');
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << getMinNumber(n) << " " << getMaxNumber(n) << endl;
    }
    return 0;
}
