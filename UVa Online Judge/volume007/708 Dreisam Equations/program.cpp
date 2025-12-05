// Dreisam Equations
// UVa ID: 708
// Verdict: Accepted
// Submission Date: 2025-12-04
// UVa Run Time: 0.030s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;

bool found;
long long leftValue;
string s;
vector<int> idxer;

// 计算表达式的值（从左到右，括号优先）
pair<long long, int> evaluate(int pos) {
    long long result = 0;
    char lastOp = '+';  // 第一个数字视为加法
    long long currentNum = 0;
    bool hasNum = false;
    while (pos < s.size() && s[pos] != ')') {
        char c = s[pos];
        if (isdigit(c)) {
            // 解析数字
            currentNum = currentNum * 10 + (c - '0');
            hasNum = true;
            pos++;
        } else if (c == '(') {
            // 递归计算括号内的值
            auto [subResult, newPos] = evaluate(pos + 1);
            currentNum = subResult;
            hasNum = true;
            pos = newPos + 1;  // 跳过')'
        } else if (c == '+' || c == '-' || c == '*') {
            // 遇到运算符，应用上一个运算符到结果
            if (hasNum) {
                if (lastOp == '+') result += currentNum;
                else if (lastOp == '-') result -= currentNum;
                else result *= currentNum;
                currentNum = 0;
                hasNum = false;
            }
            lastOp = c;
            pos++;
        }
    }
    // 处理最后一个数字
    if (hasNum) {
        if (lastOp == '+') result += currentNum;
        else if (lastOp == '-') result -= currentNum;
        else result *= currentNum;
    }
    return {result, pos};
}

void dfs(int idx) {
    if (found) return;
    if (idx == idxer.size()) {
        auto [v, _] = evaluate(0);
        if (v == leftValue) {
            cout << leftValue << '=' << s << '\n';
            found = true;
        }
        return;
    }
    for (int i = 0; i < 3; i++) {
        s[idxer[idx]] = "+-*"[i];
        dfs(idx + 1);
        if (found) return;
    }
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    string line;
    int cs = 1;
    while (getline(cin, line)) {
        if (line == "0") break;
        istringstream iss(line);
        // 读入左侧值和等号
        char equal;
        long long v;
        iss >> leftValue >> equal;
        // 解析右侧表达式
        string token;
        vector<string> terms;
        while(iss >> token) terms.push_back(token);
        // 将表达式解析为紧凑形式，运算符位置使用 # 代替
        s.clear();
        s += terms.front();
        for (int i = 1; i < terms.size(); i++) {
            if (s.back() != '(' && terms[i].front() != ')') s += "#";
            s += terms[i];
        }
        // 进一步检查是否还有遗漏，因为输入可能非常“恶心”
        string normalized;
        normalized += s.front();
        for (int i = 1; i < s.size(); i++) {
            if (normalized.back() == ')' && s[i] == '(') normalized += "#";
            if (isdigit(normalized.back()) && s[i] == '(') normalized += '#';
            if (normalized.back() == ')' && isdigit(s[i])) normalized += '#';
            normalized += s[i];
        }
        s = normalized;
        cout << "Equation #" << cs << ":\n";
        found = false;
        // 确定运算符位置
        idxer.clear();
        for (int i = 0; i < s.size(); i++)
            if (s[i] == '#')
                idxer.push_back(i);
        // 回溯构造表达式
        dfs(0);
        if (!found) cout << "Impossible.\n";
        cout << '\n';
        cs++;
    }
    return 0;
}
