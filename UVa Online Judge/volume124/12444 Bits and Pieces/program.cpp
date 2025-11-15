// Bits and Pieces
// UVa ID: 12444
// Verdict: Accepted
// Submission Date: 2025-11-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
using namespace std;

int main() {
    int testCaseCount;
    cin >> testCaseCount;
    while (testCaseCount--) {
        unsigned int cValue, dValue;
        cin >> cValue >> dValue;
        
        // 检查可行性条件：C 的 1 位必须是 D 的 1 位的子集
        if ((cValue & (~dValue)) != 0) {
            cout << -1 << endl;
            continue;
        }
        
        // 计算自由位集合
        unsigned int freeBits = dValue & (~cValue);
        
        // 如果没有自由位，则 A = B = C = D
        if (freeBits == 0) {
            cout << cValue << " " << cValue << endl;
            continue;
        }
        
        // 找到自由位中的最高位
        unsigned int highBit = 1;
        while (highBit <= freeBits / 2) {
            highBit <<= 1;
        }
        
        // 分配自由位：最高位给 B，其余给 A
        unsigned int lowBits = freeBits & (~highBit);
        unsigned int aResult = cValue | lowBits;
        unsigned int bResult = cValue | highBit;
        
        cout << aResult << " " << bResult << endl;
    }
    return 0;
}
