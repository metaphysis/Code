// Now or Later
// UVa ID: 1146
// Verdict: Accepted
// Submission Date: 2018-05-07
// UVa Run Time: 0.140s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 4096;

int n, time1[MAXV], time2[MAXV];
int dfn[MAXV], low[MAXV], scc[MAXV], dfstime, cscc;
vector<list<int>> edges(MAXV);
stack<int> s;

void initialize()
{
    dfstime = 0, cscc = 0;
    while (!s.empty()) s.pop();
    for (int u = 0; u < MAXV; u++) edges[u].clear();
    memset(dfn, 0, sizeof(dfn)); memset(scc, 0, sizeof(scc));
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++dfstime; s.push(u);
    for (auto v : edges[u])
    {
        if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
        else if (!scc[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])
    {
        ++cscc;
        while (true)
        {
            int v = s.top(); s.pop();
            scc[v] = cscc;
            if (u == v) break;
        }
    }
}

bool feasible(int gap)
{
    initialize();
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
        {
            int k = 0;

            int ii = i * 2, jj = j * 2;

            // Conflict: aircraft i and j both land early.
            // !i OR !j
            if (abs(time1[i] - time1[j]) < gap)
            {
                edges[ii].push_back(jj ^ 1);
                edges[jj].push_back(ii ^ 1);
                k++;
            }
            
            // Conflict: Aircraft i lands early and j lands later.
            // !i OR j
            if (abs(time1[i] - time2[j]) < gap)
            {
                edges[ii].push_back(jj);
                edges[jj ^ 1].push_back(ii ^ 1);
                k++;
            }
            
            // Conflict: aircraft i and j both land later.
            // i OR j
            if (abs(time2[i] - time2[j]) < gap)
            {
                edges[ii ^ 1].push_back(jj);
                edges[jj ^ 1].push_back(ii);
                k++;
            }

            // Conflict: aircraft i lands later and j lands early.
            // i OR !j
            if (abs(time2[i] - time1[j]) < gap)
            {
                edges[ii ^ 1].push_back(jj ^ 1);
                edges[jj].push_back(ii);
                k++;
            }
            
            if (k == 4) return false;
        }

    for (int i = 0; i < 2 * n; i++)
            if (!dfn[i])
                tarjan(i);

    for (int i = 0; i < 2 * n; i += 2)
        if (scc[i] == scc[i ^ 1])
            return false;
    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n)
    {
        int maxTime = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> time1[i] >> time2[i];
            maxTime = max(maxTime, max(time1[i], time2[i]));
        }
        int low = 0, high = maxTime, gap;
        while (low <= high)
        {
            gap = (low + high) / 2;
            if (feasible(gap)) low = gap + 1;
            else high = gap - 1;
        }
        cout << (low + high) / 2 << '\n';
    }

    return 0;
}
