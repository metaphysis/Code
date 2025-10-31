// Encoding
// UVa ID: 11058
// Verdict: Accepted
// Submission Date: 2025-10-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net
//
// https://blog.csdn.net/metaphysis/article/details/154122230

#include <bits/stdc++.h>
using namespace std;

struct rule {
    int p;
    char x, y;
};

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    string s;
    int T = 0;
    while (cin >> s) {
        T++;
        char table[128];
        for (int i = 0; i < 26; i++) cin >> table['a' + i];
        int R;
        cin >> R;
        vector<rule> rules(R);
        for (int i = 0; i < R; i++) cin >> rules[i].p >> rules[i].x >> rules[i].y;
        string encoding;
        for (int i = 0, j = 0; i < (int)s.length(); i++) {
            while (j < R && rules[j].p <= i) {
                table[rules[j].x] = rules[j].y;
                j++;
            }
            encoding += table[s[i]];
        }
        cout << "Case #" << T << ": The encoding string is " << encoding << "." << "\n\n";
    }
    return 0;
}

