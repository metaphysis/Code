// Formatting Text
// UVa ID: 709
// Verdict: Accepted
// Submission Date: 2018-11-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

int n, dp[10010], path[10010][2];
vector<string> words;

int getBadness(int spaces, int gap)
{
    if (gap == 0) return 500;
    int q = spaces / gap, r = spaces % gap;     
    return (gap - r) * (q - 1) * (q - 1) + r * q * q;
}

int dfs(int u)
{
    if (u == words.size()) return 0;
    if (~dp[u]) return dp[u];
    int r = INF, width = 0;
    for (int i = 0; u + i < words.size(); i++)
    {
        width += words[u + i].length();
        if (width + i <= n)
        {
            int next = getBadness(n - width, i) + dfs(u + i + 1);
            if (next <= r)
            {
                r = next;
                path[u][0] = u + i + 1;
                path[u][1] = width;
            }
        }
        else break;
    }
    return dp[u] = r;
}

void format(int u)
{
    if (u == words.size()) return;
    int t = path[u][0] - u, w = n - path[u][1];
    if (t == 1) cout << words[u];
    else
    {
        int q = w / (t - 1), r = w % (t - 1);
        for (int i = 0; i < t; i++)
        {
            if (i)
            {
                cout << string(q, ' ');
                if (i >= t - r) cout << ' ';
            }
            cout << words[u + i];
        }
    }
    cout << '\n';
    format(path[u][0]);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n, n > 0)
    {
        cin.ignore(256, '\n');
        string line, word;
        words.clear();
        while (getline(cin, line), line.length() > 0)
        {
            istringstream iss(line);
            while (iss >> word) words.push_back(word);
        }
        memset(dp, -1, sizeof(dp));
        dfs(0);
        format(0);
        cout << '\n';
    }

    return 0;
}
