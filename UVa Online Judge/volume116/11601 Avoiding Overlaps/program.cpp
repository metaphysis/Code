// Avoiding Overlaps
// UVa ID: 11601
// Verdict: Accepted
// Submission Date: 2018-12-21
// UVa Run Time: 0.260s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point
{
    int x, y;
    point (int x = 0, int y = 0): x(x), y(y) {}
};

struct rectangle
{
    point lowLeft, upRight;
};

int grid[256][256], OFFSET = 100;

bool isOverlapped(rectangle r)
{
    for (int i = r.lowLeft.x; i <= r.upRight.x - 1; i++)
        for (int j = r.lowLeft.y; j <= r.upRight.y - 1; j++)
            if (grid[i][j])
                return true;
    for (int i = r.lowLeft.x; i <= r.upRight.x - 1; i++)
        for (int j = r.lowLeft.y; j <= r.upRight.y - 1; j++)
            grid[i][j] = 1;
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int T, N;
    cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        cin >> N;
        memset(grid, 0, sizeof(grid));
        int area = 0;
        rectangle r;
        for (int i = 0; i < N; i++)
        {
            cin >> r.lowLeft.x >> r.lowLeft.y;
            cin >> r.upRight.x >> r.upRight.y;
            r.lowLeft.x += OFFSET, r.lowLeft.y += OFFSET;
            r.upRight.x += OFFSET, r.upRight.y += OFFSET;
            if (!isOverlapped(r))
                area += abs(r.lowLeft.x - r.upRight.x) * abs(r.lowLeft.y - r.upRight.y);
        }
        cout << "Case " << cs << ": " << area << '\n';
    }

    return 0;
}
