// The die is cast
// UVa ID: 657
// Verdict: Accepted
// Submission Date: 2016-08-27
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
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

char grid[60][60];
int w, h;

void label(int i, int j)
{
    if (i >= 0 && i < h && j >= 0 && j < w)
    {
        if (grid[i][j] == '*' || grid[i][j] == 'X')
        {
            if (grid[i][j] == '*')
                grid[i][j] = '.';
            else
                grid[i][j] = '1';
                
            label(i + 1, j);
            label(i - 1, j);
            label(i, j + 1);
            label(i, j - 1);
        }
    }
}

void cover(int i, int j)
{
    if (i >= 0 && i < h && j >= 0 && j < w && grid[i][j] == '1')
    {
        grid[i][j] = '.';
        cover(i + 1, j);
        cover(i - 1, j);
        cover(i, j + 1);
        cover(i, j - 1);
    }
}

void flip(int i, int j)
{
    if (i >= 0 && i < h && j >= 0 && j < w && grid[i][j] == 'X')
    {
        grid[i][j] = '.';
        flip(i + 1, j);
        flip(i - 1, j);
        flip(i, j + 1);
        flip(i, j - 1);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int throws = 0;
    while (cin >> w >> h, w)
    {
        for (int i = 0; i < h; i++)
            for (int j = 0; j < w; j++)
                cin >> grid[i][j];
        
        vector<int> dices;
        for (int i = 0; i < h; i++)
            for (int j = 0; j < w; j++)
                if (grid[i][j] == '*')
                {
                    label(i, j);
                    
                    int dice = 0;
                    for (int x = 0; x < h; x++)
                        for (int y = 0; y < w; y++)
                            if (grid[x][y] == '1')
                            {
                                dice++;
                                cover(x, y);
                            }
                            
                    dices.push_back(dice);
                                
                }
        
        for (int i = 0; i < h; i++)
            for (int j = 0; j < w; j++)
                if (grid[i][j] == 'X')
                {
                    dices.push_back(1);
                    flip(i, j);
                }
                
        sort(dices.begin(), dices.end());
        
        cout << "Throw " << ++throws << '\n';
        
        for (int i = 0; i < dices.size(); i++)
        {
            if (i > 0)
                cout << ' ';
            cout << dices[i];
        }
        cout << "\n\n";
                
    }
    
	return 0;
}
