// Citizen attention offices
// UVa ID: 10660
// Verdict: Accepted
// Submission Date: 2017-11-08
// UVa Run Time: 0.010s
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

    int dist[25][25];
    
    for (int i = 0; i < 25; i++)
    {
        int x1 = i / 5, y1 = i % 5;
        for (int j = 0; j < 25; j++)
        {
            int x2 = j / 5, y2 = j % 5;
            dist[i][j] = abs(x1 - x2) + abs(y1 - y2);
        }
    }
    
    int cases, n, count[25], coord[25];
    int r, c, p;

    cin >> cases;
    for (int c1 = 1; c1 <= cases; c1++)
    {
        cin >> n;

        memset(count, 0, sizeof(count));

        for (int i = 0; i < n; i++)
        {
            cin >> r >> c >> p;
            count[r * 5 + c] = p;
            coord[i] = r * 5 + c;
        }
        
        if (n <= 5)
        {
            for (int i = 0; i < 25 && n < 5; i++)
            {
                if (count[i]) continue;
                count[i] = 1;
                n++;
            }

            bool space = false;
            for (int i = 0; i < 25; i++)
                if (count[i])
                {
                    if (space) cout << ' ';
                    else space = true;
                    cout << i;
                }
            cout << '\n';
            continue;
        }

        int least = 0x3fffffff, sum, temp, aa, bb, cc, dd, ee;

        for (int a = 0; a <= 20; a++)
            for (int b = a + 1; b <= 21; b++)
                for (int c = b + 1; c <= 22; c++)
                    for (int d = c + 1; d <= 23; d++)
                        for (int e = d + 1; e <= 24; e++)
                        {
                            sum = 0;
                            for (int i = 0; i < n; i++)
                            {
                                temp = min(dist[coord[i]][a], dist[coord[i]][b]);
                                temp = min(temp, dist[coord[i]][c]);
                                temp = min(temp, dist[coord[i]][d]);
                                sum += count[coord[i]] * min(temp, dist[coord[i]][e]);
                            }
                            if (sum < least)
                            {
                                least = sum;
                                aa = a, bb = b, cc = c, dd = d, ee = e;
                            }
                        }
                        
        cout << aa << ' ' << bb << ' ' << cc << ' ' << dd << ' ' << ee << '\n';
    }
    
    return 0;
}
