// Arithmetic Expressions
// UVa ID: 12803
// Verdict: Accepted
// Submission Date: 2025-10-
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdio>
#include <cctype>
#include <cmath>
using namespace std;
// 词法分析函数：将输入字符串分解为token序列
vector<string> tokenize(const string& line) {
    vector<string> tokens;
    string current;
    for (size_t i = 0; i < line.length(); i++) {
        char c = line[i];
        if (isspace(c)) {
            if (!current.empty()) {
                tokens.push_back(current);
                current.clear();
            }
        } else if (c == '(' || c == ')' || c == '+' || c == '*' || c == '/') {
            if (!current.empty()) {
                tokens.push_back(current);
                current.clear();
            }
            tokens.push_back(string(1, c));
        } else if (c == '-') {
            // 区分负号和减号：负号出现在表达式开头、左括号后或运算符后
            if (current.empty() && (tokens.empty() || tokens.back() == "(" || 
                tokens.back() == "+" || tokens.back() == "-" || tokens.back() == "*" || tokens.back() == "/")) {
                current += c;  // 负号，作为数字的一部分
            } else {
                if (!current.empty()) {
                    tokens.push_back(current);
                    current.clear();
                }
                tokens.push_back(string(1, c));  // 减号运算符
            }
        } else {
            current += c;  // 数字部分
        }
    }
    if (!current.empty()) {
        tokens.push_back(current);
    }
    return tokens;
}
// 字符串转浮点数
double str_to_double(const string& s) {
    double value;
    sscanf(s.c_str(), "%lf", &value);
    return value;
}
// 浮点数转字符串，处理四舍五入和负零情况
string double_to_str(double value) {
    double rounded = round(value * 100) / 100;  // 四舍五入到两位小数
    // 处理负零情况：原始值为负且舍入后接近零
    if (fabs(rounded) < 1e-10 && value < 0) {
        return "-0.00";
    }
    if (fabs(rounded) < 1e-10) {
        return "0.00";
    }
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%.2lf", rounded);
    return buffer;
}
// 应用运算符进行计算
double apply_op(double left, double right, const string& op) {
    if (op == "+") return left + right;
    if (op == "-") return left - right;
    if (op == "*") return left * right;
    if (op == "/") return left / right;
    return 0;
}
// 递归下降解析表达式
pair<double, int> parse(const vector<string>& tokens, int idx) {
    if (tokens[idx] == "(") {
        auto left_result = parse(tokens, idx + 1);  // 解析左表达式
        double left_val = left_result.first;
        int pos = left_result.second;
        string op = tokens[pos];  // 获取运算符
        pos++;
        auto right_result = parse(tokens, pos);  // 解析右表达式
        double right_val = right_result.first;
        pos = right_result.second;
        if (pos < tokens.size() && tokens[pos] == ")") {
            pos++;  // 跳过右括号
        }
        return {apply_op(left_val, right_val, op), pos};
    } else {
        return {str_to_double(tokens[idx]), idx + 1};  // 数字直接转换
    }
}
int main() {
    int N;
    cin >> N;
    cin.ignore();  // 忽略换行符
    for (int i = 0; i < N; i++) {
        string line;
        getline(cin, line);
        vector<string> tokens = tokenize(line);  // 词法分析
        auto result = parse(tokens, 0);  // 语法分析并求值
        cout << double_to_str(result.first) << endl;  // 格式化输出
    }
    return 0;
}
