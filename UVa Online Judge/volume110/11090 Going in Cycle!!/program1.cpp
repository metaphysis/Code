// Going in Cycle!!
// UVa ID: 11090
// Verdict: Accepted
// Submission Date: 2017-11-17
// UVa Run Time: 0.060s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 110, INF = -1;

struct edge
{
    int u, v, w;
    edge (int u = 0, int v = 0, int w = 0): u(u), v(v), w(w) {}
};

list<edge> edges[MAXV];

int n, m;
long long f[MAXV][MAXV];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, u, v, w;

    cin >> cases;
    for (int c1 = 1; c1 <= cases; c1++)
    {
        cin >> n >> m;

        for (int i = 0; i <= n; i++)
        {
            edges[i].clear();
            edges[n + 1].push_back(edge(n + 1, i, 0));
            
        }

        for (int i = 1; i <= m; i++)
        {
            cin >> u >> v >> w;
            u--, v--;
            edges[u].push_back(edge(u, v, w));
        }

        // Karp最小平均权值回路算法。
        // 按照原论文的要求，是选取任意一个顶点作为起始顶点，因此要求给定的图是强连通图，
        // 否则将无法正确计算最短路径（因为若图不是强联通的，则某些环可能无法从选择的起点到达，进而无法得到正确的最短路径）。
        // 由于此处给定的图可能并不是强连通图，无法照搬论文的方法。为了解决该问题，一个方法是求出各个连通子图的
        // 最小平均权值然后取最小值，这显然增加了代码实现的复杂度。分析可知，之所以要求图是强连通的，是为了便于选择任意一个顶点作为起点用于计算最短路径，
        // 那么可以在原图中新增一个“隐形”的起始顶点s，从s向原图的每个顶点连接一条有向边，则原图中所有的环都能够从s可达，从而使得最短路径能够计算，后续的算法过程也可以继续执行。
        // 设原图中顶点数目为n，由于新图增加了一个起始顶点，在迭代求步长为k的最短路径时，需要迭代n+1次而不是原来的n次。
        // 如果原图中顶点编号是从0开始，则由于新增的s顶点使用了编号0，原图中的顶点编号应该增加1，若原图中顶点编号从1开始，则可保持不变。
        // 按照算法要求，如果某个顶点v其步长为k的最短路径不存在，即Fk(v)=无穷大，则Fk(v)不参与计算，因为v肯定不在环上。
        memset(f, -1, sizeof(f));
        n += 1;
        f[0][0] = 0;
        for (int k = 0; k < n; k++)
            for (int j = 0; j < n; j++)
                for (auto e : edges[j])
                    if (f[k][e.u] != INF && (f[k + 1][e.v] == INF || f[k + 1][e.v] > f[k][e.u] + e.w))
                        f[k + 1][e.v] = f[k][e.u] + e.w;

        double minMean = 1e20;
        for (int k = 0; k < n - 1; k++)
        {
            double maxMean = -1;
            for (int i = 1; i < n - 1; i++)
                if (f[n][i] != INF)
                    maxMean = max(maxMean, (double)(f[n][i] - f[k][i]) / (n - k));
            minMean = min(minMean, maxMean);
        }

        cout << "Case #" << c1 << ": ";
        if (minMean < 0)
            cout << "No cycle found.\n";
        else
            cout << fixed << setprecision(2) << minMean << '\n';
    }

    return 0;
}
