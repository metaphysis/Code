// Gerg's Cake
// UVa ID: 10831
// Verdict: Accepted
// Submission Date: 2025-11-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
using namespace std;

long long modPow(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

bool canShareCake(long long a, long long p) {
    if (p == 1) return true;
    a %= p;
    if (a == 0) return true;
    if (p == 2) return true;
    return modPow(a, (p - 1) / 2, p) == 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long a, p;
    while (cin >> a >> p) {
        if (a == -1 && p == -1) break;
        if (canShareCake(a, p)) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    return 0;
}

