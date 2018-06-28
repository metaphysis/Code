// So Doku Checker
// UVa ID: 10957
// Verdict: Accepted
// Submission Date: 2018-06-28
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int grid[9][9], row[9], cln[9], sub[9], cnt = 0, NINE_ONES = (1 << 9) - 1;

void dfs(int i, int j)
{
    if (cnt > 1) return;
    if (j == 9)
    {
        dfs(i + 1, 0);
        return;
    }
    if (grid[i][j])
    {
        dfs(i, j + 1);
        return;
    }
    if (i == 9) cnt++;
    else
    {
        int available, next, k = (i / 3) * 3 + j / 3;
        available = NINE_ONES & (~(row[i] | cln[j] | sub[k]));
        while (available)
        {
            next = available & (~available + 1);
            available ^= next;
            row[i] ^= next, cln[j] ^= next, sub[k] ^= next;
            dfs(i, j + 1);
            row[i] ^= next, cln[j] ^= next, sub[k] ^= next;
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, cases = 0;
    while (cin >> n)
    {
        cout << "Case " << ++cases << ": ";

        bool bad = false;
    
        memset(grid, 0, sizeof(grid));
        memset(row, 0, sizeof(row));
        memset(cln, 0, sizeof(cln));
        memset(sub, 0, sizeof(sub));

        grid[0][0] = n;
        if (n > 0)
        {
            n--;
            row[0] |= (1 << n);
            cln[0] |= (1 << n);
            sub[0] |= (1 << n);
        }

        for (int j = 1; j < 9; j++)
        {
            cin >> n;
            grid[0][j] = n;
            if (n == 0) continue;
            n--;
            if ((row[0] | cln[j] | sub[j / 3]) & (1 << n)) bad = true;
            row[0] |= (1 << n);
            cln[j] |= (1 << n);
            sub[j / 3] |= (1 << n);
        }
        for (int i = 1; i < 9; i++)
            for (int j = 0; j < 9; j++)
            {
                cin >> n;
                grid[i][j] = n;
                if (n == 0) continue;
                n--;
                if ((row[i] | cln[j] | sub[(i / 3) * 3 + j / 3]) & (1 << n)) bad = true;
                row[i] |= (1 << n);
                cln[j] |= (1 << n);
                sub[(i / 3) * 3 + j / 3] |= (1 << n);
            }
        if (bad)
        {
            cout << "Illegal.\n";
            continue;
        }
        cnt = 0;
        dfs(0, 0);
        if (cnt == 0) cout << "Impossible.\n";
        if (cnt == 1) cout << "Unique.\n";
        if (cnt == 2) cout << "Ambiguous.\n";
    }

    return 0;
}
