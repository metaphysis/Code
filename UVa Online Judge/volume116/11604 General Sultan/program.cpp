// General Sultan
// UVa ID: 11604
// Verdict: Accepted
// Submission Date: 2026-01-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int caseNum = 1;
    int n;
    while (cin >> n && n) {
        cout << "Case #" << caseNum++ << ": ";
        string name, code;
        set<string> codes[3];  // codes[0]: 原始编码, codes[1]: 当前Si, codes[2]: 新的Si+1
        bool ambiguous = false;
        
        // 读入所有编码
        for (int i = 0; i < n; ++i) {
            cin >> name >> code;
            if (codes[0].count(code)) ambiguous = true;  // 检查是否有重复编码
            codes[0].insert(code);
            codes[1].insert(code);  // S0也作为初始S1
        }
        
        if (ambiguous) {
            cout << "Ambiguous.\n";
            continue;
        }
        
        // Sardinas-Patterson算法
        while (true) {
            codes[2].clear();  // 清空用于存储新生成的剩余部分
            
            // 生成新的剩余字符串集合
            for (auto c0 : codes[0])  // 原始编码集合
                for (auto c1 : codes[1]) {  // 当前Si集合
                    if (c0 == c1) continue;
                    if (c0.length() > c1.length()) swap(c0, c1);
                    // 检查是否是前缀关系
                    if (c0 == c1.substr(0, c0.length()))
                        codes[2].insert(c1.substr(c0.length()));  // 添加剩余部分
                }
            
            if (codes[2].empty()) break;  // 没有新的剩余部分，无歧义
            
            // 检查新生成的剩余部分是否包含原始编码
            for (auto c2 : codes[2]) {
                if (codes[0].count(c2)) {
                    ambiguous = true;
                    break;
                }
            }
            if (ambiguous) break;
            
            // 检查是否出现循环
            if (codes[2] == codes[1]) break;
            
            codes[1].swap(codes[2]);  // 继续下一轮迭代
        }
        
        cout << (ambiguous ? "Ambiguous." : "Not ambiguous.") << '\n';
    }
    return 0;
}
