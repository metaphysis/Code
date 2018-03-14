// Knuth's Permutation
// UVa ID: 10063
// Verdict: Accepted
// Submission Date: 2017-11-12
// UVa Run Time: 0.020s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

string line;

void dfs(int depth, string s)
{
    if (depth == line.length()) cout << s << '\n';
    else
    {
        for (int i = 0; i < s.length(); i++)
        {
            string t(s);
            dfs(depth + 1, t.insert(i, line.substr(depth, 1)));
        }
        dfs(depth + 1, s + line[depth]);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> line)
    {
        if (cases++ > 0) cout << '\n';
        dfs(1, line.substr(0, 1));
    }
    
    return 0;
}
