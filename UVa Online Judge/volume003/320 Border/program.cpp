// Border
// UVa IDs: 320
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
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    char bitmap[40][40];
    int cases;
    
    cin >> cases;
    for (int i = 1; i <= cases; i++)
    {
        for (int m = 1; m <= 32; m++)
            for (int n = 1; n <= 32; n++)
                bitmap[m][n] = '.';
                
        cout << "Bitmap #" << i << endl;
        
        int x, y;
        cin >> x >> y;
        
        string path;
        cin >> path;
        
        for (int j = 0; j < path.length() - 1; j++)
        {
            if (path[j] == 'E')
            {
                x += 1;
                bitmap[x][y] = 'X';
            }
            else if (path[j] == 'N')
            {
                y += 1;
                bitmap[x + 1][y] = 'X';
            }
            else if (path[j] == 'W')
            {
                x -= 1;
                bitmap[x + 1][y + 1] = 'X';
            }
            else if (path[j] == 'S')
            {
                y -= 1;
                bitmap[x][y + 1] = 'X';
            }
        }
        
        for (int m = 32; m >= 1; m--)
        {
            for (int n = 1; n <= 32; n++)
                cout << bitmap[n][m];
            cout << endl;
        }
        
        cout << endl;
    }
    
	return 0;
}
