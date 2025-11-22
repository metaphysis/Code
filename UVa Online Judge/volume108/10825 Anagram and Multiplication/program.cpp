// Anagram and Multiplication
// UVa ID: 10825
// Verdict: Accepted
// Submission Date: 2025-11-19
// UVa Run Time: 0.050s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

vector<int> findAmazingNumber(int m, int n) {
    for (int lastDigit = 1; lastDigit < n; lastDigit++) {
        set<int> digitsSet;
        digitsSet.insert(lastDigit);
        for (int k = 2; k <= m; k++) digitsSet.insert((lastDigit * k) % n);
        
        if (digitsSet.size() == m) {
            vector<int> digits(digitsSet.begin(), digitsSet.end());
            do {
                if (digits[0] == 0 || digits[0] * m >= n) continue;
                
                long long num = 0;
                for (int d : digits) num = num * n + d;
                
                vector<int> sortedOrig = digits;
                sort(sortedOrig.begin(), sortedOrig.end());
                bool valid = true;
                
                for (int k = 2; k <= m && valid; k++) {
                    long long product = num * k;
                    if (product >= (long long)pow(n, m)) { valid = false; break; }
                    
                    vector<int> prodDigits(m);
                    long long temp = product;
                    for (int i = m - 1; i >= 0; i--) {
                        prodDigits[i] = temp % n;
                        temp /= n;
                    }
                    
                    sort(prodDigits.begin(), prodDigits.end());
                    if (sortedOrig != prodDigits) valid = false;
                }
                
                if (valid) return digits;
            } while (next_permutation(digits.begin(), digits.end()));
        }
    }
    return vector<int>();
}

int main() {
    int m, n;
    while (cin >> m >> n && (m || n)) {
        vector<int> result = findAmazingNumber(m, n);
        if (result.empty()) cout << "Not found." << endl;
        else {
            for (int i = 0; i < m; i++) cout << (i ? " " : "") << result[i];
            cout << endl;
        }
    }
    return 0;
}
