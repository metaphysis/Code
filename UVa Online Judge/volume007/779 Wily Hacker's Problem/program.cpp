/*
本题在 UVa OnlineJudge 上的题目描述中的样例输入与样例输出并不一致，原始题目，样例输入为：

6742a447d483868e 1111222233334444
4ced98bf8eb91895 feedf1d0facef00d

样例输出为：

STUDENTS
TEACHERS

符合图中所示的加密逻辑关系：
A1 = M1 < K1
A2 = M2 + K2
A3 = M3 ^ K3
A4 = M4 < K4
A5 = A1 ^ A3
A6 = A2 ^ A4
A7 = A5 < (K1 + K2)
A8 = A7 + A6
A9 = A8 < (K3 + K4)
A10 = A1 ^ A9
A11 = A3 ^ A9
A12 = A7 ^ A9
A13 = A2 ^ A12
A14 = A4 ^ A12
C1 = A10 < K4
C2 = A13 + K3
C3 = A11 ^ K2
C4 = A14 < K1

而 UVa OnlineJudge 上的题目描述中的样例测试数据和样例输出并不符合题目中的加密逻辑关系
另外，此题的在线测试数据大概率存在问题，因为 uDebug 上的参考通过代码有奇怪的行为：
加密数据的前 48 位和秘钥的前 48 位对输出没有任何影响，也就是说，
只要密文的后 16 位和秘钥的后 16 位保持不变，前面的 48 位修改成任何合法内容，输出均不变。

以下代码是按照原题目中的样例输入和样例输出实现，可以得到一致的结果，但无法通过在线测试。
*/
#include <bits/stdc++.h>
using namespace std;

uint32_t rotateLeft(uint32_t value, uint32_t shift) {
    shift %= 16;
    value &= 65535;
    if (shift == 0) return value;
    return ((value << shift) | (value >> (16 - shift))) & 65535;
}

uint32_t rotateRight(uint32_t value, uint32_t shift) {
    shift %= 16;
    value &= 65535;
    if (shift == 0) return value;
    return ((value >> shift) | (value << (16 - shift))) & 65535;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string cryptogram, key;
    while (cin >> cryptogram >> key) {
        uint64_t cValue = stoull(cryptogram, nullptr, 16), kValue = stoull(key, nullptr, 16);
        uint32_t c1 = (cValue >> 48) & 65535, c2 = (cValue >> 32) & 65535, c3 = (cValue >> 16) & 65535, c4 = cValue & 65535;
        uint32_t k1 = (kValue >> 48) & 65535, k2 = (kValue >> 32) & 65535, k3 = (kValue >> 16) & 65535, k4 = kValue & 65535;
        uint32_t a10 = rotateRight(c1, k4), a11 = c3 ^ k2, a13 = (c2 - k3) & 65535, a14 = rotateRight(c4, k1);
        uint32_t a7 = rotateLeft(a10 ^ a11, k1 + k2);
        uint32_t a6 = a13 ^ a14;
        uint32_t a8 = (a7 + a6) & 65535;
        uint32_t a9 = rotateLeft(a8, k3 + k4);
        uint32_t a12 = a7 ^ a9;
        uint32_t a1 = a10 ^ a9, a2 = a13 ^ a12, a3 = a11 ^ a9, a4 = a14 ^ a12;
        uint32_t m1 = rotateRight(a1, k1), m2 = (a2 - k2) & 65535, m3 = a3 ^ k3, m4 = rotateRight(a4, k4);
        cout << char(m1 >> 8) << char(m1 & 255);
        cout << char(m2 >> 8) << char(m2 & 255);
        cout << char(m3 >> 8) << char(m3 & 255);
        cout << char(m4 >> 8) << char(m4 & 255) << '\n';
    }
    return 0;
}
