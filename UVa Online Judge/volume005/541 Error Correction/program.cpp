// Error Correction
// UVa ID: 541
// Verdict: Accepted
// Submission Date: 2016-08-07
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

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n, grid[110][110];

    while (cin >> n, n)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> grid[i][j];
        
        int row, column, row_odd_number = 0, column_odd_number = 0;
        for (int i = 0; i < n; i++)
        {
            int row_sum = 0, column_sum = 0;
            for (int j = 0; j < n; j++)
                row_sum += grid[i][j], column_sum += grid[j][i];

            if (row_sum % 2 == 1)
            {
                row_odd_number++;
                row = i;
            }
            
            if (column_sum % 2 == 1)
            {
                column_odd_number++;
                column = i;
            }
        }
        
        if (row_odd_number == 0 && column_odd_number == 0)
            cout << "OK\n";
        else if (row_odd_number == 1 && column_odd_number == 1)
            cout << "Change bit (" << (row + 1) << "," << (column + 1) << ")\n";
        else
            cout << "Corrupt\n";
    }
    
	return 0;
}
