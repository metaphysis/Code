// Milk Bottle Data
// UVa ID: 525
// Verdict: Accepted
// Submission Date: 2017-05-14
// UVa Run Time: 0.220s
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

char rows[20][20];
int used[20], R, N, chosen[20];

bool backtrack(int depth)
{
    if (depth >= R) return true;
    
    for (int i = 0; i < R; i++)
        if (!used[i])
        {
            // prune, cross check.
            bool matched = true;
            int start = (depth % 2 == 0 ? 1 : 0), column = depth / 2;
            for (int j = start, k = 0; j < depth; j += 2, k++)
            {
                if (rows[chosen[j]][column] == '2') continue;
                if (rows[i][k] == '2') continue;
                if (rows[chosen[j]][column] == rows[i][k]) continue;
                matched = false;
                break;
            }

            if (!matched) continue;

            used[i] = 1;
            chosen[depth] = i;

            if (backtrack(depth + 1)) return true;

            used[i] = 0;
        }
        
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    string row;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';

        cin >> row;
        for (int i = 0; i < row.length(); i++)
            rows[0][i] = row[i];
        
        N = row.length(), R = 2 * N;

        for (int i = 1; i < R; i++)
        {
            cin >> row;
            for (int j = 0; j < row.length(); j++)
                rows[i][j] = row[j];
        }
        
        memset(used, 0, sizeof(used));

        bool exist = backtrack(0);
        
        if (exist)
        {
            char grid[20][20];

            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                    grid[i][j] = rows[chosen[2 * i]][j];

            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                {
                    if (grid[j][i] == '2')
                        grid[j][i] = rows[chosen[2 * i + 1]][j];
                    if (grid[j][i] == '2')
                        grid[j][i] = '0';
                }

            cout << "     ";
            for (int i = 0; i < N - 1; i++)
                cout << setw(3) << left << (chosen[2 * i + 1] + 1);
            cout << chosen[2 * (N - 1) + 1] + 1 << '\n';
            cout << '\n';

            for (int i = 0; i < N; i++)
            {
                cout << setw(3) << left << (chosen[2 * i] + 1);
                for (int j = 0; j < N; j++)
                    cout << setw(3) << right << grid[i][j];
                cout << '\n';
            }
        }
        else
        {
            cout << "impossible\n";
        }
    }
    
    return 0;
}
