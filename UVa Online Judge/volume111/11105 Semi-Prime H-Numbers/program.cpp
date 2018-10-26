// Semi-Prime H-Numbers
// UVa ID: 11105
// Verdict: Accepted
// Submission Date: 2018-10-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000001;

int H[MAXN + 1] = {0, 1}, P[MAXN >> 3], C = 0;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    for (int i = 1; i <= 1000001; i += 4)
    {
        if (!H[i]) P[C++] = i;
        for (int j = 0; j < C && i * P[j] <= MAXN; j++)
        {
            H[i * P[j]] = 1;
            if (!(i % P[j])) break;
        }
    }
    memset(H, 0, sizeof(H));
    for (int i = 0; i < C; i++)
        for (int j = 0; j <= i && P[i] * P[j] <= MAXN; j++)
            H[P[i] * P[j]] = 1;
    for (int i = 0; i <= MAXN; i++)
        H[i] += H[i - 1];
    
    int h;
    while (cin >> h, h) cout << h << ' ' << H[h] << '\n';

    return 0;
}
