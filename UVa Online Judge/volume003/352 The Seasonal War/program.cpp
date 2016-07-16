// The Seasonal War 
// UVa ID: 352
// Verdict: Accepted
// Submission Date: 2016-06-25
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
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

char matrix[30][30];
int n;
    
void floodFill(int i, int j)
{
    if (i < 1 || i > n || j < 1 || j > n)
        return;
    
    if (matrix[i][j] == '1')
    {
        matrix[i][j] = '0';
    
        for (int m = -1; m <= 1; m++)
            for (int n = -1; n <= 1; n++)
                floodFill(i + m, j + n);
    }
}

int main(int argc, char *argv[])
{
    int cases = 0;
    while (cin >> n)
    {
        memset(matrix, 0, sizeof(matrix));
        
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                cin >> matrix[i][j];
        
        int eagles = 0;
        bool updated = false;
        do
        {
            updated = false;
            
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    if (matrix[i][j] == '1')
                    {
                        floodFill(i, j);
                        updated = true;
                        eagles++;
                    }
                        
        } while (updated);
        
        cout << "Image number " << ++cases << " contains " << eagles << " war eagles." << endl;
    }
    
	return 0;
}
