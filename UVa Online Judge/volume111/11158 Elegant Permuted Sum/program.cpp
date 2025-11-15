// Elegant Permuted Sum
// UVa ID: 11158
// Verdict: Accepted
// Submission Date: 2025-11-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main() {
    int testCases;
    cin >> testCases;
    
    for (int caseNum = 1; caseNum <= testCases; ++caseNum) {
        int n;
        cin >> n;
        vector<int> numbers(n);
        for (int i = 0; i < n; ++i) {
            cin >> numbers[i];
        }
        
        // 处理特殊情况：只有一个元素时，没有相邻元素，和为 0
        if (n == 1) {
            cout << "Case " << caseNum << ": 0" << endl;
            continue;
        }
        
        // 对数组进行排序，便于后续的贪心选择
        sort(numbers.begin(), numbers.end());
        deque<int> remainingNumbers(numbers.begin(), numbers.end());
        deque<int> resultSequence;
        
        // 初始化：用最小值和最大值开始构建序列
        resultSequence.push_back(remainingNumbers.front());
        resultSequence.push_back(remainingNumbers.back());
        remainingNumbers.pop_front();
        remainingNumbers.pop_back();
        
        // 贪心构建序列：每次选择能产生最大差异的放置方式
        while (!remainingNumbers.empty()) {
            int currentMin = remainingNumbers.front();
            int currentMax = remainingNumbers.back();
            
            // 计算四种可能的放置方式产生的差异
            int diffMinFront = abs(currentMin - resultSequence.front());
            int diffMinBack = abs(currentMin - resultSequence.back());
            int diffMaxFront = abs(currentMax - resultSequence.front());
            int diffMaxBack = abs(currentMax - resultSequence.back());
            
            // 选择能产生最大差异的放置方式
            int maxDifference = max({diffMinFront, diffMinBack, diffMaxFront, diffMaxBack});
            
            if (maxDifference == diffMinFront) {
                // 将最小值放在序列头部
                resultSequence.push_front(currentMin);
                remainingNumbers.pop_front();
            } else if (maxDifference == diffMinBack) {
                // 将最小值放在序列尾部
                resultSequence.push_back(currentMin);
                remainingNumbers.pop_front();
            } else if (maxDifference == diffMaxFront) {
                // 将最大值放在序列头部
                resultSequence.push_front(currentMax);
                remainingNumbers.pop_back();
            } else {
                // 将最大值放在序列尾部
                resultSequence.push_back(currentMax);
                remainingNumbers.pop_back();
            }
        }
        
        // 计算最终序列的相邻元素绝对差之和
        int totalSum = 0;
        for (int i = 1; i < n; i++) {
            totalSum += abs(resultSequence[i] - resultSequence[i - 1]);
        }
        
        cout << "Case " << caseNum << ": " << totalSum << endl;
    }
    
    return 0;
}
