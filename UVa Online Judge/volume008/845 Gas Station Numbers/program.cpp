// Gas Station Numbers
// UVa ID: 845
// Verdict: Accepted
// Submission Date: 2025-11-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 数字翻转映射表
map<char, char> fliped = {
    {'0', '0'}, {'1', '1'}, {'2', '5'}, {'3', '3'}, {'4', '4'},
    {'5', '2'}, {'6', '9'}, {'7', '7'}, {'8', '8'}, {'9', '6'}
};

/**
 * 标准化字符串：将指定位置之后的部分转换为最小字典序
 * @param s 要标准化的字符串
 * @param k 起始位置
 */
void normalize(string& s, int k) {
    // 将5转为2，9转为6，统一使用较小的表示
    for (size_t i = k; i < s.size(); i++) {
        if (s[i] == '5') s[i] = '2';
        if (s[i] == '9') s[i] = '6';
    }
    // 对剩余部分排序，得到最小排列
    sort(s.begin() + k, s.end());
}

int main() {
    string line;
    while (getline(cin, line)) {
        if (line == ".") break;  // 输入结束
        
        string price = line;
        // 移除小数点，便于处理
        price.erase(price.find('.'), 1);
        
        vector<string> answer;  // 存储所有候选解
        int n = price.length();
        int changed = 0;  // 标记是否找到可行解
        
        // 从右向左扫描每个位置
        for (int i = n - 1; i >= 0; i--) {
            // 情况1：当前数字可以直接翻转增大（2->5 或 6->9）
            if (price[i] == '2' || price[i] == '6') {
                string s = price;
                s[i] = fliped[s[i]];  // 执行翻转
                normalize(s, i + 1);   // 标准化剩余部分
                answer.push_back(s);   // 加入候选
                changed = 1;
            }
            
            // 情况2：与后面的数字交换
            int bestJ = -1;    // 最佳交换位置
            char bestC = -1;   // 最佳交换字符
            
            // 在当前位置之后寻找可交换的数字
            for (int j = i + 1; j < n; j++) {
                // 检查原始数字是否大于当前位置数字
                if (price[j] > price[i]) {
                    if (bestJ == -1 || price[j] < bestC) {
                        bestJ = j;
                        bestC = price[j];
                    }
                }
                // 检查翻转后的数字是否大于当前位置数字
                if (fliped[price[j]] > price[i]) {
                    if (bestJ == -1 || fliped[price[j]] < bestC) {
                        bestJ = j;
                        bestC = fliped[price[j]];
                    }
                }
            }
            
            // 如果找到可交换的数字
            if (bestJ != -1) {
                string s = price;
                // 执行交换
                s[bestJ] = s[i];  // 当前位置数字移到后面
                s[i] = bestC;     // 更大的数字移到当前位置
                normalize(s, i + 1);  // 标准化剩余部分
                answer.push_back(s);  // 加入候选
                changed = 1;
            }
            
            // 如果找到解，立即停止（贪心：第一个能增大的位置就是关键位置）
            if (changed) break;
        }
        
        // 选择最小的候选解
        sort(answer.begin(), answer.end());
        string r;
        if (answer.size()) r = answer.front();
        
        // 输出结果
        if (r.empty()) {
            cout << "The price cannot be raised.\n";
        } else {
            // 重新插入小数点（在倒数第二位之前）
            cout << r.substr(0, r.length() - 1) << '.' << r.back() << '\n';
        }
    }
    return 0;
}
