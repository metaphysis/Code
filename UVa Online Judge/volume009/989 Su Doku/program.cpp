// Su Doku
// UVa ID: 989
// Verdict: Accepted
// Submission Date: 2017-03-08
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

const int MAXN = 10;

int n, board[MAXN][MAXN];
int squareUsed[MAXN][MAXN], rowUsed[MAXN][MAXN], columnUsed[MAXN][MAXN];
bool finished = false;

void dfs(int i, int j)
{
    if (i == n * n)
    {
        finished = true;
        return;
    }
    
    if (board[i][j] > 0)
    {
        if (j + 1 == n * n) dfs(i + 1, 0);
        else dfs(i, j + 1);
    }
    else
    {
        for (int c = 1; c <= n * n; c++)
        {
            if (!rowUsed[i][c] && !columnUsed[j][c] && !squareUsed[i / n * n + j / n][c])
            {
                rowUsed[i][c] = 1, columnUsed[j][c] = 1;
                squareUsed[i / n * n + j / n][c] = 1;
                board[i][j] = c;
                
                if (j + 1 == n * n) dfs(i + 1, 0);
                else dfs(i, j + 1);
                
                if (finished) return;
                
                rowUsed[i][c] = 0, columnUsed[j][c] = 0;
                squareUsed[i / n * n + j / n][c] = 0;
                board[i][j] = 0;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> n)
    {
        memset(rowUsed, 0, sizeof(rowUsed));
        memset(columnUsed, 0, sizeof(columnUsed));
        memset(squareUsed, 0, sizeof(squareUsed));
        
        for (int i = 0; i < n * n; i++)
            for (int j = 0; j < n * n; j++)
            {
                cin >> board[i][j];
                rowUsed[i][board[i][j]] = 1;
                columnUsed[j][board[i][j]] = 1;
                squareUsed[i / n * n + j / n][board[i][j]] = 1;
            }
        
        if (cases++ > 0) cout << '\n';
        
        finished = false;
        dfs(0, 0);
        
        if (!finished) cout << "NO SOLUTION\n";
        else
        {
            for (int i = 0; i < n * n; i++)
            {
                for (int j = 0; j < n * n; j++)
                {
                    if (j > 0) cout << ' ';
                    cout << board[i][j];
                }
                cout << '\n';
            }
        }
    }
    
    return 0;
}
