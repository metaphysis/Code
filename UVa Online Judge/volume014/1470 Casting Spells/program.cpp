// Casting Spells
// UVa ID: 1470
// Verdict: Accepted
// Submission Date: 2025-11-22
// UVa Run Time: 0.030s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

vector<int> manacher(const string &s) {
    int n = s.length();
    vector<int> d2(n, 0);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) k++;
        d2[i] = k--;
        if (i + k > r) {
            l = i - k - 1;
            r = i + k;
        }
    }
    return d2;
}

int solve(const string &s) {
    int n = s.length();
    if (n < 4) return 0;
    vector<int> d2 = manacher(s);
    int maxPower = 0;
    for (int i = 0; i < n; i++) {
        d2[i] *= 2;
        if (d2[i] >= maxPower + 4) {
            int current = maxPower + 4;
            while (current <= d2[i]) {
                int secondCenter = i - current / 4;
                if (secondCenter >= 0 && d2[secondCenter] >= current / 2) maxPower = current;
                current += 4;
            }
        }
    }
    return maxPower;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int z;
    cin >> z;
    while (z--) {
        string word;
        cin >> word;
        cout << solve(word) << "\n";
    }
    return 0;
}
