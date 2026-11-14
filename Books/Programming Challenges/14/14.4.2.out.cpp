#include <bits/stdc++.h>

using namespace std;

const int MAXN = 110;
int grid[MAXN][MAXN];

int main(int argc, char *argv[])
{
    int n, cases = 0;
    while (cin >> n, n > 0)
    {
        memset(grid, 0, sizeof(grid));
        int x1, y1, x2, y2;
        for (int i = 0; i < n; i++)
        {
            cin >> x1 >> y1 >> x2 >> y2;
            for (int x = x1; x < x2; x++)
                for (int y = y1; y < y2; y++)
                    grid[x][y] = 1;
        }
        int area = 0;
        for (int x = 0; x < MAXN; x++)
            for (int y = 0; y < MAXN; y++)
                area += grid[x][y];
        cout << "Case " << ++cases << ": " << area << '\n';
    }
    return 0;
}
