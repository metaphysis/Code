// Automatic Cheater Detection
// UVa ID: 1726
// Verdict: Accepted
// Submission Date: 2025-11-04
// UVa Run Time: 0.170s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int testCaseCount;
    cin >> testCaseCount;
    
    while (testCaseCount--) {
        int questionCount;
        cin >> questionCount;
        
        // 统计数组：下标 1~10 对应难度 1~10
        int leakedCorrect[11] = {0};          // 泄露且答对的题目数
        int notLeakedIncorrect[11] = {0};     // 未泄露且答错的题目数
        
        // 读取并统计每道题目的信息
        for (int i = 0; i < questionCount; i++) {
            int difficulty, status;
            char result;
            cin >> difficulty >> status >> result;
            
            if (status == 1 && result == 'c') {
                leakedCorrect[difficulty]++;
            } else if (status == 0 && result == 'i') {
                notLeakedIncorrect[difficulty]++;
            }
        }
        
        // 计算前缀和：prefixIncorrect[k] 表示难度 ≤ k 的未泄露答错题目总数
        int prefixIncorrect[11] = {0};
        for (int k = 1; k <= 10; k++) {
            prefixIncorrect[k] = prefixIncorrect[k - 1] + notLeakedIncorrect[k];
        }
        
        // 计算总可疑行为数
        long long totalSuspicious = 0;
        for (int d1 = 2; d1 <= 10; d1++) {  // d1 从 2 开始，因为需要 d1 > d2
            if (leakedCorrect[d1] > 0) {
                totalSuspicious += (long long)leakedCorrect[d1] * prefixIncorrect[d1 - 1];
            }
        }
        
        cout << totalSuspicious << "\n";
    }
    
    return 0;
}
