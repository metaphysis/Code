// Right Words
// UVa ID: 10597
// Verdict: Accepted
// Submission Date: 2026-01-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    string root;
    while (cin >> root) {
        string V, T;
        cin >> V >> T;

        // 存储产生式
        vector<pair<char, string>> productions;
        string line;
        // 读取产生式，直到遇到 # -> #
        while (getline(cin, line)) {
            if (line == "# -> #") break;
            if (line.empty()) continue;
            // 解析产生式，格式如 "A -> BC" 或 "A -> a"
            char left = line[0];
            string right = line.substr(5);
            productions.push_back({left, right});
        }

        // 预处理：将产生式分类存储
        map<char, vector<string>> toTerminal;   // A -> a
        map<string, vector<char>> toNonTerminal; // A -> BC 映射为 BC -> A

        for (auto& prod : productions) {
            char left = prod.first;
            string right = prod.second;
            if (right.size() == 1) {
                // A -> a
                toTerminal[left].push_back(right);
            } else {
                // A -> BC
                toNonTerminal[right].push_back(left);
            }
        }

        // 处理候选字符串
        string candidate;
        while (getline(cin, candidate)) {
            if (candidate == "#") break;
            if (candidate.empty()) continue;

            int n = candidate.size();
            vector<vector<set<char>>> dp(n, vector<set<char>>(n));

            // 初始化：长度为 1 的子串
            for (int i = 0; i < n; i++) {
                char ch = candidate[i];
                for (char nt : V) {
                    if (toTerminal.count(nt)) {
                        for (string& term : toTerminal[nt]) {
                            if (term[0] == ch) {
                                dp[i][i].insert(nt);
                                break;
                            }
                        }
                    }
                }
            }

            // 动态规划：长度从 2 到 n
            for (int len = 2; len <= n; len++) {
                for (int i = 0; i <= n - len; i++) {
                    int j = i + len - 1;
                    for (int k = i; k < j; k++) {
                        // 检查所有可能的 B 和 C 组合
                        for (char B : dp[i][k]) {
                            for (char C : dp[k + 1][j]) {
                                string bc = string(1, B) + C;
                                if (toNonTerminal.count(bc)) {
                                    for (char A : toNonTerminal[bc]) {
                                        dp[i][j].insert(A);
                                    }
                                }
                            }
                        }
                    }
                }
            }

            // 判断根符号是否在 dp[0][n-1] 中
            if (dp[0][n - 1].count(root[0]))
                cout << candidate << " is in L(G)" << endl;
            else
                cout << candidate << " is not in L(G)" << endl;
        }
        cout << endl;
    }
    return 0;
}
