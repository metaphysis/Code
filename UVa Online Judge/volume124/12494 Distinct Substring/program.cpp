// Distinct Substring
// UVa ID: 12494
// Verdict: Accepted
// Submission Date: 2025-10-15
// UVa Run Time: 0.130s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

string minCyclicShift(const string& s) {
    int n = s.length();
    string t = s + s;
    int i = 0, j = 1;
    while (i < n && j < n) {
        int k = 0;
        while (k < n && t[i + k] == t[j + k]) {
            k++;
        }
        if (k == n) {
            break;
        }
        if (t[i + k] > t[j + k]) {
            i += k + 1;
        } else {
            j += k + 1;
        }
        if (i == j) {
            j++;
        }
    }
    int pos = min(i, j);
    return t.substr(pos, n);
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        string s;
        cin >> s;
        int n = s.length();
        unordered_set<string> seen;
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j <= n; j++) {
                string substr = s.substr(i, j - i);
                string canonical = minCyclicShift(substr);
                seen.insert(canonical);
            }
        }
        
        cout << seen.size() << endl;
    }
    return 0;
}
