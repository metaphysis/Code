// Mine Sweeper
// UVa ID: 10279
// Verdict: Accepted
// Submission Date: 2017-12-24
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
    char board1[20][20], board2[20][20];
    int n;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';

        cin >> n;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> board1[i][j];
                
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> board2[i][j];
                
        int flag = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                if (board2[i][j] == 'x' && board1[i][j] == '*')
                {
                    flag = 1;
                    goto print;
                }
            }
            
        print:
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (board2[i][j] == 'x')
                {
                    if (board1[i][j] == '*') cout << '*';
                    else
                    {
                        int count = 0;
                        for (int ii = -1; ii <= 1; ii++)
                            for (int jj = -1; jj <= 1; jj++)
                            {
                                int nexti = i + ii, nextj = j + jj;
                                if (nexti >= 0 && nexti < n && nextj >= 0 && nextj < n)
                                {
                                    if (board1[nexti][nextj] == '*')
                                        count++;
                                }
                            }
                        cout << count;
                    }
                }
                else
                {
                    if (flag && board1[i][j] == '*') cout << '*';
                    else cout << '.';
                }
            }
            cout << '\n';
        }
    }
    
    return 0;
}
