// And Or
// UVa ID: 12898
// Verdict: Accepted
// Submission Date: 2025-11-04
// UVa Run Time: 0.030s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
using namespace std;

typedef unsigned long long ull;

// 计算区间按位与
ull rangeAnd(ull a, ull b) {
    int shiftCount = 0;
    // 找到 a 和 b 的公共前缀
    while (a != b) {
        a >>= 1;
        b >>= 1;
        shiftCount++;
    }
    // 将公共前缀左移回原位
    return a << shiftCount;
}

// 计算区间按位或
ull rangeOr(ull a, ull b) {
    if (a == b) return a;
    // 找到第一个不同的位
    int firstDiffBit = 63 - __builtin_clzll(a ^ b);
    // 构造掩码：从第一个不同位往右全部置 1
    ull mask = (1ULL << (firstDiffBit + 1)) - 1;
    // 保留高位，低位全置 1
    ull highBits = (a >> (firstDiffBit + 1)) << (firstDiffBit + 1);
    return highBits | mask;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int testCases;
    cin >> testCases;
    for (int caseNum = 1; caseNum <= testCases; caseNum++) {
        ull start, end;
        cin >> start >> end;
        ull orResult = rangeOr(start, end);
        ull andResult = rangeAnd(start, end);
        cout << "Case " << caseNum << ": " << orResult << " " << andResult << "\n";
    }
    return 0;
}
