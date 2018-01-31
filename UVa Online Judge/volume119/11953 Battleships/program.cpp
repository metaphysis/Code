// Battleships
// UVa ID: 11953
// Verdict: Accepted
// Submission Date: 2018-01-31
// UVa Run Time: 0.000s
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

int N, T1, T2, nexti, nextj;
int offset[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
char grid[110][110];

void dfs(int i, int j)
{
    if (grid[i][j] == 'x') T1++; else T2++;
    grid[i][j] = '.';
    for (int k = 0; k < 4; k++)
    {
        nexti = i + offset[k][0], nextj = j + offset[k][1];
        if (nexti >= 0 && nexti < N && nextj >= 0 && nextj < N)
            if (grid[nexti][nextj] == 'x' || grid[nexti][nextj] == '@')
                dfs(nexti, nextj);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> N;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                cin >> grid[i][j];

        int alived = 0;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (grid[i][j] == 'x' || grid[i][j] == '@')
                {
                    T1 = 0, T2 = 0;
                    dfs(i, j);
                    if (T1 > 0) alived++;
                }

        cout << "Case " << c << ": " << alived << '\n';
    }

    return 0;
}
