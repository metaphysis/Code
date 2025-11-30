#include <bits/stdc++.h>
using namespace std;

int main() {
    int testCases;
    cin >> testCases;
    for (int caseNum = 1; caseNum <= testCases; caseNum++) {
        int n;
        cin >> n;
        int oneCount = 0;        // 数字1的个数
        int nonOneStepCount = 0; // 非1数字的消除步数
        int nonOneCount = 0;     // 非1数字的个数
        for (int i = 0; i < n; i++) {
            int num;
            cin >> num;
            if (num == 1) oneCount++;
            else {
                nonOneStepCount += num;  // 每个非1数字需要num次减1操作
                nonOneCount++;
            }
        }
        // 计算非1数字的总消除步数：
        // 1. 减1操作步数：所有非1数字值之和
        // 2. 合并操作步数：nonOneCount-1（将nonOneCount个数字合并成1个需要nonOneCount-1次合并操作）
        if (nonOneCount > 0) {
            nonOneStepCount += nonOneCount - 1;
        }
        string winner;
        if (nonOneStepCount > 2) {
            // 情况1：非1数字消除步数大于2
            // 当非1步数为奇数 或 1的个数为奇数时，先手必胜
            // 证明思路：
            // - 非1步数为奇数，1的个数为偶数：先手对非1数字减1，转移到必败态
            // - 非1步数为偶数，1的个数为奇数：先手对1减1，转移到必败态  
            // - 非1步数为奇数，1的个数为奇数：先手合并1和非1数字，转移到必败态
            winner = (nonOneStepCount % 2 == 1 || oneCount % 2 == 1) ? "Alice" : "Bob";
        } else {
            // 情况2：非1数字消除步数小于等于2（只有0或2两种情况）
            // 当1的个数是3的倍数时，先手必败；否则先手必胜
            // 证明思路：
            // - 1的个数模3余1：先手对1减1，转移到必败态
            // - 1的个数模3余2：先手合并两个1，转移到必败态
            // - 1的个数模3余0：任何操作都会转移到必胜态
            winner = (oneCount % 3 == 0) ? "Bob" : "Alice";
        }
        cout << "Case #" << caseNum << ": " << winner << endl;
    }
    return 0;
}
