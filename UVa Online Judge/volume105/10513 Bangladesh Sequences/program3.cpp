// Bangladesh Sequences
// UVa ID: 10513
// Verdict: Accepted
// Submission Date: 2018-08-19
// UVa Run Time: 0.120s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

char sq[16];
int n, cnt[16], mask, bits[20];
string trick[16][33000];

void dfs(int D, int L, int M, int R)
{
    int available, cln;
    if (D != n) {
        available = mask & bits[D] & (~(L | M | R));
        while (available) {
            cln = available & (~available + 1);
            sq[D] = (char)('A' + __builtin_ctz(cln));
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
    else 
    {
        for (int i = 0; i < n; i++)
            trick[n][cnt[n]] += sq[i];
        cnt[n]++;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    for (int i = 1; i <= 15; i++)
    {
        memset(bits, 0, sizeof(bits));
        for (int j = 0; j < i; j++)
            bits[j] = (1 << i) - 1;
        mask = (1 << i) - 1;
        dfs(cnt[n = i] = 0, 0, 0, 0);
    }

    string parts[16];
    int cases = 0, available[16][256];
    while (cin >> n, n > 0)
    {
        memset(available, 0, sizeof(available));
        long long total = 1;
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
                available[i][parts[i][j]] = 1;
        }
        
        long long invalid = 0;
        for (int i = 0; i < cnt[n]; i++)
        {
            bool matched = true;
            for (int j = 0; j < n; j++)
            {
                if (!available[j][trick[n][i][j]])
                {
                    matched = false;
                    break;
                }
            }
            if (matched) invalid++;
        }

        cout << "Case " << ++cases << ": " << (total - invalid) << '\n';
    }

    return 0;
}
