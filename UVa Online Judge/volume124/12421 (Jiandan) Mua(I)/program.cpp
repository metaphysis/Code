// (Jiandan) Mua(I)
// UVa ID: 12421
// Verdict: Accepted
// Submission Date: 2025-12-31
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 保留字集合
const unordered_set<string> reservedWords = {
    "and", "break", "do", "else", "elseif", "end",
    "false", "for", "function", "if", "in", "local",
    "nil", "not", "or", "repeat", "return", "then",
    "true", "until", "while"
};

// 符号集合（按长度降序排列，确保贪婪匹配）
const vector<string> symbols = {
    "...", "..",      // 三字符和两字符符号在前
    "==", "~=", "<=", ">=",
    "+", "-", "*", "/", "%", "~", "#",
    "<", ">", "=",
    "(", ")", "{", "}", "[", "]",
    ";", ":", ",", "."
};

// 辅助函数：判断字符是否为字母
bool isAlpha(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

// 辅助函数：判断字符是否为数字
bool isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

// 辅助函数：判断字符是否为十六进制数字
bool isHexDigit(char ch) {
    return isDigit(ch) || (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F');
}

// 辅助函数：判断字符是否为空白（不包括换行）
bool isSpace(char ch) {
    return ch == ' ' || ch == '\t' || ch == '\r';
}

// 主词法分析函数
vector<pair<string, string>> lex(const string& program) {
    vector<pair<string, string>> tokens;
    int n = program.size();
    int i = 0;

    while (i < n) {
        // 跳过空白
        if (isSpace(program[i])) {
            i++;
            continue;
        }

        // 处理注释
        if (i + 1 < n && program[i] == '-' && program[i + 1] == '-') {
            while (i < n && program[i] != '\n') i++;
            // 注释后的换行符由后续循环处理
            continue;
        }

        // 处理换行（EOL）
        if (program[i] == '\n') {
            tokens.emplace_back("EOL", "");
            i++;
            continue;
        }

        // 处理字符串
        if (program[i] == '"' || program[i] == '\'') {
            char quote = program[i];
            int start = i;
            i++; // 跳过开头的引号
            while (i < n && program[i] != quote) {
                if (program[i] == '\\') {
                    // 处理转义字符
                    if (i + 1 < n && (program[i + 1] == '\\' || program[i + 1] == '"' ||
                                      program[i + 1] == '\'' || program[i + 1] == 'n'))
                        i += 2;
                    else
                        i++; // 非法转义，按普通字符处理（根据题目，输入合法）
                } else
                    i++;
            }
            if (i < n) i++; // 跳过结尾的引号
            tokens.emplace_back("STRING", program.substr(start, i - start));
            continue;
        }

        // 处理数字（整数、浮点数、十六进制）
        if (isDigit(program[i]) || (program[i] == '.' && i + 1 < n && isDigit(program[i + 1]))) {
            int start = i;
            bool isHex = false;
            bool isFloat = false;

            // 检查十六进制前缀
            if (program[i] == '0' && i + 1 < n && (program[i + 1] == 'x' || program[i + 1] == 'X')) {
                isHex = true;
                i += 2;
                while (i < n && isHexDigit(program[i])) i++;
            } else {
                // 十进制整数或浮点数
                while (i < n && isDigit(program[i])) i++;
                if (i < n && program[i] == '.') {
                    isFloat = true;
                    i++;
                    while (i < n && isDigit(program[i])) i++;
                }
                if (i < n && (program[i] == 'e' || program[i] == 'E')) {
                    isFloat = true;
                    i++;
                    if (i < n && (program[i] == '+' || program[i] == '-')) i++;
                    while (i < n && isDigit(program[i])) i++;
                }
            }
            tokens.emplace_back("NUMBER", program.substr(start, i - start));
            continue;
        }

        // 处理符号（按长度降序匹配，确保贪婪）
        bool foundSymbol = false;
        for (const string& sym : symbols) {
            if (program.compare(i, sym.size(), sym) == 0) {
                tokens.emplace_back("SYMBOL", sym);
                i += sym.size();
                foundSymbol = true;
                break;
            }
        }
        if (foundSymbol) continue;

        // 处理名称和保留字
        if (isAlpha(program[i]) || program[i] == '_') {
            int start = i;
            while (i < n && (isAlpha(program[i]) || isDigit(program[i]) || program[i] == '_')) i++;
            string name = program.substr(start, i - start);
            string type = reservedWords.count(name) ? "RESERVED" : "NAME";
            tokens.emplace_back(type, name);
            continue;
        }

        // 如果遇到无法识别的字符，跳过（根据题目，输入合法，不会发生）
        i++;
    }

    return tokens;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    string program;
    while (getline(cin, line)) {
        program += line + '\n'; // 保留换行符以识别 EOL
    }

    auto tokens = lex(program);
    for (const auto& [type, token] : tokens) {
        if (type == "EOL")
            cout << "[EOL]\n";
        else
            cout << "[" << type << "] " << token << "\n";
    }

    return 0;
}
