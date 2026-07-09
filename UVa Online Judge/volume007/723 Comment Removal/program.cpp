// Comment Removal
// UVa ID: 723
// Verdict: Accepted
// Submission Date: 2026-07-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 第一步：压缩空格（字符串常量内除外）
// 将非字符串区域内的连续空格替换为单个空格
string compressSpaces(const string& s) {
    string res;
    int n = (int)s.size();
    bool inString = false;
    for (int i = 0; i < n; ) {
        if (!inString) {
            if (s[i] == '\'') {
                inString = true;
                res.push_back(s[i]);
                ++i;
            } else if (s[i] == ' ') {
                res.push_back(' ');
                while (i < n && s[i] == ' ') ++i;
            } else {
                res.push_back(s[i]);
                ++i;
            }
        } else {
            res.push_back(s[i]);
            if (s[i] == '\'') {
                if (i + 1 < n && s[i + 1] == '\'') {
                    res.push_back(s[i + 1]);
                    i += 2;
                } else {
                    inString = false;
                    ++i;
                }
            } else ++i;
        }
    }
    return res;
}

// 第二步：删除注释（(* *) 和 { }），同样需要区分字符串常量
string removeComments(const string& s) {
    string res;
    int n = (int)s.size();
    bool inString = false;
    for (int i = 0; i < n; ) {
        if (!inString) {
            if (i + 1 < n && s[i] == '(' && s[i + 1] == '*') {
                i += 2;
                while (i + 1 < n && !(s[i] == '*' && s[i + 1] == ')')) ++i;
                if (i + 1 < n) i += 2;
                continue;
            }
            if (s[i] == '{') {
                ++i;
                while (i < n && s[i] != '}') ++i;
                if (i < n) ++i;
                continue;
            }
            if (s[i] == '\'') {
                inString = true;
                res.push_back(s[i]);
                ++i;
            } else {
                res.push_back(s[i]);
                ++i;
            }
        } else {
            res.push_back(s[i]);
            if (s[i] == '\'') {
                if (i + 1 < n && s[i + 1] == '\'') {
                    res.push_back(s[i + 1]);
                    i += 2;
                } else {
                    inString = false;
                    ++i;
                }
            } else ++i;
        }
    }
    return res;
}

// 第三步：删除完全空白的行（仅包含空格和换行符的行）
string removeBlankLines(const string& s) {
    vector<string> lines;
    string line;
    istringstream iss(s);
    while (getline(iss, line)) {
        bool onlySpaces = true;
        for (char c : line) {
            if (c != ' ') {
                onlySpaces = false;
                break;
            }
        }
        if (!onlySpaces) lines.push_back(line);
    }
    string result;
    for (size_t i = 0; i < lines.size(); ++i) {
        result += lines[i];
        if (i + 1 < lines.size()) result += '\n';
    }
    if (!lines.empty()) result += '\n';
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string input, line;
    while (getline(cin, line)) {
        input += line;
        input += '\n';
    }
    string step1 = compressSpaces(input);
    string step2 = removeComments(step1);
    string output = removeBlankLines(step2);
    cout << output;
    return 0;
}
