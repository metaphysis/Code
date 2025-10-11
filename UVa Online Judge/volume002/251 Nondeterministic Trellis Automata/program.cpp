// Nondeterministic Trellis Automata
// UVa ID: 251
// Verdict: Accepted
// Submission Date: 2025-10-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 清理字符串中的重复字符
void cleanup(string &s) {
    bool used[26] = {};
    int newSize = 0;
    for (int i = 0; i < s.length(); ++i) {
        if (!used[s[i] - 'a']) {
            used[s[i] - 'a'] = true;
            s[newSize++] = s[i];
        }
    }
    s.resize(newSize);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int numStates, numAccept;
    string transitionTable[17][17];  // 转移表
    string dp[17][17][17];           // dp[i][j][k] 表示第 i 层第 j 个处理器的状态集合
    string inputStr;
    for (int caseNum = 1; cin >> numStates >> numAccept && numStates; ++caseNum) {
        if (caseNum > 1) cout << "\n";
        cout << "NTA " << caseNum << "\n";
        cin.ignore(100, '\n'); // 清除换行符
        // 读入转移表
        for (int i = 0; i < numStates; ++i) {
            for (int j = 0; j < numStates; ++j) {
                getline(cin, transitionTable[i][j]);
            }
        }
        // 构建接受状态字符串
        string acceptStates = "";
        for (int i = numStates - numAccept; i < numStates; ++i) {
            acceptStates += 'a' + i;
        }
        // 处理每个输入配置
        while (getline(cin, inputStr) && inputStr != "#") {
            int len = inputStr.length();
            // 单字符输入直接判断
            if (len == 1) {
                if (inputStr[0] - 'a' >= numStates - numAccept) {
                    cout << "accept " << inputStr << "\n";
                } else {
                    cout << "reject " << inputStr << "\n";
                }
                continue;
            }
            // 初始化 dp 数组
            for (int i = 0; i < len; ++i) {
                for (int j = 0; j <= i; ++j) {
                    for (int k = 0; k < numStates; ++k) {
                        dp[i][j][k] = "";
                    }
                }
            }
            // 初始化底部两层
            for (int j = 0; j < len - 1; ++j) {
                int state = inputStr[j] - 'a';
                dp[len - 2][j][state] = inputStr[j + 1];
            }
            // 自底向上动态规划
            for (int i = len - 3; i >= 0; --i) {
                for (int j = 0; j <= i; ++j) {
                    for (int leftState = 0; leftState < numStates; ++leftState) {
                        for (char rightChar : dp[i + 1][j][leftState]) {
                            int rightState = rightChar - 'a';
                            if (!transitionTable[leftState][rightState].empty()) {
                                for (char grandChildChar : dp[i + 1][j + 1][rightState]) {
                                    int grandChildState = grandChildChar - 'a';
                                    for (char parentChar : transitionTable[leftState][rightState]) {
                                        dp[i][j][parentChar - 'a'] += transitionTable[rightState][grandChildState];
                                    }
                                }
                            }
                        }
                    }
                    // 清理重复状态
                    for (int k = 0; k < numStates; ++k) {
                        cleanup(dp[i][j][k]);
                    }
                }
            }
            // 检查顶端是否可能为接受状态
            bool accepted = false;
            for (int topState = 0; topState < numStates; ++topState) {
                for (char childChar : dp[0][0][topState]) {
                    int childState = childChar - 'a';
                    if (transitionTable[topState][childState].find_first_of(acceptStates) != string::npos) {
                        accepted = true;
                        break;
                    }
                }
                if (accepted) break;
            }
            if (accepted) {
                cout << "accept " << inputStr << "\n";
            } else {
                cout << "reject " << inputStr << "\n";
            }
        }
    }
    return 0;
}
