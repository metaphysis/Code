// Shark
// UVa ID: 830
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

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

char grid[70][70];
int L, C;
int leftC, rightC, topL, bottomL, area;
int offset[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void floodFill(int i, int j, char oldChar, char newChar)
{
    if (grid[i][j] == oldChar)
    {
        area++;
        grid[i][j] = newChar;
        leftC = min(leftC, j), rightC = max(rightC, j), topL = min(topL, i), bottomL = max(bottomL, i);
        for (int k = 0; k < 4; k++)
        {
            int ii = i + offset[k][0], jj = j + offset[k][1];
            if (ii >= 1 && ii <= L && jj >= 1 && jj <= C)
                floodFill(ii, jj, oldChar, newChar);
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases; cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> L >> C;
        
        //cin.ignore(1024, '\n');
        //string line;

        for (int i = 1; i <= L; i++)
        {
            //getline(cin, line);
            //for (int j = 1; j <= C; j++)
            //    grid[i][j] = line[j - 1];
                
            for (int j = 1; j <= C; j++)
                cin >> grid[i][j];
            cin.ignore(1024, '\n');
        }

        int sardines = 0, mackerels = 0, salmons = 0, groupers = 0, turtles = 0, dolphines = 0, whales = 0, sharks = 0;
        for (int i = 1; i <= L; i++)
            for (int j = 1; j <= C; j++)
                if (grid[i][j] != '.')
                {
                    leftC = C, rightC = 1, topL = L, bottomL = 1, area = 0;
                    floodFill(i, j, grid[i][j], '.');
                    int width = abs(topL - bottomL) + 1, height = abs(leftC - rightC) + 1;
                    if (area != width * height) sharks++;
                    else
                    {
                        if (width > height) swap(width, height);
                        if (width == 1 && height == 1) { sardines++; continue; }
                        if (width == 1 && height == 2) { mackerels++; continue; }
                        if (width == 1 && height > 2) { salmons++; continue; }
                        if (width == height && width >= 2) { turtles++; continue; }
                        if (width == 2 && height > 2) { groupers++; continue; }
                        if (width == 3 && height > 3) { dolphines++; continue; }
                        if (width == 4 && height > 4) { whales++; continue; }
                    }
                }
        if (c > 1) cout << '\n';
        cout << sardines << ' ' << mackerels << ' ' << salmons << ' ' << groupers << ' ' << turtles << ' ' << dolphines << ' ' << whales << ' ' << sharks << '\n';
    }

    return 0;
}
