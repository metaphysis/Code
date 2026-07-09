// Morse Code Generation
// UVa ID: 730
// Verdict: Accepted
// Submission Date: 2026-07-08
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    unordered_map<char, string> morse;
    string line;
    // 读取映射表，直到单独一行的 '@'
    while (getline(cin, line) && line != "@") {
        if (line.empty()) continue;
        stringstream ss(line);
        char ch;
        string code;
        ss >> ch >> code;
        morse[ch] = code;
    }
    bool firstDataset = true;
    int wpm;
    // 循环读取每个数据集
    while (cin >> wpm) {
        cin.ignore(); // 忽略 wpm 后的换行
        // 读取报文行，直到遇到下一个 '@' 或 EOF
        vector<string> msgLines;
        while (getline(cin, line) && line != "@") {
            msgLines.push_back(line);
        }
        // 拼接报文，换行处插入空格（除最后一行）
        string msg;
        for (size_t i = 0; i < msgLines.size(); ++i) {
            msg += msgLines[i];
            if (i + 1 < msgLines.size()) msg += ' ';
        }
        // 提取有效字符，并记录其后是否有空格（单词分隔）
        vector<pair<char, bool>> chars; // {字符, 是否单词分隔}
        for (size_t i = 0; i < msg.size(); ) {
            if (isalnum(msg[i])) {
                char ch = toupper(msg[i]);
                size_t j = i + 1;
                bool hasSpace = false;
                while (j < msg.size() && msg[j] == ' ') {
                    hasSpace = true;
                    ++j;
                }
                chars.push_back({ch, hasSpace});
                i = j;
            } else ++i;
        }
        // 计算时间参数（使用 double 保持精度，最后四舍五入）
        const double baseDot = 60000.0 / 520.0; // 13 wpm 基准点长
        double dot_real, intra_real;
        if (wpm < 13) {
            dot_real = baseDot;
            intra_real = 60000.0 / (wpm * 40.0);
        } else {
            dot_real = 60000.0 / (wpm * 40.0);
            intra_real = dot_real;
        }
        int dot = (int)round(dot_real);
        int dash = (int)round(3.0 * dot_real);
        int intra = (int)round(intra_real);
        int interChar = (int)round(3.0 * intra_real);
        int interWord = (int)round(9.0 * intra_real); // 3 * interChar
        // 两个数据集之间输出空行
        if (!firstDataset) cout << '\n';
        firstDataset = false;
        // 逐个输出字符
        for (const auto& p : chars) {
            char ch = p.first;
            bool wordSep = p.second;
            string code = morse[ch]; // 查表得到摩尔斯码
            cout << ch;
            // 输出每个符号的 on 和 off（off 为内部间隔）
            for (char c : code) {
                int on = (c == '.') ? dot : dash;
                cout << ' ' << on << " S";
                cout << ' ' << intra << " N";
            }
            // 输出字符间间隔
            cout << ' ' << interChar << " N";
            cout << '\n';
            // 若该字符后是单词分隔，额外输出一行（两个空格缩进）
            if (wordSep) cout << "  " << interWord << " N\n";
        }
    }
    return 0;
}
