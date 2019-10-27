// Cube
// UVa ID: 10601
// Verdict: Accepted
// Submission Date: 2019-10-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int Cnk[16][16] = {0}, rods1[6], rods2[6];

long long work(int k)
{
    int x = 0;
    for (int i = 0; i < 6; i++) {
        if (rods2[i] % k) return 0;
        rods2[i] /= k;
        x += rods2[i];
    }

    long long r = 1;
    for (int i = 0; i < 6; i++) {
        r *= Cnk[x][rods2[i]];
        x -= rods2[i];
    }

    return r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    for (int i = 0; i <= 12; i++) {
        Cnk[i][0] = Cnk[i][i] = 1;
        for (int j = 1; j < i; j++)
            Cnk[i][j] = Cnk[i - 1][j] + Cnk[i - 1][j - 1];
    }

    int cases = 0;
    cin >> cases;

    for (int cs = 1; cs <= cases; cs++) {
        memset(rods1, 0, sizeof(rods1));
        for (int i = 0, color; i < 12; i++) {
            cin >> color;
            rods1[--color]++;
        }
        
        long long r = 0;

        memcpy(rods2, rods1, sizeof(rods1));
        r += work(1);

        memcpy(rods2, rods1, sizeof(rods1));
        r += 3 * 2 * work(4);

        memcpy(rods2, rods1, sizeof(rods1));
        r += 3 * work(2);

        memcpy(rods2, rods1, sizeof(rods1));
        r += 4 * 2 * work(3);

        for (int i = 0; i < 6; i++)
            for (int j = 0; j < 6; j++) {
                memcpy(rods2, rods1, sizeof(rods1));
                rods2[i]--, rods2[j]--;
                if (rods2[i] < 0 || rods2[j] < 0) continue;
                r += 6 * work(2);
            }

        cout << r / 24 << '\n';
    }

    return 0;
}
