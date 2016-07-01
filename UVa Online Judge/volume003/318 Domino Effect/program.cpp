// Domino Effect
// UVa IDs: 318
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

struct edge
{
    int number, seconds;
};

int main(int argc, char *argv[])
{
    int n, m, cases = 0;
    int start, end, seconds;
    int parent[510], distances[510], visited[510];
    int linked[510][510], length[510][510];
    
    vector<vector<edge>> edges; 
    while (cin >> n >> m, n)
    {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                linked[i][j] = 0, length[i][j] = 0;
        
        edges.clear();
        edges.assign(n + 1, vector<edge>());
        
        cout << "System #" << ++cases << endl;
        
        for (int i = 1; i <= m; i++)
        {
            cin >> start >> end >> seconds;
            edges[start].push_back((edge){end, seconds});
            edges[end].push_back((edge){start, seconds});
            linked[start][end] = 1, length[start][end] = seconds;
        }
        
        fill(parent, parent + 510, -1);
        fill(distances, distances + 510, -1);
        fill(visited, visited + 510, 0);
        
        int current = 1;
        distances[current] = 0;

        // dijkstra
        while (visited[current] == 0)
        {
            visited[current] = 1;
            
            for (int i = 0; i < edges[current].size(); i++)
            {
                edge e = edges[current][i];
                if (visited[e.number] == 0)
                {
                    if (distances[e.number] == -1 || distances[current] + e.seconds < distances[e.number])
                    {
                        distances[e.number] = distances[current] + e.seconds;
                        parent[e.number] = current;
                    }
                }
            }
            
            int minDistances = -1;
            for (int i = 1; i <= n; i++)
                if (visited[i] == 0)
                {
                    if (minDistances == -1 || distances[i] < minDistances)
                    {
                        minDistances = distances[i];
                        current = i;
                    }
                }
        }
        
        bool isEndAtKey = true;
        int startKey = 1, endKey = 1;
        
        double maxWastedTime = 0.0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (linked[i][j])
                {
                    double wastedTime1 = distances[i];
                    double wastedTime2 = distances[j];
                    
                    if (i == parent[j] || j == parent[i])
                    {
                        if (wastedTime1 > maxWastedTime)
                        {
                            isEndAtKey = true;
                            endKey = i;
                            maxWastedTime = wastedTime1;
                        }
                        
                        if (wastedTime2 > maxWastedTime)
                        {
                            isEndAtKey = true;
                            endKey = j;
                            maxWastedTime = wastedTime2;
                        }
                    }
                    else
                    {
                        double wastedTime3 = max(wastedTime1, wastedTime2);
                        wastedTime3 += fabs(length[i][j] - fabs(wastedTime1 - wastedTime2)) / 2.0;
                        if (wastedTime3 > maxWastedTime)
                        {
                            isEndAtKey = false;
                            startKey = min(i, j);
                            endKey = max(i, j);
                            maxWastedTime = wastedTime3;
                        }
                    }
                }
                
        
        cout << "The last domino falls after ";
        cout << fixed << setprecision(1) << maxWastedTime << " seconds, ";
        if (isEndAtKey)
            cout << "at key domino " << endKey << "." << endl;
        else
            cout << "between key dominoes " << startKey << " and " << endKey << "." << endl;
        cout << endl;
    }
    
	return 0;
}
