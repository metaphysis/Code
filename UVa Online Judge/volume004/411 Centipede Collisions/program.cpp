// Centipede Collisions
// UVa ID: 411
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

char grid[30][30], hole[30][30];

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    map<char, pair<int, int>> direction = {
        {'L', {-1, 0}}, {'U', {0, 1}}, {'R', {1, 0}}, {'D', {0, -1}}
    };

    int n;
    while (cin >> n)
    {
        memset(grid, '.', sizeof(grid));
        memset(hole, '.', sizeof(hole));
        
        char orientation;
        int length, x, y;

        map<int, char> heading;
        for (int i = 0; i < n; i++)
        {
            cin >> orientation >> length >> x >> y;
            heading[i] = orientation;

            for (int j = 1; j <= length; j++)
            {
                grid[29 - y][x] = '0' + i;
                x += (-1) * direction[orientation].first;
                y += (-1) * direction[orientation].second;
            }
        }
        
        while (true)
        {
            
        }
        
        cout << "   0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2\n";
        cout << "   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9\n";
        for (int i = 0; i < 30; i++)
        {
            int label = 29 - i;
            if (label < 10)
                cout << '0';
            cout << label;
            
            for (int j = 0; j < 30; j++)
                cout << ' ' << grid[i][j];
            cout << '\n';
        }
        cout << '\n';
    }
    
	return 0;
}
