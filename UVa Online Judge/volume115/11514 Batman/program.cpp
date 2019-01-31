// Batman
// UVa ID: 11514
// Verdict: Accepted
// Submission Date: 2019-01-31
// UVa Run Time: 0.120s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010, INF = 0x3f3f3f3f;

struct power
{
    string name;
    int attack, energy;
} abilities[MAXN];

struct villain
{
    string name;
    int defense;
    set<string> affected;
} villains[MAXN];

int P, V, E;
int dp[MAXN][MAXN];

int dfs(int p, int v)
{
    if (v == V) return 0;
    if (p == P) return INF;
    if (~dp[p][v]) return dp[p][v];
    int r = INF;
    if (villains[v].affected.find(abilities[p].name) != villains[v].affected.end())
        if (abilities[p].attack >= villains[v].defense)
            r = min(r, abilities[p].energy + dfs(p + 1, v + 1));
    r = min(r, dfs(p + 1, v));
    return dp[p][v] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string superpowers;
    while (cin >> P >> V >> E)
    {
        if (P == 0 && V == 0 && E == 0) break;
        for (int i = 0; i < P; i++)
            cin >> abilities[i].name >> abilities[i].attack >> abilities[i].energy;
        for (int i = 0; i < V; i++)
        {
            cin >> villains[i].name >> villains[i].defense;
            villains[i].affected.clear();
            cin >> superpowers;
            string block;
            istringstream iss(superpowers);
            while (getline(iss, block, ','))
                villains[i].affected.insert(block);
        }
        for (int i = 0; i <= P; i++)
            for (int j = 0; j <= V; j++)
                dp[i][j] = -1;
        int needed = dfs(0, 0);
        if (needed <= E) cout << "Yes\n";
        else cout << "No\n";
    }

    return 0;
}
