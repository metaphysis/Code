// Injured Queen Problem
// UVa ID: 10401
// Verdict: Accepted
// Submission Date: 2018-02-24
// UVa Run Time: 0.060s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const int MAXV = 256;

int n, visited[MAXV];
string line;
long long cnt[MAXV];
list<int> edges[MAXV];

int getRow(char c)
{
    if (c == '?') return 0;
    if (isdigit(c)) return c - '0';
    return c - 'A' + 10;
}

bool addEdge(int r1, int r2, int cln1, int cln2)
{
    if (r1 == 0 && r2 == 0)
    {
        for (int u = 1; u <= n; u++)
            for (int v = 1; v <= n; v++)
            {
                if (abs(u - v) <= 1) continue;
                edges[(cln1 - 1) * n + u].push_back((cln2 - 1) * n + v);
            }
    }
    else if (r1 == 0 && r2 != 0)
    {
        int v = r2;
        for (int u = 1; u <= n; u++)
        {
            if (abs(u - v) <= 1) continue;
            edges[(cln1 - 1) * n + u].push_back((cln2 - 1) * n + v);
        }
    }
    else if (r1 != 0 && r2 == 0)
    {
        int u = r1;
        for (int v = 1; v <= n; v++)
        {
            if (abs(u - v) <= 1) continue;
            edges[(cln1 - 1) * n + u].push_back((cln2 - 1) * n + v);
        }
    }
    else
    {
        int u = r1, v = r2;
        if (abs(u - v) <= 1) return false;
        u += (cln1 - 1) * n, v += (cln2 - 1) * n;
        edges[u].push_back(v);
    }
    
    return true;
}

void dfs(int u)
{
    visited[u] = 1;
    for (auto v : edges[u])
    {
        if (!visited[v])
            dfs(v);
        cnt[u] += cnt[v];
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int u, v;

    while (getline(cin, line))
    {
        if (line.length() == 0) continue;

        n = line.size();
        for (int i = 0; i < MAXV; i++) edges[i].clear();

        if (line.front() == '?')
        {
            for (int i = 1; i <= n; i++)
            {
                u = 0, v = i;
                edges[u].push_back(v);
            }
        }
        else
        {
            u = 0, v = getRow(line.front());
            edges[u].push_back(v);
        }

        bool flag = true;
        for (int i = 1; i < line.size(); i++)
        {
            if (!addEdge(getRow(line[i - 1]), getRow(line[i]), i, i + 1))
            {
                flag = false;
                break;
            }
        }

        if (line.back() == '?')
        {
            for (int i = 1; i <= n; i++)
            {
                u = (n - 1) * n + i, v = n * n + 1;
                edges[u].push_back(v);
            }
        }
        else
        {
            u = (n - 1) * n + getRow(line.back()), v = n * n + 1;
            edges[u].push_back(v);
        }

        if (flag)
        {
            memset(cnt, 0, sizeof(cnt));
            memset(visited, 0, sizeof(visited));
            cnt[n * n + 1] = 1;
            dfs(0);
            cout << cnt[0] << '\n';
        }
        else cout << 0 << '\n';
    }

    return 0;
}
