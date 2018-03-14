// Little Red Riding Hood
// UVa ID: 11067
// Verdict: Accepted
// Submission Date: 2018-02-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long cnt[110][110];
    int w, h, n;

    while (cin >> w >> h, w > 0)
    {
        cin >> n;
        memset(cnt, -1, sizeof(cnt));
        for (int i = 1, x, y; i <= n; i++)
        {
            cin >> x >> y;
            cnt[y][x] = 0;
        }
        cnt[0][0] = 1;
        for (int i = 0; i <= h; i++)
            for (int j = 0; j <= w; j++)
                if (cnt[i][j] < 0)
                {
                    cnt[i][j] = 0;
                    if (i - 1 >= 0) cnt[i][j] += cnt[i - 1][j];
                    if (j - 1 >= 0) cnt[i][j] += cnt[i][j - 1];
                }
        if (cnt[h][w] == 0) cout << "There is no path.\n";
        else
        {
            cout << "There ";
            if (cnt[h][w] == 1) cout << "is one path";
            else cout << "are " << cnt[h][w] << " paths";
            cout << " from Little Red Riding Hood's house to her grandmother's house.\n";
        }
    }

    return 0;
}
