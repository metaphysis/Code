// Don't Get Rooked
// UVa ID: 639
// Verdict: Accepted
// Submission Date: 2016-08-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

char grid[20], backup[20];
int n, max_rooks;

bool floodFill(int position)
{
    int i = position / n, j = position % n;
    for (int next_i = i + 1; next_i < n; next_i++)
        if (backup[next_i * n + j] == 'r')
            return false;
        else if (backup[next_i * n + j] == 'X')
            break;
    for (int next_i = i - 1; next_i >= 0; next_i--)
        if (backup[next_i * n + j] == 'r')
            return false;
        else if (backup[next_i * n + j] == 'X')
            break;
    for (int next_j = j + 1; next_j < n; next_j++)
        if (backup[i * n + next_j] == 'r')
            return false;
        else if (backup[i * n + next_j] == 'X')
            break;
    for (int next_j = j - 1; next_j >= 0; next_j--)
        if (backup[i * n + next_j] == 'r')
            return false;
        else if (backup[i * n + next_j] == 'X')
            break;
            
    return true;
}

bool check()
{
    copy(grid, grid + 20, backup);
    for (int i = 0; i < n * n; i++)
        if (backup[i] == 'r' && !floodFill(i))
            return false;
   return true;
}

void backtrack(int position, int rooks)
{
    max_rooks = max(max_rooks, rooks);

    for (int i = position; i < n * n; i++)
    {
        if (grid[i] == '.')
        {
            grid[i] = 'r';
            if (check())
                backtrack(position + 1, rooks + 1);
            grid[i] = '.';   
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    while (cin >> n, n)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> grid[i * n + j];
        max_rooks = 0;
        backtrack(0, 0);
        cout << max_rooks << '\n';
    }
    
	return 0;
}
