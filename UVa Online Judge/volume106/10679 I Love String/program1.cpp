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

int pi[MAXN] = {};

void getNext(string &p)
{
    int n = p.length();
    pi[0] = pi[1] = 0;
    for (int i = 1, j = 0; i < n; i++) {
        while (j && p[j] != p[i]) j = pi[j];
        if (p[j] == p[i]) j++;
        pi[i + 1] = j;
    }
    //int i = 1, j = 0, n = p.length();
    //while (i < n) {
    //    if (j == 0 || p[i] == p[j]) {
    //        i++, j++;
    //        if (p[i] != p[j]) pi[i] = j;
    //        else pi[i] = pi[j];
    //   }
    //    else j = pi[j];
    //}
}

bool kmp(string &s, string &p)
{
    int m = s.length(), n = p.length();
    getNext(p);
    for (int i = 0, j = 0; i < m; i++) {
        while (j && p[j] != s[i]) j = pi[j];
        if (p[j] == s[i]) j++;
        if (j == n) return true;
    }
    return false;
    //int i = 0, j = 1;
    //while (i < m && j < n) {
    //    if (j == 0 || s[i] == p[j]) i++, j++;
    //    else j = pi[j];
    //}
    //return j >= n;
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
            if (S.length() >= T.length()) cout << (kmp(S, T) ? 'y' : 'n');
            cout << '\n';
        }
    }

    return 0;
}
