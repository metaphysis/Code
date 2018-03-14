// Non-Stop Travel
// UVa ID: 341
// Verdict: Accepted
// Submission Date: 2016-06-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct edge
{
    int index, delay;
};

void findPath(int parent[], int end, int start)
{
    if (end != start)
        findPath(parent, parent[end], start);
    cout << " " << end;
}

int main(int argc, char *argv[])
{
    int n, cases = 0;
    while (cin >> n, n)
    {
        vector<vector<edge>> edges(n + 1);
        for (int i = 1; i <= n; i++)
        {
            int pairs;
            cin >> pairs;
            for (int j = 1; j <= pairs; j++)
            {
                int next, delay;
                cin >> next >> delay;
                edges[i].push_back((edge){next, delay});
            }
        }
        
        int start, end;
        cin >> start >> end;
        
        int distances[n + 1], parent[n + 1], visited[n + 1];
        
        fill(distances, distances + n + 1, -1);
        fill(parent, parent + n + 1, -1);
        fill(visited, visited + n + 1, 0);
        distances[start] = 0;
        
        int current = start;
        while (visited[current] == 0)
        {
            visited[current] = 1;
            for (int i = 0; i < edges[current].size(); i++)
            {
                edge e = edges[current][i];
                if (visited[e.index] == 0)
                {
                    if (distances[e.index] == -1 || distances[current] + e.delay < distances[e.index])
                    {
                        distances[e.index] = distances[current] + e.delay;
                        parent[e.index] = current;
                    }
                }
            }
            
            int minDistance = -1;
            for (int i = 1; i <= n; i++)
                if (visited[i] == 0)
                {
                    if (distances[i] >= 0 && (minDistance == -1 || distances[i] < minDistance))
                    {
                        minDistance = distances[i];
                        current = i;
                    }
                }
        }
        
        cout << "Case " << ++cases << ": Path =";
        findPath(parent, end, start);
        cout << "; " << distances[end] << " second delay" << endl;
    }
    
	return 0;
}
