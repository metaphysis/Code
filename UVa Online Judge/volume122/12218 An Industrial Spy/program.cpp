// An Industrial Spy
// UVa ID: 12218
// Verdict: Accepted
// Submission Date: 2023-04-21
// UVa Run Time: 0.720s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
const int MAXN = 10000010;
int p[MAXN], pc = 0;
int f[1000010], fc = 0;
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    for (int i = 2; i < MAXN; i++) {
        if (!p[i]) p[pc++] = i;
        for (int j = 0; j < pc && i * p[j] < MAXN; j++) {
            p[i * p[j]] = 1;
            if (i % p[j] == 0) break;
        }
    }
    int T;
    string s;
    cin >> T;
    while (T--) {
        cin >> s;
        sort(s.begin(), s.end());
        fc = 0;
        do {
            for (int i = 1; i <= s.length(); i++)
                for (int j = 0; j < s.length(); j++) {
                    if (j + i > s.length()) break;
                    int k = stoi(s.substr(j, i));
                    if (binary_search(p, p + pc, k))
                        f[fc++] = k;
                }

        } while (next_permutation(s.begin(), s.end()));
        sort(f, f + fc);
        fc = unique(f, f + fc) - f;
        cout << fc << '\n';
    }
    return 0;
}
