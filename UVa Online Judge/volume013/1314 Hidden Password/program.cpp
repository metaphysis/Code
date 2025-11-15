// Hidden Password
// UVa ID: 1314
// Verdict: Accepted
// Submission Date: 2025-11-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int findMinRotation(const string& s) {
    int n = s.length();
    int i = 0, j = 1, k = 0;
    
    while (i < n && j < n && k < n) {
        char a = s[(i + k) % n];
        char b = s[(j + k) % n];
        
        if (a == b) {
            k++;
        } else {
            if (a > b) {
                i = i + k + 1;
            } else {
                j = j + k + 1;
            }
            if (i == j) {
                j++;
            }
            k = 0;
        }
    }
    return min(i, j);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        int l;
        string s;
        cin >> l >> s;
        cout << findMinRotation(s) << "\n";
    }
    
    return 0;
}
