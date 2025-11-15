// Digits Count
// UVa ID: 12241
// Verdict: Accepted
// Submission Date: 2025-11-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>

using namespace std;

vector<long long> countFrom1ToN(long long n) {
    vector<long long> cnt(10, 0);
    if (n <= 0) return cnt;
    
    long long base = 1;
    while (base <= n) {
        long long high = n / (base * 10);
        long long low = n % base;
        int cur = (n / base) % 10;
        
        // 对于非零数字
        for (int d = 1; d <= 9; d++) {
            if (d < cur) {
                cnt[d] += (high + 1) * base;
            } else if (d == cur) {
                cnt[d] += high * base + low + 1;
            } else {
                cnt[d] += high * base;
            }
        }
        
        // 对于数字0，需要特殊处理前导零
        if (high > 0) {
            if (cur == 0) {
                cnt[0] += (high - 1) * base + low + 1;
            } else {
                cnt[0] += high * base;
            }
        }
        
        base *= 10;
    }
    
    return cnt;
}

int main() {
    long long A, B;
    while (cin >> A >> B) {
        if (A == 0 && B == 0) break;
        
        vector<long long> cntB = countFrom1ToN(B);
        vector<long long> cntA = countFrom1ToN(A - 1);
        
        for (int i = 0; i <= 9; i++) {
            if (i > 0) cout << " ";
            cout << cntB[i] - cntA[i];
        }
        cout << endl;
    }
    
    return 0;
}
