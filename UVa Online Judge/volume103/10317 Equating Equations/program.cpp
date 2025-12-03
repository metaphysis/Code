// Equating Equations
// UVa ID: 10317
// Verdict: Accepted
// Submission Date: 2025-12-01
// UVa Run Time: 0.070s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

vector<int> nums;          // 存储所有数字
vector<char> ops;          // 存储所有运算符（包括=）
vector<int> signs;         // 每个数字前的符号（+1或-1）
vector<int> solution;      // 存储最终的数字排列
bool found = false;        // 是否找到解

// 解析输入的等式
void parseEquation(const string& line) {
    nums.clear();
    ops.clear();
    signs.clear();
    solution.clear();
    found = false;
    
    stringstream ss(line);
    string token;
    vector<string> tokens;
    
    // 分割 tokens
    while (ss >> token) tokens.push_back(token);
    
    // 第一个数字
    nums.push_back(stoi(tokens[0]));
    signs.push_back(1);  // 第一个数字符号为正
    
    bool onLeft = true;
    int i = 1;
    
    while (i < tokens.size()) {
        string op = tokens[i++];
        
        if (op == "=") {
            ops.push_back('=');
            onLeft = false;
            // 等号后的第一个数字
            if (i < tokens.size()) {
                nums.push_back(stoi(tokens[i++]));
                signs.push_back(-1);  // 移到左边后符号为负
            }
            continue;
        }
        
        // 读取数字
        if (i < tokens.size()) {
            int num = stoi(tokens[i++]);
            nums.push_back(num);
            
            if (onLeft) {
                // 左边：+ 为正，- 为负
                signs.push_back(op == "+" ? 1 : -1);
            } else {
                // 右边：移到左边后符号取反
                signs.push_back(op == "+" ? -1 : 1);
            }
            ops.push_back(op[0]);
        }
    }
}

// 回溯查找 count 个数字和为 target
bool findSubset(int start, int count, int sum, int target, vector<bool>& selected) {
    if (count == 0) return sum == target;
    if (start >= (int)nums.size()) return false;
    
    // 剪枝：如果当前数字太大
    if (nums[start] > target - sum) {
        return findSubset(start + 1, count, sum, target, selected);
    }
    
    // 尝试选择当前数字
    selected[start] = true;
    if (findSubset(start + 1, count - 1, sum + nums[start], target, selected)) {
        return true;
    }
    selected[start] = false;
    
    // 不选当前数字
    return findSubset(start + 1, count, sum, target, selected);
}

void solve() {
    int n = nums.size();
    if (n == 0) return;
    
    // 统计正负号数量
    int posCount = 0, negCount = 0;
    for (int sign : signs) {
        if (sign == 1) posCount++;
        else negCount++;
    }
    
    // 计算总和
    int total = 0;
    for (int num : nums) total += num;
    
    // 总和必须是偶数
    if (total % 2 != 0) return;
    
    int target = total / 2;
    int m = min(posCount, negCount);
    
    // 对数字排序便于回溯剪枝
    sort(nums.begin(), nums.end());
    
    // 回溯查找 m 个数字和为 target
    vector<bool> selected(n, false);
    if (!findSubset(0, m, 0, target, selected)) return;
    
    // 分配数字到符号位置
    vector<int> posGroup, negGroup;
    for (int i = 0; i < n; i++) {
        if (selected[i]) {
            // 这些数字将分配给较少的符号位置
            if (posCount <= negCount) {
                posGroup.push_back(nums[i]);  // 放正号位置
            } else {
                negGroup.push_back(nums[i]);  // 放负号位置
            }
        } else {
            // 剩余数字分配给另一种符号位置
            if (posCount <= negCount) {
                negGroup.push_back(nums[i]);  // 放负号位置
            } else {
                posGroup.push_back(nums[i]);  // 放正号位置
            }
        }
    }
    
    // 直接分配
    solution.resize(n);
    int posIdx = 0, negIdx = 0;
    
    for (int i = 0; i < n; i++) {
        if (signs[i] == 1) {
            solution[i] = posGroup[posIdx++];
        } else {
            solution[i] = negGroup[negIdx++];
        }
    }
    
    found = true;
}

void printSolution() {
    if (!found) {
        cout << "no solution" << endl;
        return;
    }
    
    // 按照原始格式输出
    cout << solution[0];
    int idx = 1;
    for (char op : ops) {
        cout << " " << op << " " << solution[idx++];
    }
    cout << endl;
}

int main() {
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        parseEquation(line);
        solve();
        printSolution();
    }
    return 0;
}
