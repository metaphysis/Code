// Special Number
// UVa ID: 11533
// Verdict: Accepted
// Submission Date: 2026-06-05
// UVa Run Time: 0.150s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

long long exgcd(long long a, long long b, long long& x, long long& y) {
    if (b == 0) { x = 1; y = 0; return a; }
    long long g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

long long invMod(long long a, long long mod) {
    long long x, y;
    exgcd(a, mod, x, y);
    return (x % mod + mod) % mod;
}

long long mulMod(long long a, long long b, long long mod) {
    if (mod <= 1000000000) return a * b % mod;
    long long res = 0;
    a %= mod;
    while (b) {
        if (b & 1) res = (res + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return res;
}

long long powMod(long long a, long long b, long long mod) {
    long long res = 1 % mod;
    a %= mod;
    while (b) {
        if (b & 1) res = mulMod(res, a, mod);
        a = mulMod(a, a, mod);
        b >>= 1;
    }
    return res;
}

long long bsgs(long long a, long long b, long long p) {
    a %= p; b %= p;
    if (p == 1) return (b == 0) ? 0 : -1;
    if (b == 1) return 0;
    
    long long m = (long long)ceil(sqrt(p));
    unordered_map<long long, long long> baby;
    baby.reserve(m + 5);
    
    long long e = 1;
    for (long long i = 0; i < m; ++i) {
        if (baby.find(e) == baby.end()) baby[e] = i;
        e = mulMod(e, a, p);
    }
    
    long long am = powMod(a, m, p);
    long long inv_am = invMod(am, p);
    long long gamma = b;
    for (long long i = 0; i <= m; ++i) {
        auto it = baby.find(gamma);
        if (it != baby.end()) return i * m + it->second;
        gamma = mulMod(gamma, inv_am, p);
    }
    return -1;
}

long long exBSGS(long long a, long long b, long long p) {
    a %= p; b %= p;
    if (p == 1) return (b == 0) ? 0 : -1;
    if (b == 1) return 0;
    
    long long g = __gcd(a, p);
    if (g == 1) return bsgs(a, b, p);
    
    if (b % g != 0) return -1;
    
    long long na = a / g;
    long long nb = b / g;
    long long np = p / g;
    
    long long inv_na = invMod(na, np);
    long long new_b = mulMod(nb, inv_na, np);
    
    long long res = exBSGS(a, new_b, np);
    if (res == -1) return -1;
    return res + 1;
}

// 构造原数字：通过模拟竖式乘法从低位向高位递推
// 返回原数字的各位（从最高位到最低位），包含前导零
vector<int> constructNumber(int N, int X, int Y, long long k) {
    vector<int> digits(k);
    digits[k - 1] = X;  // 个位
    
    long long carry = 0;
    for (int i = k - 1; i >= 1; --i) {
        long long val = carry + (long long)digits[i] * Y;
        digits[i - 1] = val % N;
        carry = val / N;
    }
    
    // 验证：最终进位应该等于 X
    // 如果 carry != X，说明无解（但理论上不会发生）
    return digits;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int N, X, Y, caseNum = 1;
    while (cin >> N >> X >> Y) {
        cout << "Case " << caseNum++ << ":";
        
        if (X == 0) {
            cout << " 0\n";
            continue;
        }
        if (Y == 0) {
            cout << " No solution\n";
            continue;
        }
        
        long long D = (long long)Y * N - 1;
        if (D <= 0) {
            cout << " No solution\n";
            continue;
        }
        
        long long g = __gcd((long long)X, D);
        long long Dprime = D / g;
        
        if (Dprime == 1) {
            cout << " " << X << "\n";
            continue;
        }
        
        long long e = exBSGS(N, Y % Dprime, Dprime);
        if (e == -1) {
            cout << " No solution\n";
            continue;
        }
        
        long long k = e + 1;
        vector<int> digits = constructNumber(N, X, Y, k);
        
        for (int d : digits) cout << " " << d;
        cout << "\n";
    }
    return 0;
}
