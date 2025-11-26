// Circular Lock
// UVa ID: 11024
// Verdict: Accepted
// Submission Date: 2025-11-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int main() {
    int n;
    cin >> n;
    
    while (n-- > 0) {
        int s11, s12, p11, p12;
        int s21, s22, p21, p22;
        cin >> s11 >> s12 >> p11 >> p12;
        cin >> s21 >> s22 >> p21 >> p22;
        
        int p = gcd(gcd(p11, p12), gcd(p21, p22));
        
        int a = s11 % p;
        int b = s12 % p;
        int c = s21 % p;
        int d = s22 % p;
        
        if ((a - b - c + d) % p == 0) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    
    return 0;
}
