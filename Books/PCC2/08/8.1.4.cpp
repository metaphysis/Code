#include <bits/stdc++.h>

using namespace std;

const int MAXN = 32;

void nQueen(int *clnAtRow, int n)
{
    if (n % 6 != 2 && n % 6 != 3)
    {
        int row = 0;
        for (int y = 2; y <= n; y += 2) clnAtRow[row++] = y - 1;
        for (int y = 1; y <= n; y += 2) clnAtRow[row++] = y - 1;
    }
    else
    {
        int k = n / 2;
        int intervals[2][4][2] = {
            {{k, n}, {2, k - 2}, {k + 3,  n - 1}, {1, k + 1}},
            {{k, n - 1}, {1, k - 2}, {k + 3, n}, {2, k + 1}}
        };
        int row = 0;
        for (int x = 0; x < 4; x++)
        {
            int start = intervals[k % 2][x][0], end = intervals[k % 2][x][1];
            for (int y = start; y <= end; y += 2)
                clnAtRow[row++] = y - 1;
        }
        if (n % 2) clnAtRow[row++] = n - 1;
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int n = 15;
    int *clnAtRow = new int[n];
    nQueen(clnAtRow, n);
    cout << " n = " << n << '\n';
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j == clnAtRow[i]) cout << " Q";
            else cout << " *";
        }
        cout << '\n';
    }
    return 0;
}
