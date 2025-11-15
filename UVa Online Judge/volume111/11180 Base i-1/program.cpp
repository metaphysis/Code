// Base i-1
// UVa ID: 11180
// Verdict: Accepted
// Submission Date: 2025-11-12
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string toBaseMinusI(int a, int b) {
    if (a == 0 && b == 0) {
        return "0";
    }
    
    vector<int> digits;
    while (a != 0 || b != 0) {
        int remainder = (a - b) % 2;
        if (remainder < 0) remainder += 2; // 保证余数为 0 或 1
        
        digits.push_back(remainder);
        
        // 更新 a 和 b
        int newA = (b - a + remainder) / 2;
        int newB = (-a - b + remainder) / 2;
        a = newA;
        b = newB;
    }
    
    // 反转 digits 得到正确顺序
    string result;
    for (int i = digits.size() - 1; i >= 0; --i) {
        result += to_string(digits[i]);
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int numCases;
    cin >> numCases;
    
    for (int caseNum = 1; caseNum <= numCases; ++caseNum) {
        int a, b;
        cin >> a >> b;
        
        string representation = toBaseMinusI(a, b);
        cout << "Case #" << caseNum << ": " << representation << "\n";
    }
    
    return 0;
}
