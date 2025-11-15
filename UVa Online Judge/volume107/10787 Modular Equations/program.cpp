// Modular Equations
// UVa ID: 10787
// Verdict: Accepted
// Submission Date: 2025-11-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;

vector<int> getDivisors(int n) {
    vector<int> divisors;
    int absN = abs(n);
    for (int i = 1; i * i <= absN; ++i) {
        if (absN % i == 0) {
            divisors.push_back(i);
            if (i != absN / i) {
                divisors.push_back(absN / i);
            }
        }
    }
    return divisors;
}

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        int amin, amax, bmin, bmax, mmin, mmax;
        cin >> amin >> amax >> bmin >> bmax >> mmin >> mmax;
        
        long long aCount = amax - amin + 1;
        long long validPairs = 0;
        
        for (int b = bmin; b <= bmax; ++b) {
            int x = 2 * b;
            if (x == 0) {
                validPairs += (mmax - mmin + 1);
            } else {
                vector<int> divisors = getDivisors(x);
                for (int d : divisors) {
                    if (d >= mmin && d <= mmax && (abs(x) % d == 0)) {
                        validPairs++;
                    }
                }
            }
        }
        
        long long result = validPairs * aCount;
        cout << "Case " << t << ": " << result << endl;
    }
    return 0;
}
