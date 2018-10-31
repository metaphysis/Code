// Bribing FIPA
// UVa degree: 1222
// Verdict: Accepted
// Submission Date: 2018-10-31
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 210, INF = 0x3f3f3f3f;

int n, m, diamonds[MAXV], C, degree[MAXV], parent[MAXV], dp[MAXV][MAXV];
list<int> edges[MAXV];
map<string, int> menu;
vector<int> S;

void makeSet()
{
    for (int i = 0; i < MAXV; i++) parent[i] = i;
}

int findSet(int x)
{
    return (x == parent[x] ? x : parent[x] = findSet(parent[x]));
}

void unionSet(int x, int y)
{
    x = findSet(x), y = findSet(y);
    if (x != y) parent[y] = x;
}

int dfs(int u)
{
    int r = 1;
    for (auto v : edges[u])
    {
        r += dfs(v);
        unionSet(u, v);
    }
    int C = S.size();
    for (int i = C - 1; i >= 0; i--)
    {
        if (u == findSet(S[i])) continue;
        for (int j = n; j >= 0; j--)
        {
            if (j >= r)
                dp[C][j] = min(dp[C][j], dp[i][j - r] + diamonds[u]);
            else
                dp[C][j] = dp[i][j];
        }
    }
    S.push_back(u);
    return r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        if (line == "#") break;
        istringstream iss(line);
        iss >> n >> m;

        int idx = 1;
        menu.clear();
        memset(degree, 0, sizeof(degree));
        for (int i = 1; i <= n; i++) edges[i].clear();

        int diamondCount, xi, yi;
        string countryName, dcName;
        for (int i = 1; i <= n; i++)
        {
            getline(cin, line);
            iss.clear();
            iss.str(line);
            iss >> countryName >> diamondCount;
            if (menu.find(countryName) == menu.end())
            {
                menu[countryName] = idx;
                idx++;
            }
            diamonds[xi = menu[countryName]] = diamondCount;
            while (iss >> dcName)
            {
                if (menu.find(dcName) == menu.end())
                {
                    menu[dcName] = idx;
                    idx++;
                }
                edges[xi].push_back(yi = menu[dcName]);
                degree[yi]++;
            }
        }

        makeSet();
        memset(dp, INF, sizeof(dp));
        dp[0][0] = 0;
        S.clear();
        S.push_back(0);
        for (int i = 1; i <= n; i++)
            if (!degree[i])
                dfs(i);

        int cost = INF;
        for (int i = 0; i <= (n + 1); i++)
            for (int j = m; j <= n; j++)
                cost = min(cost, dp[i][j]);
        cout << cost << '\n';
    }

    return 0;
}
