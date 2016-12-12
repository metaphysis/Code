// Airline Comparison
// UVa ID: 869
// Verdict: Accepted
// Submission Date: 2016-12-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net
//
// uDebug: Solving this problem assuming a graph has either directed or
// undirected edges should get a verdict of "Accepted" on UVa. The solution on
// uDebug assumes that the graph has undirected edges.

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
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int airline1[26][26], airline2[26][26];
    int cases = 0, N;
    char from, to;
    
    cin >> cases;
    
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';
        
        memset(airline1, 0, sizeof(airline1));
        memset(airline2, 0, sizeof(airline2));
        
        cin >> N;
        for (int i = 1; i <= N; i++)
        {
            cin >> from >> to;
            airline1[from - 'A'][to - 'A'] = 1;
            airline1[to - 'A'][from - 'A'] = 1;
        }
        
        cin >> N;
        for (int i = 1; i <= N; i++)
        {
            cin >> from >> to;
            airline2[from - 'A'][to - 'A'] = 1;
            airline2[to - 'A'][from - 'A'] = 1;
        }
        
        for (int k = 0; k < 26; k++)
            for (int i = 0; i < 26; i++)
                for (int j = 0; j < 26; j++)
                {
                    if (airline1[i][k] && airline1[k][j])
                        airline1[i][j] = 1;
                    if (airline2[i][k] && airline2[k][j])
                        airline2[i][j] = 1;
                }
        
        bool same = true;
        for (int i = 0; i < 26; i++)
            for (int j = 0; j < 26; j++)
                if (airline1[i][j] != airline2[i][j])
                {
                    same = false;
                    goto print;
                }

        print:        
        cout << (same ? "YES\n" : "NO\n");
    }
    
	return 0;
}
