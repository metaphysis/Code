// Matty's Blocks
// UVa ID: 434
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

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0;
    cin >> cases;

    for (int i = 1; i <= cases; i++)
    {
        int row;
        cin >> row;

        vector<int> front_view(row), right_view(row);
        vector<vector<int>> matrix(row, vector<int>());
        
        for (int j = 0; j < row; j++)
            cin >> front_view[j];
        for (int j = 0; j < row; j++)
            cin >> right_view[j];

        reverse(right_view.begin(), right_view.end());
  
        int max_blocks = 0;
        for (int j = 0; j < row; j++)
            for (int k = 0; k < row; k++)
            {
                max_blocks += min(right_view[j], front_view[k]);
                matrix[j].push_back(min(right_view[j], front_view[k]));
            }

        for (int j = 0; j < row; j++)
        {
            for (int k = 0; k < row; k++)
                cout << setw(3) << matrix[j][k];
            cout << endl;
        }

        for (int j = 0; j < row; j++)
            for (int k = 0; k < row; k++)
            {
                while (matrix[j][k] > 0)
                {
                    matrix[j][k]--;
                    
                    bool same = true;
                    for (int x = 0; x < row; x++)
                    {
                        int max_blocks_row = 0, max_blocks_column = 0;
                        for (int y = 0; y < row; y++)
                        {
                            max_blocks_row = max(max_blocks_row, matrix[x][y]);
                            max_blocks_column = max(max_blocks_column, matrix[y][x]);
                        }
                            
                        if (max_blocks_row < right_view[x] || max_blocks_column < front_view[x])
                        {
                            same = false;
                            break;
                        }
                    }
                            
                    if (!same)
                    {
                        matrix[j][k]++;
                        break;
                    }
                }
            }
        
        int min_blocks = 0;
        for (int j = 0; j < row; j++)
            for (int k = 0; k < row; k++)
                min_blocks += matrix[j][k];
                    
        cout << "Matty needs at least " << min_blocks;
        cout << " blocks, and can add at most ";
        cout << (max_blocks - min_blocks) << " extra blocks.\n";
    }
    
	return 0;
}
