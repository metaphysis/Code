// Dominant Strings
// UVa ID: 10745
// Verdict: Accepted
// Submission Date: 2025-10-25
// UVa Run Time: 0.690s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 检查 countA 是否支配 countB
bool checkDomination(const vector<int>& countA, const vector<int>& countB) {
    bool hasStrictlyGreater = false;
    for (int i = 0; i < 26; i++) {
        if (countA[i] < countB[i]) return false;
        if (countA[i] > countB[i]) hasStrictlyGreater = true;
    }
    return hasStrictlyGreater;
}

int main() {
    vector<string> wordList;
    string inputStr;
    
    // 读取输入
    while (cin >> inputStr) {
        wordList.push_back(inputStr);
    }
    
    int totalWords = wordList.size();
    
    // 计算每个单词的字符计数
    vector<vector<int>> charCount(totalWords, vector<int>(26, 0));
    for (int i = 0; i < totalWords; i++) {
        for (char ch : wordList[i]) {
            charCount[i][ch - 'a']++;
        }
    }
    
    vector<bool> isDominated(totalWords, false);
    
    // 比较所有单词对
    for (int i = 0; i < totalWords; i++) {
        if (isDominated[i]) continue;
        for (int j = 0; j < totalWords; j++) {
            if (i == j) continue;
            // 如果 j 支配 i，则标记 i 被支配
            if (checkDomination(charCount[j], charCount[i])) {
                isDominated[i] = true;
                break;
            }
        }
    }
    
    // 收集未被支配的单词
    vector<string> resultList;
    for (int i = 0; i < totalWords; i++) {
        if (!isDominated[i]) {
            resultList.push_back(wordList[i]);
        }
    }
    
    // 按字典序排序
    sort(resultList.begin(), resultList.end());
    
    // 输出结果
    for (const string& word : resultList) {
        cout << word << endl;
    }
    
    return 0;
}
