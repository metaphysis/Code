// Party at Hali-Bula
// UVa ID: 1220
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int N;
int dp[256][2];
list<int> edges[256];

int dfs(int u)
{
    dp[u][0] = 0, dp[u][1] = 1;
    for (auto v : edges[u])
    {
        dfs(v);
        dp[u][0] += max(dp[v][0], dp[v][1]);
        dp[u][1] += dp[v][0];
    }
    return max(dp[u][0], dp[u][1]);
}

bool isUnique(int u, int state)
{
    for (auto v : edges[u])
    {
        if (state == 0)
        {
            if (dp[v][0] == dp[v][1]) return false;
            if (!isUnique(v, dp[v][0] < dp[v][1]))
                return false;
        }
        else
        {
            if (!isUnique(v, 0))
                return false;
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> N)
    {
        if (N == 0) break;
        for (int i = 0; i <= N; i++)
            edges[i].clear();

        map<string, int> indexer;
        string name1, name2;
        // Big Boss.
        cin >> name1;
        indexer[name1] = 0;
        
        int idx = 1;
        for (int i = 1; i < N; i++)
        {
            cin >> name1 >> name2;
            if (indexer.find(name1) == indexer.end())
                indexer[name1] = idx++;
            if (indexer.find(name2) == indexer.end())
                indexer[name2] = idx++;
            edges[indexer[name2]].push_back(indexer[name1]);
        }

        cout << dfs(0) << ' ';
        if (dp[0][0] == dp[0][1])
        {
            cout << "No\n";
            continue;
        }
        cout << (isUnique(0, dp[0][0] < dp[0][1]) ? "Yes" : "No") << '\n';
    }

    return 0;
}
