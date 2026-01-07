// Placing the Ops
// UVa ID: 695
// Verdict: Accepted
// Submission Date: 2026-01-02
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int caseNum = 1;  // 测试用例编号

// 计算表达式的值（从左到右，优先级相同）
int evaluate(const vector<int>& nums, const vector<char>& ops) {
    int answer = nums[0];
    for (size_t i = 0; i < ops.size(); ++i) {
        int next = nums[i + 1];
        char op = ops[i];
        if (op == '+') answer += next;
        else if (op == '-') answer -= next;
        else if (op == '*') answer *= next;
        else { // 除法
            if (next == 0) return INT_MAX;  // 除零错误
            answer /= next;  // 整数除法
        }
    }
    return answer;
}

// 检查数字是否有效（无前导零，除非数字就是0）
bool isValidNumber(const string& numStr) {
    if (numStr.length() > 1 && numStr[0] == '0') return false;
    return true;
}

vector<vector<int>> assigned;  // 存储所有长度分配方案
vector<int> tmp;  // 当前正在构建的长度分配方案

// 使用递归生成所有长度组合（将remaining个字符分成parts个数字）
void dfs(int remaining, int parts) {
    if (parts == 0) {
        if (remaining == 0) assigned.push_back(tmp);
        return;
    }
    // 每个数字至少1位，最多 remaining - (parts - 1) 位
    for (int len = 1; len <= remaining - (parts - 1); ++len) {
        tmp.push_back(len);
        dfs(remaining - len, parts - 1);
        tmp.pop_back();
    }
}

bool solve(const string& equation, const string& ops) {
    int eqPos = equation.find('=');  // 等号位置
    string leftStr = equation.substr(0, eqPos);  // 等号左边的数字字符
    string rightStr = equation.substr(eqPos + 1);  // 等号右边的数字字符
    int totalOps = ops.size();  // 运算符总数
    
    // 枚举左边运算符数量
    for (int leftOps = 0; leftOps <= totalOps; ++leftOps) {
        int rightOps = totalOps - leftOps;
        int leftDigits = leftOps + 1;  // 左边需要的数字数量
        int rightDigits = rightOps + 1;  // 右边需要的数字数量
        
        // 检查字符数量是否足够
        if (leftDigits > (int)leftStr.size()) continue;
        if (rightDigits > (int)rightStr.size()) continue;
        
        // 生成左边数字的所有位数分配方案
        tmp.clear();
        assigned.clear();
        dfs(leftStr.size(), leftDigits);
        vector<vector<int>> leftLengths = assigned;
        
        // 生成右边数字的所有位数分配方案
        tmp.clear();
        assigned.clear();
        dfs(rightStr.size(), rightDigits);
        vector<vector<int>> rightLengths = assigned;
        
        // 尝试所有左右长度组合
        for (const auto& leftLen : leftLengths) {
            for (const auto& rightLen : rightLengths) {
                // 构建左边的数字
                vector<int> leftNums;
                int pos = 0;
                bool valid = true;
                for (int len : leftLen) {
                    string numStr = leftStr.substr(pos, len);
                    if (!isValidNumber(numStr)) {
                        valid = false;
                        break;
                    }
                    leftNums.push_back(stoi(numStr));
                    pos += len;
                }
                if (!valid) continue;
                
                // 构建右边的数字
                vector<int> rightNums;
                pos = 0;
                for (int len : rightLen) {
                    string numStr = rightStr.substr(pos, len);
                    if (!isValidNumber(numStr)) {
                        valid = false;
                        break;
                    }
                    rightNums.push_back(stoi(numStr));
                    pos += len;
                }
                if (!valid) continue;
                
                // 生成运算符的所有排列
                string sortedOps = ops;
                sort(sortedOps.begin(), sortedOps.end());
                do {
                    // 分配运算符到左右两边
                    vector<char> leftOpsVec, rightOpsVec;
                    for (int i = 0; i < leftOps; ++i) leftOpsVec.push_back(sortedOps[i]);
                    for (int i = leftOps; i < totalOps; ++i) rightOpsVec.push_back(sortedOps[i]);
                    
                    // 计算左右两边的值
                    int leftVal = evaluate(leftNums, leftOpsVec);
                    int rightVal = evaluate(rightNums, rightOpsVec);
                    
                    // 检查等式是否成立
                    if (leftVal == rightVal && leftVal != INT_MAX) {
                        // 输出结果
                        cout << "Case " << caseNum++ << ": ";
                        for (size_t i = 0; i < leftNums.size(); ++i) {
                            cout << leftNums[i];
                            if (i < leftOpsVec.size()) cout << leftOpsVec[i];
                        }
                        cout << '=';
                        for (size_t i = 0; i < rightNums.size(); ++i) {
                            cout << rightNums[i];
                            if (i < rightOpsVec.size()) cout << rightOpsVec[i];
                        }
                        cout << '\n';
                        return true;
                    }
                } while (next_permutation(sortedOps.begin(), sortedOps.end()));
            }
        }
    }
    return false;
}

int main() {
    string equation;
    while (cin >> equation) {
        if (equation == "$") break;
        string ops;
        cin >> ops;
        if (!solve(equation, ops))
            cout << "Case " << caseNum++ << ": NO SOLUTION\n";
    }
    return 0;
}
