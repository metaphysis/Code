// Self-Describing Sequence
// UVa ID: 10049
// Verdict: Accepted
// Submission Date: 2020-03-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2020，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2000000000;

int G[700000], capacity = 0, prepared = 0;

int getFn(int n)
{
    if (!prepared) {
        G[0] = 1, G[1] = 2, G[2] = 4;
        int idx = 0;
        while (G[G[idx] - 1] < MAXN) {
            for (int j = G[idx]; j < G[idx + 1]; j++)
                G[j] = G[j - 1] + idx + 1;
            idx++;
        }
        capacity = G[idx] - 1;
        prepared = 1;
    }
    return upper_bound(G, G + capacity, n) - G;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    while (cin >> n, n) cout << getFn(n) << '\n';

    return 0;
}
