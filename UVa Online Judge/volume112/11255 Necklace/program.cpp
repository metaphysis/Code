// Necklace
// UVa ID: 11255
// Verdict: Accepted
// Submission Date: 2019-10-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

long long Cnk[41][41];
int pearls1[3], pearls2[3];

long long work(int k)
{
    int x = 0;
    for (int i = 0; i < 3; i++)
    {
        if (pearls2[i] % k) return 0;
        pearls2[i] /= k;
        x += pearls2[i];
    }
    long long r = 1;
    for (int i = 0; i < 3; i++)
    {
        r *= Cnk[x][pearls2[i]];
        x -= pearls2[i];
    }
    return r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    for (int i = 0; i <= 40; i++)
    {
        Cnk[i][0] = Cnk[i][i] = 1;
        for (int j = 1; j < i; j++)
            Cnk[i][j] = Cnk[i - 1][j] + Cnk[i - 1][j - 1];
    }

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        int n = 0;
        for (int i = 0; i < 3; i++) { cin >> pearls1[i]; n += pearls1[i]; }
        long long r = 0;
        for (int i = 0; i < n; i++)
        {
            memcpy(pearls2, pearls1, sizeof(pearls1));
            r += work(n / __gcd(n, i));
        }
        
        if (n % 2)
        {
            for (int i = 0; i < 3; i++)
            {
                memcpy(pearls2, pearls1, sizeof(pearls1));
                pearls2[i]--;
                if (pearls2[i] < 0) continue;
                r += n * work(2);
            }
        }
        else
        {
            memcpy(pearls2, pearls1, sizeof(pearls1));
            r += (n / 2) * work(2);
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                {
                    memcpy(pearls2, pearls1, sizeof(pearls1));
                    pearls2[i]--, pearls2[j]--;
                    if (pearls2[i] < 0 || pearls2[j] < 0) continue;
                    r += (n / 2) * work(2);
                }
        }

        cout << (r / (2 * n)) << '\n';
    }

    return 0;
}
