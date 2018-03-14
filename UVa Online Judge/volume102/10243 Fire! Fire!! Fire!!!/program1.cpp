// Fire! Fire!! Fire!!!
// UVa ID: 10243
// Verdict: Accepted
// Submission Date: 2017-10-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1010;

struct edge
{
    int u, v, next;
};

int head[MAXV], nodes[MAXV], visited[MAXV], parent[MAXV], cnt = 0, n;
int covered[MAXV], mvs[MAXV];
edge edges[1010 * 1010];

int greedy()
{
    memset(covered, 0, sizeof(covered));
    memset(mvs, 0, sizeof(mvs));

    int cvn = 0;
    for (int i = cnt - 1; i >= 0; i--)
    {
        int u = nodes[i];
        if (!covered[u] && !covered[parent[u]])
        {
            mvs[parent[u]] = 1;
            covered[u] = covered[parent[u]] = 1;
            cvn++;
        }
    }
    return cvn;
}

void dfs(int u)
{
    nodes[cnt++] = u;
    for (int i = head[u]; ~i; i = edges[i].next)
        if (!visited[edges[i].v])
        {
            parent[edges[i].v] = u;
            visited[edges[i].v] = 1;
            dfs(edges[i].v);
        }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    
    int nv, v;
    while (cin >> n, n > 0)
    {
        cnt = 0;
        memset(head, -1, sizeof(head));
        for (int u = 1; u <= n; u++)
        {
            cin >> nv;
            for (int j = 1; j <= nv; j++)
            {
                cin >> v;
                edges[cnt] = (edge){u, v, head[u]};
                head[u] = cnt++;
                edges[cnt] = (edge){v, u, head[v]};
                head[v] = cnt++;
            }
        }

        cnt = 0;
        memset(visited, 0, sizeof(visited));
        memset(parent, -1, sizeof(parent));
        dfs(1);
        
        if (n == 1) cout << "1\n";
        else cout << greedy() << '\n';
    }
    
	return 0;
}
