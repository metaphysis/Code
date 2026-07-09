// Codebreakers
// UVa ID: 777
// Verdict: Accepted
// Submission Date: 2026-07-08
// UVa Run Time: 2.150s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 存储单条猜测及其答复
struct Guess {
    vector<char> g; // 猜测序列
    int c, w;       // 正确位置数、错位数
};

// 解析一行猜测‑答复，填充 Guess 结构
void parseLine(const string& line, int m, Guess& guess) {
    string s;
    for (char ch : line)
        if (!isspace(ch)) s.push_back(ch); // 移除所有空白字符

    size_t arrow = s.find("->");
    string left = s.substr(0, arrow);
    string right = s.substr(arrow + 2);

    // 去掉左右括号
    left = left.substr(1, left.size() - 2);
    right = right.substr(1, right.size() - 2);

    // 解析猜测序列（逗号分隔）
    stringstream ss1(left);
    string token;
    while (getline(ss1, token, ',')) {
        if (!token.empty()) guess.g.push_back(token[0]);
    }

    // 解析 c 和 w
    stringstream ss2(right);
    vector<int> nums;
    while (getline(ss2, token, ',')) {
        nums.push_back(stoi(token));
    }
    guess.c = nums[0];
    guess.w = nums[1];
}

// 检查候选密钥是否满足所有猜测
bool checkKey(const vector<char>& key, const vector<Guess>& guesses) {
    int m = key.size();
    for (const auto& guess : guesses) {
        int c = 0, w = 0;
        // 计算正确位置数
        for (int i = 0; i < m; ++i)
            if (key[i] == guess.g[i]) ++c;

        // 统计密钥和猜测中各字符出现次数
        int cntKey[256] = {0}, cntGuess[256] = {0};
        for (char ch : key) cntKey[(unsigned char)ch]++;
        for (char ch : guess.g) cntGuess[(unsigned char)ch]++;

        // 共同字符总数
        int total = 0;
        for (int i = 0; i < 256; ++i)
            total += min(cntKey[i], cntGuess[i]);

        w = total - c; // 错位数 = 共同总数 - 正确位置数

        if (c != guess.c || w != guess.w) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    while (getline(cin, line)) {
        // 跳过空行
        if (line.empty()) continue;

        // 读取字符集 S
        vector<char> S;
        for (char ch : line)
            if (!isspace(ch)) S.push_back(ch);

        // 读取 m
        getline(cin, line);
        while (line.empty()) getline(cin, line);
        int m = stoi(line);

        // 读取所有猜测记录
        vector<Guess> guesses;
        while (true) {
            getline(cin, line);
            if (line.empty()) continue;
            // 去除行首空白
            size_t start = line.find_first_not_of(" \t");
            if (start == string::npos) continue;
            line = line.substr(start);
            if (line[0] == '%') break;

            Guess g;
            parseLine(line, m, g);
            guesses.push_back(g);
        }

        // 枚举所有排列（回溯）
        vector<vector<char>> solutions;
        vector<bool> used(S.size(), false);
        vector<char> cur;

        function<void()> dfs = [&]() {
            if (cur.size() == (size_t)m) {
                if (checkKey(cur, guesses))
                    solutions.push_back(cur);
                return;
            }
            for (size_t i = 0; i < S.size(); ++i) {
                if (!used[i]) {
                    used[i] = true;
                    cur.push_back(S[i]);
                    dfs();
                    cur.pop_back();
                    used[i] = false;
                    // 若已找到两个可行解，无需继续枚举
                    if (solutions.size() > 1) return;
                }
            }
        };

        dfs();

        if (solutions.size() == 1) {
            cout << "(";
            for (int i = 0; i < m; ++i) {
                if (i) cout << ",";
                cout << solutions[0][i];
            }
            cout << ")\n";
        } else {
            cout << "N\n";
        }
    }
    return 0;
}
