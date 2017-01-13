// Audiophobia
// UVa ID: 10048
// Verdict: Accepted
// Submission Date: 2017-01-13
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
#include <vector>

using namespace std;

const int MAXV = 110, MAX_DECIBEL = 1000000;

int C, S, Q, decibels[MAXV][MAXV];

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int c1, c2, d, cases = 0;
    while (cin >> C >> S >> Q, C || S || Q)
    {
        for (int i = 1; i <= C; i++)
            for (int j = 1; j <= C; j++)
            {
                decibels[i][j] = MAX_DECIBEL;
                if (i == j) decibels[i][j] = 0;
            }
            
        for (int i = 1; i <= S; i++)
        {
            cin >> c1 >> c2 >> d;
            decibels[c1][c2] = decibels[c2][c1] = d;
        }
        
        // Floyd-Warshall min-max distance.
        for (int k = 1; k <= C; k++)
            for (int i = 1; i <= C; i++)
                for (int j = 1; j <= C; j++)
                    if (decibels[i][k] < MAX_DECIBEL && decibels[k][j] < MAX_DECIBEL)
                        decibels[i][j] = min(decibels[i][j], max(decibels[i][k], decibels[k][j]));

        if (cases++ > 0) cout << '\n';
        cout << "Case #" << cases << '\n';
         
        for (int i = 1; i <= Q; i++)
        {
            cin >> c1 >> c2;
            if (decibels[c1][c2] == MAX_DECIBEL) cout << "no path\n";
            else cout << decibels[c1][c2] << '\n';
        }
    }
    
    return 0;
}
