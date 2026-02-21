// Hanoi Towers
// UVa ID: 1414
// Verdict: Accepted
// Submission Date: 2026-02-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 50;
int n;
ll x, y, dp[N];

// 根据策略确定递推参数 (x, y)，使得 dp[n] = dp[n-1] * x + y
void initialize() {
    int firstMove[4] = {0};  // firstMove[i] = 从柱子i第一个合法移动的目标柱, 1:A, 2:B, 3:C
    char s[3];
    
    // 读取6个移动，但只记录每个柱子的第一个合法目标
    for (int i = 0; i < 6; i++) {
        scanf("%s", s);
        int src = s[0] - 'A' + 1;
        int dst = s[1] - 'A' + 1;
        
        if (firstMove[src]) continue;  // 已经记录过该柱子的第一个移动
        firstMove[src] = dst;
    }
    
    // 情况1: 柱子B和C都不能直接移动到A
    if (firstMove[2] != 1 && firstMove[3] != 1) {
        x = 3, y = 0;
    }
    // 情况2: 从A移动到的柱子能够立即移回A
    else if (firstMove[firstMove[1]] == 1) {
        x = 3, y = 2;
    }
    // 情况3: 其他所有情况（包括经典汉诺塔策略）
    else {
        x = 2, y = 1;
    }
}

int main() {
    while (scanf("%d", &n) == 1) {
        initialize();
        dp[1] = 1;  // 1个盘子总是需要1步
        for (int i = 2; i <= n; i++)
            dp[i] = dp[i - 1] * x + y;
        printf("%lld\n", dp[n]);
    }
    return 0;
}
