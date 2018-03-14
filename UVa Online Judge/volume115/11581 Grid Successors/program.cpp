// Grid Successors
// UVa ID: 11581
// Verdict: Accepted
// Submission Date: 2018-01-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int grid[4][4], temp[4][4], exist[1024][4][4];
    int offset[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int cnt, cases;
    char digit;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        for (int i = 1; i <= 3; i++)
            for (int j = 1; j <= 3; j++)
            {
                cin >> digit;
                grid[i][j] = digit - '0';
            }
        cnt = 0;
        
        int firstIdx = -1;

        while (true)
        {
            for (int k = 0; k < cnt; k++)
            {
                bool same = true;
                for (int i = 1; i <= 3; i++)
                    for (int j = 1; j <= 3; j++)
                        if (exist[k][i][j] != grid[i][j])
                        {
                            same = false;
                            goto next;
                        }
                next:
                if (same)
                {
                    firstIdx = k - 1;
                    goto print;
                }
            }
            
            for (int i = 1; i <= 3; i++)
                for (int j = 1; j <= 3; j++)
                    exist[cnt][i][j] = grid[i][j];
            cnt++;
            
            memset(temp, 0, sizeof(temp));

            for (int i = 1; i <= 3; i++)
                for (int j = 1; j <= 3; j++)
                {
                    for (int k = 0; k < 4; k++)
                    {
                        int ii = i + offset[k][0], jj = j + offset[k][1];
                        if (ii >= 1 && ii <= 3 && jj >= 1 && jj <= 3)
                        {
                            temp[i][j] += grid[ii][jj];
                        }
                        temp[i][j] %= 2;
                    }
                }
            
            for (int i = 1; i <= 3; i++)
                for (int j = 1; j <= 3; j++)
                    grid[i][j] = temp[i][j];
                    
            //for (int i = 1; i <= 3; i++)
            //{
            //    for (int j = 1; j <= 3; j++)
            //        cout << setw(10) << right << grid[i][j];
            //    cout << '\n';
            //}
            //cout << '\n';
        }

        print:
        cout << firstIdx << '\n';
    }

    return 0;
}
