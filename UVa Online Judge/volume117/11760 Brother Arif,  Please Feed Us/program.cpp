// Brother Arif, Please Feed Us
// UVa ID: 11760
// Verdict: Accepted
// Submission Date: 2018-01-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int row[10010], cln[10010], R, C, N, xi, yi, bxi, byi;
    int offset[5][2] = {{0, 0}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int cases = 0;

    while (cin >> R >> C >> N, R > 0)
    {
        memset(row, 0, sizeof(row));
        memset(cln, 0, sizeof(cln));
        
        for (int i = 1; i <= N; i++)
        {
            cin >> xi >> yi;
            row[xi] = cln[yi] = 1;
        }
        
        cin >> bxi >> byi;
        
        bool safe = false;
        for (int i = 0; i < 5; i++)
        {
            int nexti = bxi + offset[i][0], nextj = byi + offset[i][1];
            if (nexti >= 0 && nexti < R && nextj >= 0 && nextj < C)
            {
                if (!row[nexti] && !cln[nextj])
                {
                    safe = true;
                    break;
                }
            }
        }
        cout << "Case " << ++cases << ": ";
        if (safe) cout << "Escaped again! More 2D grid problems!\n";
        else cout << "Party time! Let's find a restaurant!\n";
        
    }
    return 0;
}
