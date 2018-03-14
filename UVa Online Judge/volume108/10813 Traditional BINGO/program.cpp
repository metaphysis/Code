// Traditional BINGO
// UVa ID: 10813
// Verdict: Accepted
// Submission Date: 2017-12-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int bingo[10][10], flag[80], cnt[20], mark[80][10];
    int cases;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        memset(bingo, 0, sizeof(bingo));
        memset(mark, 0, sizeof(mark));

        for (int i = 1; i <= 5; i++)
        {
            int clns = 5;
            if (i == 3) clns = 4;
            for (int j = 1; j <= clns; j++)
            {
                cin >> bingo[i][j];
            }
            if (i == 3)
            {
                swap(bingo[i][5], bingo[i][4]);
                swap(bingo[i][4], bingo[i][3]);
            }
            for (int j = 1; j <= 5; j++)
            {
                if (bingo[i][j])
                {
                    mark[bingo[i][j]][1] = i;
                    mark[bingo[i][j]][2] = j + 5;
                    if (abs(i - 3) == abs(j - 3))
                    {
                        if (i < 3 && j < 3) mark[bingo[i][j]][3] = 11;
                        if (i > 3 && j > 3) mark[bingo[i][j]][3] = 11;
                        if (i < 3 && j > 3) mark[bingo[i][j]][3] = 12;
                        if (i > 3 && j < 3) mark[bingo[i][j]][3] = 12;
                    }
                }
            }
        }

        memset(flag, 0, sizeof(flag));
        memset(cnt, 0, sizeof(cnt));

        cnt[3] = cnt[8] = cnt[11] = cnt[12] = 1;

        int ball, outputed = 0;
        for (int i = 1; i <= 75; i++)
        {
            cin >> ball;

            if (outputed) continue;
            if (flag[ball]) continue; flag[ball] = 1;
            if (!mark[ball][1]) continue;

            cnt[mark[ball][1]]++;
            if (cnt[mark[ball][1]] == 5)
            {
                cout << "BINGO after " << i << " numbers announced\n";
                outputed = 1;
                continue;
            }
            cnt[mark[ball][2]]++;
            if (cnt[mark[ball][2]] == 5)
            {
                cout << "BINGO after " << i << " numbers announced\n";
                outputed = 1;
                continue;
            }
            cnt[mark[ball][3]]++;
            if (mark[ball][3] && cnt[mark[ball][3]] == 5)
            {
                cout << "BINGO after " << i << " numbers announced\n";
                outputed = 1;
                continue;
            }
        }
    }

    return 0;
}
