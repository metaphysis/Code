// I Love String
// UVa ID: 10679
// Verdict: Accepted
// Submission Date: 2018-03-27
// UVa Run Time: 1.410s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1024;

bool kmp1(string &s, string &p)
{
    static int fail[MAXN] = {};

    fail[0] = fail[1] = 0;
    int i = 1, j = 0;
    while (i < p.length()) {
        if (j == 0 || p[i] == p[j]) {
            i++, j++;
            if (p[i] != p[j]) fail[i] = j;
            else fail[i] = fail[j];
        } else j = fail[j];
    }

    i = 0, j = 1;
    while (i < s.length() && j < p.length()) {
        if (j == 0 || s[i] == p[j - 1]) i++, j++;
        else j = fail[j];
    }
    return j >= p.length();
}

bool kmp2(string &s, string &p)
{
    static int fail[MAXN] = {};

    fail[0] = fail[1] = 0;
    for (int i = 1, j = 0; i < p.length(); i++) {
        while (j && p[j] != p[i]) j = fail[j];
        if (p[j] == p[i]) j++;
        fail[i + 1] = j;
    }

    for (int i = 0, j = 0; i < s.length(); i++) {
        while (j && p[j] != s[i]) j = fail[j];
        if (p[j] == s[i]) j++;
        if (j == p.length()) return true;
    }
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, q;
    string S, T;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> S >> q;
        for (int i = 0; i < q; i++)
        {
            cin >> T;
            if (S.length() >= T.length()) cout << (kmp1(S, T) ? 'y' : 'n');
            cout << '\n';
        }
    }

    return 0;
}
