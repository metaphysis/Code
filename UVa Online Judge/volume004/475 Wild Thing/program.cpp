// Wild Thing
// UVa ID: 475
// Verdict: Accepted
// Submission Date: 2019-01-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

bool done;
string pattern, filename;

void dfs(int pl, int pr, int fl, int fr)
{
    if (pl == pr && fl == fr)
    {
        done = true;
        return;
    }
    if (pl < pr && pattern[pl] == '*')
    {
        int x = 0;
        for (x = pl + 1; x < pr && pattern[x] != '*'; x++);
        int L = x - pl - 1;
        for (int i = fl; i + L <= fr; i++)
        {
            if (pattern[pl + 1] != filename[i]) continue;
            if (pattern.substr(pl + 1, L) == filename.substr(i, L))
                dfs(pl + L + 1, pr, i + L, fr);
            if (done) return;
        }
    }
    else if (pl < pr && pattern[pl] != '*')
    {
        int x = 0;
        for (x = pl + 1; x < pr && pattern[x] != '*'; x++);
        int L = x - pl;
        if (fl + L <= fr && pattern.substr(pl, L) == filename.substr(fl, L))
            dfs(pl + L, pr, fl + L, fr);
        if (done) return;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    while (getline(cin, pattern))
    {
        string backup = pattern;
        for (int i = pattern.size() - 1; i > 0; i--)
            if (pattern[i] == '*' && pattern[i - 1] == '*')
                pattern.erase(pattern.begin() + i);

        vector<string> matched;
        while (getline(cin, filename), filename.length() > 0)
        {
            done = false;
            if (pattern == "*") done = true;
            if (!done) dfs(0, pattern.size(), 0, filename.size());
            if (done) matched.push_back(filename);
        }
        if (matched.size() > 0)
        {
            if (cases++) cout << '\n';
            cout << "MATCHES FOR THE PATTERN: " << backup << '\n';
            for (auto m : matched) cout << m << '\n';
        }
    }

    return 0;
}
