// Text Comparison
// UVa ID: 287
// Verdict: Accepted
// Submission Date: 2026-05-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Token {
    string raw;      // 原始内容（含大小写）
    string low;      // 小写内容（用于比较）
    int pos;         // 在原字符串中的起始位置
    int len;         // 长度
    bool isWord;     // 是否为单词（字母组成）
};

// 将字符串转为小写
string toLower(const string& s) {
    string res = s;
    for (char& c : res) c = tolower(c);
    return res;
}

// 分词：单词包含尾随空格，但标点单独处理
vector<Token> splitTokens(const string& s) {
    vector<Token> tokens;
    int n = s.size();
    int i = 0;
    
    while (i < n) {
        if (isalpha(s[i]) || s[i] == '\'') {
            int start = i;
            string word = "";
            while (i < n && (isalpha(s[i]) || s[i] == '\'')) {
                word += s[i];
                ++i;
            }
            // 单词后面的空格作为单词的一部分
            while (i < n && s[i] == ' ') {
                word += s[i];
                ++i;
            }
            string lowWord = toLower(word);
            string trimWord = word;
            while (!trimWord.empty() && trimWord.back() == ' ') trimWord.pop_back();
            bool isWordFlag = true;
            for (char c : trimWord) if (!isalpha(c) && c != '\'') { isWordFlag = false; break; }
            tokens.push_back({word, lowWord, start, (int)word.size(), isWordFlag});
        } else if (s[i] == ' ') {
            // 单独的空格（不应该出现，因为上面已经处理了）
            ++i;
        } else {
            // 标点符号
            int start = i;
            string punct = string(1, s[i]);
            ++i;
            // 标点后面的空格
            while (i < n && s[i] == ' ') {
                punct += s[i];
                ++i;
            }
            string lowPunct = toLower(punct);
            tokens.push_back({punct, lowPunct, start, (int)punct.size(), false});
        }
    }
    return tokens;
}

// 计算 LCS 匹配位置
vector<pair<int, int>> getLcsMatches(const vector<Token>& oldTokens, const vector<Token>& newTokens) {
    int n = oldTokens.size(), m = newTokens.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (oldTokens[i - 1].low == newTokens[j - 1].low)
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    
    vector<pair<int, int>> matches;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (oldTokens[i - 1].low == newTokens[j - 1].low) {
            matches.push_back({i - 1, j - 1});
            --i; --j;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            --i;
        } else {
            --j;
        }
    }
    reverse(matches.begin(), matches.end());
    return matches;
}

// 去除字符串末尾的空格，并转为小写
string formatOutput(const string& s, bool keepSpace = true) {
    string res = s;
    // 转为小写
    for (char& c : res) c = tolower(c);
    // 去除末尾空格（单词本身不包含尾随空格）
    if (!keepSpace) {
        while (!res.empty() && res.back() == ' ') res.pop_back();
    }
    return res;
}

void processTestCase(const string& text1, const string& text2) {
    vector<Token> oldTokens = splitTokens(text2);
    vector<Token> newTokens = splitTokens(text1);
    
    vector<pair<int, int>> matches = getLcsMatches(oldTokens, newTokens);
    
    int oldIdx = 0, newIdx = 0;
    
    for (size_t k = 0; k <= matches.size(); ++k) {
        int oldEnd = (k < matches.size()) ? matches[k].first : oldTokens.size();
        int newEnd = (k < matches.size()) ? matches[k].second : newTokens.size();
        
        string oldStr = "", newStr = "";
        int oldStartPos = (oldIdx < oldTokens.size()) ? oldTokens[oldIdx].pos : 0;
        
        for (int i = oldIdx; i < oldEnd; ++i)
            oldStr += oldTokens[i].raw;
        for (int j = newIdx; j < newEnd; ++j)
            newStr += newTokens[j].raw;
        
        if (!oldStr.empty() || !newStr.empty()) {
            bool oldHasChar = false, newHasChar = false;
            for (char c : oldStr) if (!isspace(c)) { oldHasChar = true; break; }
            for (char c : newStr) if (!isspace(c)) { newHasChar = true; break; }
            
            if (oldHasChar && !newHasChar) {
                // 删除：输出小写形式，保留尾随空格
                cout << "pos " << oldStartPos << " deleted " << oldStr.size() 
                     << " chars \"" << formatOutput(oldStr, true) << "\"\n";
            } else if (!oldHasChar && newHasChar) {
                // 插入：输出小写形式，保留尾随空格
                cout << "pos " << oldStartPos << " inserted " << newStr.size() 
                     << " chars \"" << formatOutput(newStr, true) << "\"\n";
            } else if (oldHasChar && newHasChar) {
                // 修改：只输出单词本身（不包含尾随空格和标点），转为小写
                string oldWord = formatOutput(oldStr, false);
                string newWord = formatOutput(newStr, false);
                // 去除标点符号（只保留字母和单引号）
                string cleanOld = "", cleanNew = "";
                for (char c : oldWord) if (isalpha(c) || c == '\'') cleanOld += c;
                for (char c : newWord) if (isalpha(c) || c == '\'') cleanNew += c;
                
                cout << "pos " << oldStartPos << " changed " << oldStr.size() 
                     << " chars from \"" << cleanOld << "\" to \"" << cleanNew << "\"\n";
            }
        }
        
        if (k < matches.size()) {
            oldIdx = matches[k].first + 1;
            newIdx = matches[k].second + 1;
        }
    }
}

int main() {
    string line1, line2;
    
    while (getline(cin, line1) && getline(cin, line2)) {
        string text1, text2;
        
        size_t colonPos1 = line1.find(':');
        size_t colonPos2 = line2.find(':');
        
        if (colonPos1 != string::npos)
            text1 = line1.substr(colonPos1 + 1);
        else
            text1 = line1;
            
        if (colonPos2 != string::npos)
            text2 = line2.substr(colonPos2 + 1);
        else
            text2 = line2;
        
        if (!text1.empty() && text1[0] == ' ') text1 = text1.substr(1);
        if (!text2.empty() && text2[0] == ' ') text2 = text2.substr(1);
        
        processTestCase(text1, text2);
        cout << "\n";
    }
    
    return 0;
}
