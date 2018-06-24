// Another n-Queen Problem
// UVa ID: 11195
// Verdict: Accepted
// Submission Date: 2018-06-24
// UVa Run Time: 0.380s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n, cnt, ONES, masks[16];

void dfs(int d, int L, int M, int R)
{
    int empty, cln;
    if (d < n) {
        empty = ONES & (~(L | M | R));
        while (empty) {
            cln = empty & (~empty + 1);
            empty ^= cln;
            if (masks[d] & cln) continue;
            dfs(d + 1, (L | cln) << 1, M | cln, (R | cln) >> 1);
        }
    }
    else cnt++;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    char piece;
    int cases = 0;
    int table[16] = {0, 1, 0, 0, 2, 10, 4, 40, 92, 352, 724, 2680, 14200, 73712, 365596, 2279184};

    while (cin >> n, n > 0)
    {
        memset(masks, 0, sizeof(masks));
        int bads = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                cin >> piece;
                if (piece == '*') masks[i] |= (1 << j), bads++;
            }
        cout << "Case " << ++cases << ": ";
        if (!bads) cout << table[n] << '\n';
        else
        {
            ONES = (1 << n) - 1, cnt = 0;
            dfs(0, 0, 0, 0);
            cout << cnt << '\n';
        }
    }

    return 0;
}
