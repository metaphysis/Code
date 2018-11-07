// Perfect Service
// UVa ID: 1218
// Verdict: Accepted
// Submission Date: 2018-11-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 10010, INF = 0x3f3f3f3f;

struct EDGE
{
    int u, v, next;
    EDGE (int u = 0, int v = 0, int next = 0): u(u), v(v), next(next) {}
} edges[MAXV << 1];

struct NODE
{
    int in, selfOut, selfChildOut;
} dp[MAXV];

int indx, head[MAXV];

void addEdge(int u, int v)
{
    edges[indx] = EDGE(u, v, head[u]);
    head[u] = indx++;
    edges[indx] = EDGE(v, u, head[v]);
    head[v] = indx++;
}

int dfs(int u, int father)
{
    dp[u].in = 1;
    dp[u].selfOut = dp[u].selfChildOut = 0;
    int x = INF, noChild = 1, noChildIn = 1, childIn = 0;
    for (int i = head[u]; ~i; i = edges[i].next)
    {
        int v = edges[i].v;
        if (v == father) continue;
        dfs(v, u);
        noChild = 0;
        //dp[u].in += min(dp[v].in, min(dp[v].selfOut, dp[v].selfChildOut));
        dp[u].in += min(dp[v].in, dp[v].selfChildOut);
        dp[u].selfOut += min(dp[v].in, dp[v].selfOut);
        if (dp[v].in > dp[v].selfOut) x = min(x, dp[v].in - dp[v].selfOut);
        else
        {
            noChildIn = 0;
            if (dp[v].in < dp[v].selfOut) childIn++;
        }
        dp[u].selfChildOut = min(INF, dp[u].selfChildOut + dp[v].selfOut);
    }
    if (noChild) dp[u].selfOut = INF;
    else 
    {
        if (noChildIn) dp[u].selfOut += x;
    }
    return childIn;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    while (cin >> n)
    {
        indx = 0;
        memset(head, -1, sizeof(head));
        for (int i = 1, u, v; i < n; i++)
        {
            cin >> u >> v;
            u--, v--;
            addEdge(u, v);
        }
        int childIn = dfs(0, 0);
        if (dp[0].selfOut < dp[0].in)
        {
            if (childIn >= 2) cout << dp[0].in;
            else cout << dp[0].selfOut;
        }
        else cout << dp[0].in;
        cout << '\n';
        cin >> n;
        if (n == -1) break;
    }

    return 0;
}
