// Graph Coloring
// UVa IDs: 193
// Verdict:
// Submission Date:
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

vector < vector < int > > edges;
vector < bool > visited;
vector < int > colors;
vector < int > black;
bool colorable = true;
int maximum;

bool bfs(int start)
{
    queue <int> q;

    colors[start] = 1;
    q.push(start);
    visited[start] = true;

    while (!q.empty())
    {
        int v = q.front();
        
        q.pop();

        for (int i = 0; i < edges[v].size(); i++)
        {
            if (visited[edges[v][i]] == false)
            {
                q.push(edges[v][i]);
                visited[edges[v][i]] = true;
            }

            if (colors[edges[v][i]] == -1)
                colors[edges[v][i]] = (colors[v] == 1 ? 0 : 1);
            else if (colors[edges[v][i]] == colors[v] && colors[v] == 1)
                return false;
        }
    }

    return true;
}

void findMaximum(int n)
{
    maximum = 0;
    visited.resize(n + 1);
    colors.resize(n + 1);

    for (int i = 1; i <= n; i++)
    {
        fill(visited.begin(), visited.end(), false);
        fill(colors.begin(), colors.end(), -1);

        if(bfs(i) == false)
            continue;
        
        int blackCounter = 0;
        for (int j = 1; j <= n; j++)
            if (colors[j] == 1 || colors[j] == -1)
                blackCounter++;

        if (blackCounter > maximum)
        {
            maximum = blackCounter;
            black.clear();
            for (int j = 1; j <= n; j++)
                if (colors[j] == 1 || colors[j] == -1)
                    black.push_back(j);
        }
    }

    cout << maximum << "\n";
    for (int i = 0; i < black.size(); i++)
        cout << (i > 0 ? " " : "" ) << black[i];
    cout << "\n";
}

int main(int argc, char *argv[])
{
    int m, n, k, start, end;

    cin >> m;
    while (m--)
    {
        cin >> n >> k;

        edges.clear();
        edges.resize(n + 1);

        for (int i = 1; i <= k; i++)
        {
            cin >> start >> end;
            edges[start].push_back(end);
            edges[end].push_back(start);
        }

        findMaximum(n);
    }

    return 0;
}
