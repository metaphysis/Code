// Bangladesh Sequences
// UVa ID: 10513
// Verdict: TLE
// Submission Date: 2018-08-19
// UVa Run Time: 3.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n, cnt, bits[20], mask;

void dfs(int D, int L, int M, int R)
{
    int available, cln;
    if (D != n) {
        available = mask & bits[D] & (~(L | M | R));
        while (available) {
            cln = available & (~available + 1);
            available ^= cln;
            // rule c, d
            int b1 = bits[D + 1], b2 = bits[D + 2];
            bits[D + 1] &= ~((cln << 2) | (cln >> 2));
            bits[D + 2] &= ~((cln << 1) | (cln >> 1));
            // rule a, b
            dfs(D + 1, (L | cln) << 1, M | cln, (R | cln) >> 1);
            bits[D + 1] = b1, bits[D + 2] = b2;
        }
    }
    else cnt++;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    string parts[16];

    while (cin >> n, n > 0)
    {
        long long total = 1;
        memset(bits, 0, sizeof(bits));
        for (int i = 0; i < n; i++)
        {
            cin >> parts[i];
            if (parts[i] == "?")
            {
                parts[i].clear();
                for (int j = 0; j < n; j++)
                    parts[i] += (char)('A' + j);
            }
            total *= parts[i].length();
            for (int j = 0; j < parts[i].length(); j++)
                bits[i] |= (1 << (parts[i][j] - 'A'));
        }
        mask = (1 << n) - 1;
        dfs(cnt = 0, 0, 0, 0);
        cout << "Case " << ++cases << ": " << (total - cnt) << '\n';
    }

    return 0;
}
