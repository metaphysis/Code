// Jill's Bike
// UVa ID: 238
// Verdict: Accepted
// Submission Date: 2016-06-02
// UVa Run Time: 0.200s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <sstream>
#include <stack>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    int grid[500][4], altitude[500];
    int n, m, cases = 0;
    
    while (cin >> n >> m)
    {
        memset(grid, 0, sizeof(grid));
        memset(altitude, 0, sizeof(altitude));
        
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                cin >> altitude[i * m + j];
        
        // create graph
        int starti, startj, endi, endj;
        while (cin >> starti >> startj >> endi >> endj, starti > 0)
        {
            if (starti == endi)
            {
                if (startj < endj)
                {
                    for (int j = startj; j < endj; j++)
                    {
                        if (abs(altitude[starti * m + j] - altitude[starti * m + j + 1]) <= 10)
                            grid[starti * m + j][0] = starti * m + j + 1;
                    }
                }
                else
                {
                    for (int j = startj; j > endj; j--)
                    {
                        if (abs(altitude[starti * m + j] - altitude[starti * m + j - 1]) <= 10)
                            grid[starti * m + j][1] = starti * m + j - 1;
                    }
                }
            }
            else if (startj == endj)
            {
                if (starti < endi)
                {
                    for (int i = starti; i < endi; i++)
                    {
                        if (abs(altitude[i * m + startj] - altitude[(i + 1) * m + startj]) <= 10)
                            grid[i * m + startj][2] = (i + 1) * m + startj;
                    }
                }
                else
                {
                    for (int i = starti; i > endi; i--)
                    {
                        if (abs(altitude[i * m + startj] - altitude[(i - 1) * m + startj]) <= 10)
                            grid[i * m + startj][3] = (i - 1) * m + startj;
                    }
                }
            }
        }
            
        // find shortest path
        while (cin >> starti >> startj >> endi >> endj, starti > 0)
        {
            if (cases++)
                cout << endl;
            
            if (starti == endi && startj == endj)
            {
                cout << "To get from " << starti << "-" << startj;
                cout << " to " << endi << "-" << endj << ", stay put!" << endl;
                continue;
            }
            
            // dijkstra
            int distances[500], parent[500] = {0}, visited[500] = {0};
            for (int i = 0; i < 500; i++)
                distances[i] = 10000;
                
            int current = starti * m + startj;
            distances[current] = 0;
            
            while (visited[current] == 0)
            {
                visited[current] = 1;
                
                
                for (int i = 0; i < 4; i++)
                {
                    if (grid[current][i] > 0 && !visited[grid[current][i]])
                    {
                        if (distances[current] + 1 < distances[grid[current][i]])
                        {
                            distances[grid[current][i]] = distances[current] + 1;
                            parent[grid[current][i]] = current;
                        }
                    }
                }
                
                int minDistance = 10000;
                for (int i = 1; i <= n; i++)
                    for (int j = 1; j <= m; j++)
                    {
                        int next = i * m + j;
                        if (!visited[next] && distances[next] < minDistance)
                        {
                            minDistance = distances[next];
                            current = next;
                        }
                    }
            }
            
            int start = starti * m + startj;
            int end = endi * m + endj;
            
            if (distances[end] == 10000)
            {
                cout << "There is no acceptable route from ";
                cout << starti << "-" << startj;
                cout << " to " << endi << "-" << endj << "." << endl;
            }
            else
            {
                vector <pair<int, int>> path;
                do
                {
                    int ii = end / m, jj = end % m;
                    if (jj == 0)
                    {
                        ii--;
                        jj = m;
                    }
                    
                    path.push_back(make_pair(ii, jj));
                    end = parent[end];
                } while (end != start);
                
                reverse(path.begin(), path.end());
                
                cout << starti << "-" << startj;
                for (int i = 0; i < path.size(); i++)
                    cout << " to " << path[i].first << "-" << path[i].second;
                cout << endl;
            }
        }
    }
    
	return 0;
}
