// According to Bartjens
// UVa ID: 817
// Verdict: Accepted
// Submission Date: 2025-11-05
// UVa Run Time: 0.520s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <cctype>

using namespace std;

vector<string> results;
string digits;
int n;

// 检查数字是否有效（没有前导零）
bool isValidNumber(const string& num) {
    return num.size() == 1 || num[0] != '0';
}

// 计算表达式的值
long long calculate(const vector<string>& tokens) {
    // 先处理乘法
    vector<long long> values;
    vector<char> ops;
    
    long long current = stoll(tokens[0]);
    
    for (int i = 1; i < tokens.size(); i += 2) {
        char op = tokens[i][0];
        long long next = stoll(tokens[i + 1]);
        
        if (op == '*') {
            current *= next;
        } else {
            values.push_back(current);
            ops.push_back(op);
            current = next;
        }
    }
    values.push_back(current);
    
    // 处理加法和减法
    long long result = values[0];
    for (int i = 0; i < ops.size(); i++) {
        if (ops[i] == '+') {
            result += values[i + 1];
        } else {
            result -= values[i + 1];
        }
    }
    
    return result;
}

// 检查是否至少有一个运算符
bool hasOperator(const vector<string>& tokens) {
    for (const string& token : tokens) {
        if (token == "+" || token == "-" || token == "*") {
            return true;
        }
    }
    return false;
}

// 递归生成所有可能的表达式
void generateExpressions(int pos, vector<string>& current, string currentNum) {
    if (pos == n) {
        if (!isValidNumber(currentNum)) return;
        
        current.push_back(currentNum);
        
        // 必须至少有一个运算符
        if (hasOperator(current)) {
            // 计算表达式值
            if (calculate(current) == 2000) {
                string expr;
                for (const string& token : current) {
                    expr += token;
                }
                expr += "=";
                results.push_back(expr);
            }
        }
        
        current.pop_back();
        return;
    }
    
    // 情况1：继续延长当前数字（如果没有前导零问题）
    if (isValidNumber(currentNum + digits[pos])) {
        generateExpressions(pos + 1, current, currentNum + digits[pos]);
    }
    
    // 情况2：在当前数字后插入运算符（确保currentNum不为空）
    if (!currentNum.empty() && isValidNumber(currentNum)) {
        // 尝试 +, -, *
        vector<char> operators = {'+', '-', '*'};
        for (char op : operators) {
            current.push_back(currentNum);
            current.push_back(string(1, op));
            
            // 确保运算符后面有数字（从下一个位置开始）
            string nextNum = string(1, digits[pos]);
            generateExpressions(pos + 1, current, nextNum);
            
            current.pop_back();
            current.pop_back();
        }
    }
}

int main() {
    string line;
    int caseNum = 1;
    
    while (getline(cin, line) && line != "=") {
        // 移除等号及后面的空格
        size_t equalPos = line.find('=');
        digits = line.substr(0, equalPos);
        n = digits.size();
        
        results.clear();
        vector<string> current;
        
        generateExpressions(0, current, "");
        
        // 去重
        set<string> uniqueResults(results.begin(), results.end());
        
        cout << "Problem " << caseNum++ << endl;
        if (uniqueResults.empty()) {
            cout << "  IMPOSSIBLE" << endl;
        } else {
            for (const string& result : uniqueResults) {
                cout << "  " << result << endl;
            }
        }
    }
    
    return 0;
}
