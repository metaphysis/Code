// Killing Aliens in Borg Maze
// UVa ID: 10307
// Verdict: Accepted
// Submission Date: 2018-12-18
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 2600, MAXE = 20000;

struct edge
{
    int from, to, weight;
    edge (int from = 0, int to = 0, int weight = 0): from(from), to(to), weight(weight) {}
    bool operator<(const edge &e) const { return weight < e.weight; }
};

edge edges[MAXE];
int n, m, parent[MAXV], ranks[MAXV];

void makeSet()
{
    for (int i = 0; i < n; i++) {
        parent[i] = i; ranks[i] = 0;
    }
}

int findSet(int x)
{
    return (parent[x] == x ? x : parent[x] = findSet(parent[x]));
}

bool unionSet(int x, int y)
{
    x = findSet(x), y = findSet(y);
    if (x != y) {
        if (ranks[x] > ranks[y]) parent[y] = x;
        else {
            parent[x] = y;
            if (ranks[x] == ranks[y]) ranks[y]++;
        }
        return true;
    }
    return false;
}

int kruskal()
{
    int minWeightSum = 0;

    makeSet();
    sort(edges, edges + m);

    for (int i = 0; i < m; i++)
        if (unionSet(edges[i].from, edges[i].to))
            minWeightSum += edges[i].weight;

    return minWeightSum;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    int x, y, visited[55][55], offset[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
    char grid[55][55];

    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> x >> y;
        cin.ignore(256, '\n');
        string line;
        memset(grid, ' ', sizeof(grid));
        for (int i = 0; i < y; i++)
        {
            getline(cin, line);
            for (int j = 0; j < min(x, (int)(line.length())); j++)
                grid[i][j] = line[j];
        }

        n = x * y, m = 0;
        for (int i = 0; i < y; i++)
            for (int j = 0; j < x; j++)
            {
                if (grid[i][j] == 'A' || grid[i][j] == 'S')
                {
                    memset(visited, 0, sizeof(visited));
                    queue<int> Y, X, D;
                    Y.push(i), X.push(j), D.push(0);
                    visited[i][j] = 1;
                    while (!Y.empty())
                    {
                        int r = Y.front(); Y.pop();
                        int c = X.front(); X.pop();
                        int d = D.front(); D.pop();
                        if (grid[r][c] == 'A' || grid[r][c] == 'S')
                            edges[m++] = edge(i * x + j, r * x + c, d);
                        for (int k = 0; k < 4; k++)
                        {
                            int nextr = r + offset[k][0], nextc = c + offset[k][1];
                            if (nextr < 0 || nextr >= y || nextc < 0 || nextc >= x) continue;
                            if (grid[nextr][nextc] == '#') continue;
                            if (visited[nextr][nextc]) continue;
                            visited[nextr][nextc] = 1;
                            Y.push(nextr), X.push(nextc), D.push(d + 1);
                        }
                    }
                }
            }
        cout << kruskal() << '\n';
    }

    return 0;
}
