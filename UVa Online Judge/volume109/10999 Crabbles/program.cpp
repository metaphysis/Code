// Crabbles
// UVa ID: 10999
// Verdict: Accepted
// Submission Date: 2025-11-04
// UVa Run Time: 0.840s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 将单词转换为字母频率表
vector<int> convertToLetterCount(const string& word) {
    vector<int> letterCount(26, 0);
    for (char currentChar : word) {
        letterCount[currentChar - 'a']++;
    }
    return letterCount;
}

// 检查手牌是否能组成给定单词
bool canFormWord(const vector<int>& wordCount, const map<char, vector<int>>& handTiles) {
    for (int i = 0; i < 26; i++) {
        if (wordCount[i] > 0) {
            char currentLetter = 'a' + i;
            auto it = handTiles.find(currentLetter);
            if (it == handTiles.end() || it->second.size() < wordCount[i]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int dictionarySize;
    cin >> dictionarySize;
    
    vector<vector<int>> dictionaryWords;
    vector<string> originalWords;
    
    // 读取并预处理词典
    for (int i = 0; i < dictionarySize; i++) {
        string currentWord;
        cin >> currentWord;
        // 只保留长度不超过 10 的单词
        if (currentWord.length() <= 10) {
            dictionaryWords.push_back(convertToLetterCount(currentWord));
            originalWords.push_back(currentWord);
        }
    }
    
    int handCount;
    cin >> handCount;
    
    // 处理每组手牌
    for (int handIndex = 0; handIndex < handCount; handIndex++) {
        int tileCount;
        cin >> tileCount;
        
        // 按字母分组存储拼块分值
        map<char, vector<int>> tileValues;
        
        for (int i = 0; i < tileCount; i++) {
            char tileLetter;
            int tileValue;
            cin >> tileLetter >> tileValue;
            tileValues[tileLetter].push_back(tileValue);
        }
        
        // 对每个字母的分值按降序排序
        for (auto& letterGroup : tileValues) {
            sort(letterGroup.second.rbegin(), letterGroup.second.rend());
        }
        
        int maxScore = 0;
        
        // 遍历词典中的每个单词
        for (int wordIndex = 0; wordIndex < dictionaryWords.size(); wordIndex++) {
            const vector<int>& wordLetterCount = dictionaryWords[wordIndex];
            
            // 检查是否能组成该单词
            if (!canFormWord(wordLetterCount, tileValues)) {
                continue;
            }
            
            // 计算该单词的最大可能分数
            int currentScore = 0;
            for (int letterIndex = 0; letterIndex < 26; letterIndex++) {
                int requiredCount = wordLetterCount[letterIndex];
                if (requiredCount == 0) continue;
                
                char currentLetter = 'a' + letterIndex;
                const vector<int>& values = tileValues.at(currentLetter);
                
                // 取前 requiredCount 个最高分值
                for (int k = 0; k < requiredCount; k++) {
                    currentScore += values[k];
                }
            }
            
            maxScore = max(maxScore, currentScore);
        }
        
        cout << maxScore << "\n";
    }
    
    return 0;
}
