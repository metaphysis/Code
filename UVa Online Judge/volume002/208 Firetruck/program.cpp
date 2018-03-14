// Firetruck
// UVa ID: 208
// Verdict: Accepted
// Submission Date: 2016-04-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAX_INT = numeric_limits<int>::max();

vector < vector < int > > edges;
vector < bool > visited;
vector < int > path;
int fire, routes;
long long weight[21][21];

void floyd()
{
    for (int k = 1; k <= 20; k++)
        for (int i = 1; i <= 20; i++)
            for (int j = 1; j <= 20; j++)
            {
                long long through = weight[i][k] + weight[k][j];
                if (weight[i][j] > through)
                    weight[i][j] = through;
            }
}

void backtrack(int corner, int length)
{
    if (corner == fire)
    {
        routes++;
        cout << 1;
        for (int i = 0; i < length; i++)
            cout << " " << path[i];
        cout << "\n";
        return;
    }
    
    for (int i = 0; i < edges[corner].size(); i++)
    {
        int next = edges[corner][i];
        if (visited[next] == false && weight[next][fire] < MAX_INT)
        {
            visited[next] = true;
            path[length] = next;
            backtrack(next, length + 1);
            visited[next] = false;
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    int cases = 0, start, end;
    
    visited.resize(21);
    path.resize(21);
        
    while (cin >> fire)
    {
        edges.clear();
        edges.resize(21);
        
        for (int i = 1; i <= 20; i++)
            for (int j = 1; j <= 20; j++)
                weight[i][j] = MAX_INT;
            
        while (cin >> start >> end, start && end)
        {
            edges[start].push_back(end);
            edges[end].push_back(start);
            weight[start][end] = 1;
            weight[end][start] = 1;
        }
        
        for (int i = 0; i < edges.size(); i++)
            if (edges[i].size() > 0)
            {
                sort(edges[i].begin(), edges[i].end());
                int n = unique(edges[i].begin(), edges[i].end()) -
                    edges[i].begin();
                edges[i].erase(edges[i].begin() + n, edges[i].end());
            }
        
        cases++;
        cout << "CASE " << cases << ":\n";
        
        floyd();
        
        routes = 0;
        fill(visited.begin(), visited.end(), false);
        visited[1] = true;
        backtrack(1, 0);
        
        cout << "There are ";
        cout << routes;
        cout << " routes from the firestation to streetcorner ";
        cout << fire << ".\n";
    }
    
	return 0;
}
