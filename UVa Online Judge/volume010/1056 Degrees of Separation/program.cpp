// Degrees of Separation
// UVa ID: 1056
// Verdict: Accepted
// Submission Date: 2017-04-11
// UVa Run Time: 0.000s
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

const int MAX_DIST = 100000;

int P, R;
int degree[60][60];
int visited[60], inNetwork;

void dfs(int i)
{
    visited[i] = 1;
    inNetwork++;
    
    for (int j = 1; j <= P; j++)
        if (degree[i][j] < MAX_DIST && !visited[j])
            dfs(j);
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0;
    
    while (cin >> P >> R)
    {
        if (P == 0) break;
        
        cout << "Network " << ++cases << ": ";
        
        string name1, name2;
        map<string, int> indexer;
        int count = 1;
        
        for (int i = 1; i <= P; i++)
        {
            for (int j = 1; j <= P; j++)
                degree[i][j] = MAX_DIST;
            degree[i][i] = 0;
        }
        
        for (int i = 1; i <= R; i++)
        {
            cin >> name1 >> name2;
            if (indexer[name1] == 0) indexer[name1] = count++;
            if (indexer[name2] == 0) indexer[name2] = count++;
            degree[indexer[name1]][indexer[name2]] = 1;
            degree[indexer[name2]][indexer[name1]] = 1;
        }
        
        memset(visited, 0, sizeof(visited));
        inNetwork = 0;
        dfs(1);
        
        if (inNetwork < P)
        {
            cout << "DISCONNECTED\n\n";
            continue;
        }
        
        for (int k = 1; k <= P; k++)
            for (int i = 1; i <= P; i++)
                for (int j = 1; j <= P; j++)
                    if (degree[i][k] < MAX_DIST && degree[k][j] < MAX_DIST && degree[i][j] > degree[i][k] + degree[k][j])
                        degree[i][j] = degree[i][k] + degree[k][j];
                        
        int maxdegree = 0;
        for (int i = 1; i <= P; i++)
            for (int j = 1; j <= P; j++)
                maxdegree = max(maxdegree, degree[i][j]);
                
        cout << maxdegree << "\n\n";
    }
    
    return 0;
}
