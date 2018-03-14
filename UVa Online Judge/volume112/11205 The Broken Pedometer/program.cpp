// The Broken Pedometer
// UVa ID: 11205
// Verdict: Accepted
// Submission Date: 2017-11-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int P, N;
int mask, symbol, code[110], used[1 << 15], ones[1 << 15];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    memset(ones, 0, sizeof(ones));
    for (int i = 0; i < (1 << 15); i++)
    {
        int t = i;
        for (int j = 0; j < 15; j++)
        {
            if (t & 1) ones[i]++;
            t >>= 1;
        }
    }
    
    int cases;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> P >> N;
        
        for (int i = 0; i < N; i++)
        {
            int bits = 0;
            for (int j = 0; j < P; j++)
            {
                cin >> symbol;
                bits = bits * 2 + symbol;
            }
            code[i] = bits;
        }

        int most = 1 << P, least = P;

        memset(used, -1, most * sizeof(int));

        for (int bar = 0; bar < most; bar++)
        {
            if (ones[bar] >= least) continue;
            
            bool diff = true;
            for (int j = 0; j < N; j++)
            {
                if (used[code[j] & bar] == bar)
                {
                    diff = false;
                    break;
                }
                used[code[j] & bar] = bar;
            }

            if (diff) least = min(least, ones[bar]);
        }
        cout << least << '\n';
    }

    return 0;
}
