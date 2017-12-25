// Tic Tac Toe
// UVa ID: 10363
// Verdict: Accepted
// Submission Date: 2017-12-25
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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    char g[3][3];
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        int sx = 0, so = 0;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cin >> g[i][j];
                if (g[i][j] == 'X') sx++;
                if (g[i][j] == 'O') so++;
            }
        }
        
        int hx = 0, vx = 0, dx1 = 0, dx2 = 0;
        int ho = 0, vo = 0, do1 = 0, do2 = 0;
        int wx = 0, wo = 0;

        for (int i = 0; i < 3; i++)
        {
            if (g[i][0] == g[i][1] && g[i][1] == g[i][2])
            {
                if (g[i][0] == 'X') hx++, wx++;
                if (g[i][0] == 'O') ho++, wo++;
            }
            if (g[0][i] == g[1][i] && g[1][i] == g[2][i])
            {
                if (g[0][i] == 'X') vx++, wx++;
                if (g[0][i] == 'O') vo++, wo++;
            }
            
        }

        if (g[0][0] == g[1][1] && g[1][1] == g[2][2])
        {
            if (g[0][0] == 'X') dx1++, wx++;
            if (g[0][0] == 'O') do1++, wo++;
        }
        if (g[0][2] == g[1][1] && g[1][1] == g[2][0])
        {
            if (g[0][2] == 'X') dx2++, wx++;
            if (g[0][2] == 'O') do2++, wo++;
        }

        if (wx > 0 && wo > 0) { cout << "no\n"; continue; }
        if (hx > 1 || vx > 1 || ho > 1 || vx > 1) { cout << "no\n"; continue; }
        if (hx > 0 && vx > 0 && dx2 > 0) { cout << "no\n"; continue; }
        if (ho > 0 && vo > 0 && do2 > 0) { cout << "no\n"; continue; }
        if (sx != so && sx != so + 1) { cout << "no\n"; continue; }
        if (sx == so && wx > 0) { cout << "no\n"; continue; }
        if (sx == so + 1 && wo > 0) { cout << "no\n"; continue; }
        
        cout << "yes\n";
    }

    return 0;
}
