// DNA Consensus String
// UVa ID: 1368
// Verdict: Accepted
// Submission Date: 2018-04-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, m, n, cnt[4][1024];;
    string dna, codes = "ACGT";

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> m >> n;
        
        memset(cnt, 0, sizeof(cnt));
        for (int i = 1; i <= m; i++)
        {
            cin >> dna;
            for (int j = 0; j < n; j++)
            {
                if (dna[j] == 'A') cnt[0][j]++;
                if (dna[j] == 'C') cnt[1][j]++;
                if (dna[j] == 'G') cnt[2][j]++;
                if (dna[j] == 'T') cnt[3][j]++;
            }
        }
        
        int total = 0;
        for (int i = 0; i < n; i++)
        {
            int smallest = 0x3f3f3f3f, idx = -1;
            for (int j = 0; j < 4; j++)
            {
                int t = 0;
                for (int k = 0; k < 4; k++)
                    if (k != j)
                        t += cnt[k][i];

                if (smallest > t)
                {
                    smallest = t;
                    idx = j;
                }
            }
            total += smallest;
            cout << codes[idx];
        }
        cout << '\n';
        cout << total << '\n';
    }

    return 0;
}
