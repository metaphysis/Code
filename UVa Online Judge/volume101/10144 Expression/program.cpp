// Expression
// UVa ID: 10144
// Verdict: Accepted
// Submission Date: 2025-11-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <string>
using namespace std;

// 生成变量名，如 'A0', 'B1'
string shefVar(char type, int idx) {
    return string(1, type) + to_string(idx);
}

// 构造 p_i = A_i ∨ B_i 的 Sheffer 形式
string shefP(int i) {
    string Ai = shefVar('A', i);
    string Bi = shefVar('B', i);
    return "((" + Ai + "|" + Ai + ")|(" + Bi + "|" + Bi + "))";
}

// 递归构造 N 位加法的溢出位表达式
string buildOverflow(int N) {
    // 基本情况：1位加法，溢出位 = A0 ∧ B0
    if (N == 1) {
        string A0 = shefVar('A', 0);
        string B0 = shefVar('B', 0);
        return "((" + A0 + "|" + B0 + ")|(" + A0 + "|" + B0 + "))";
    }
    
    // 递归情况：C_N = (NOT g_{N-1}) | (C_{N-1} | p_{N-1})
    string ALast = shefVar('A', N - 1);      // A_{N-1}
    string BLast = shefVar('B', N - 1);      // B_{N-1}
    string notG = "(" + ALast + "|" + BLast + ")";  // NOT g_{N-1} = (A_{N-1}|B_{N-1})
    
    string prevOverflow = buildOverflow(N - 1);  // C_{N-1}
    string pLast = shefP(N - 1);                 // p_{N-1}
    
    // 返回 C_N = (NOT g_{N-1}) | (C_{N-1} | p_{N-1})
    return "(" + notG + "|(" + prevOverflow + "|" + pLast + "))";
}

int main() {
    int testCases;
    cin >> testCases;
    bool isFirst = true;
    
    while (testCases--) {
        if (!isFirst) {
            cout << "\n";  // 测试用例之间输出空行
        }
        isFirst = false;
        
        int bitLength;
        cin >> bitLength;
        cout << buildOverflow(bitLength) << "\n";
    }
    
    return 0;
}
