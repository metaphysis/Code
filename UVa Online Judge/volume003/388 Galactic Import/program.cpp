// Galactic Import
// UVa IDs: 388
// Verdict: Accepted
// Submission Date: 2016-07-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

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
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

struct edge
{
    int to, weight;
    
    bool operator<(const edge &another) const
    {
        return weight > another.weight;
    }
};

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int n;
    while (cin >> n)
    {
        vector<vector<int>> edges(30);
        vector<double> value(30);
        
        char planet;
        string line;

        for (int i = 1; i <= n; i++)
        {
            cin >> planet;
            cin >> value[planet - 'A'];
            cin >> line;
            
            assert('A' <= planet && planet <= 'Z');
            
            for (auto letter : line)
                if (letter == '*')
                {
                    edges[planet - 'A'].push_back(26);
                    edges[26].push_back(planet - 'A');
                }
                else
                {
                    edges[planet - 'A'].push_back(letter - 'A');
                    edges[letter - 'A'].push_back(planet - 'A');
                }
        }
        
        vector<int> distances(30);
        fill(distances.begin(), distances.end(), 100000);
        
        distances[26] = 0;
        priority_queue<edge> unvisited;
        unvisited.push((edge){26, 0});
        
        while (!unvisited.empty())
        {
            edge v = unvisited.top();
            unvisited.pop();

            for (auto e : edges[v.to])
                if (distances[v.to] + 1 < distances[e])
                {
                    distances[e] = distances[v.to] + 1;
                    unvisited.push((edge){e, distances[e]});
                }
        }
        
        double maxValue = -1.0;
        int import_from;
        for (int i = 0; i <= 25; i++)
            if (distances[i] < 100000)
            {
                double finalValue = value[i] * pow(0.95, distances[i] - 1);
                if (finalValue > maxValue)
                {
                    maxValue = finalValue;
                    import_from = i;
                }
            }
            
        cout << "Import from " << (char)('A' + import_from) << endl;
    }
    
	return 0;
}
