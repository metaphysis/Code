// Lexicographic Order
// UVa ID: 12335
// Verdict: Accepted
// Submission Date: 2022-10-06
// UVa Run Time: 0.010s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

unsigned long long factorial[21] = {1}, n;
map<char, char> jump;
string s, ss;

void cantorExpansion(string s, string ss)
{
    n %= factorial[s.length()];
    for (int i = s.length() - 1; i >= 0; i--)
    {
        long long idx = n / factorial[i];
        jump[s[idx]] = ss[ss.length() - 1 - i];
        s.erase(s.begin() + idx);
        n %= factorial[i];
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    for (int i = 1; i <= 20; i++) factorial[i] = factorial[i - 1] * i;

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> s >> n;
        n--;
        jump.clear();
        ss = s;
        sort(s.begin(), s.end());
        cantorExpansion(s, ss);
        cout << "Case " << cs << ": ";
        for (auto c : s) cout << jump[c];
        cout << '\n';
    }

    return 0;
}
