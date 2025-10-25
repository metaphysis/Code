// Felipe and the Sequence
// UVa ID: 13187
// Verdict: Accepted
// Submission Date: 2025-10-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int testCaseCount;
    cin >> testCaseCount;
    
    while (testCaseCount--) {
        long long targetSum;
        cin >> targetSum;
        // 根据公式 n = S^2 + 2S 计算所需项数
        long long termCount = targetSum * targetSum + 2 * targetSum;
        cout << termCount << "\n";
    }
    
    return 0;
}
