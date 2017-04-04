// Partitioning by Palindromes
// UVa ID: 11584
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

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

struct edge
{
    int from, weight;
    
    bool operator<(edge another) const
    {
        return weight > another.weight;
    }
};

string line;
int weights[1010][1010], dist[1010];

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    
    for (int c = 1; c <= cases; c++)
    {
        cin >> line;
        
        for (int i = 0; i < line.length(); i++)
            for (int j = i; j < line.length(); j++)
            {
                weights[i][j] = j - i + 1;
                bool isPalindrome = true;
                for (int x = i, y = j; x <= y; x++, y--)
                    if (line[x] != line[y])
                    {
                        isPalindrome = false;
                        break;
                    }
                if (isPalindrome) weights[i][j] = 1;
            }

        fill(dist, dist + line.length(), 10000);
        
        priority_queue<edge> unvisited;
        dist[0] = 0;
        unvisited.push((edge){0, dist[0]});

        while (!unvisited.empty())
        {
            edge v = unvisited.top();
            unvisited.pop();
            
            for (int i = v.from + 1; i < line.length(); i++)
                if (dist[i] > dist[v.from] + weights[v.from][i])
                {
                    dist[i] = dist[v.from] + weights[v.from][i];
                    unvisited.push((edge){i, dist[i]});
                }
        }
        
        cout << dist[line.length() - 1] << '\n';
    }
    
    return 0;
}
