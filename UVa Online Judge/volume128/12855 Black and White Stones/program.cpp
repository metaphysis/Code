// Black and White Stones
// UVa ID: 12855
// Verdict: Accepted
// Submission Date: 2024-11-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2024，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int A, B;
    string s;
    while (cin >> A >> B) {
        cin >> s;
        int bidx = 0;
        for (int i = 0; i < s.length(); i++)
            if (s[i] == 'B') bidx++;
        if (!bidx) { cout << 0 << '\n'; continue; }
        long long r = 0;
        for (int i = bidx - 1, j = bidx; i >= 0; i--)
            if (s[i] == 'W') {
                while (s[j] == 'W') j++;
                r += min((long long)A, (long long)(A - B) * (j - i));
                s[i] = 'B', s[j] = 'W';
            }
        cout << r << '\n';
    }
    return 0;
}
