// The Countess' Pearls
// UVa ID: 13180
// Verdict: Accepted
// Submission Date: 2021-12-24
// UVa Run Time: 0.020s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int pearls[1024], diameter, n;
    while (cin >> diameter)
    {
        if (diameter == 0) break;
        n = 0;
        pearls[n++] = diameter;
        while (cin >> diameter, diameter) pearls[n++] = diameter;
        if (n % 2 == 0) cout << "NO\n";
        else
        {
            sort(pearls, pearls + n, greater<int>());
            int last = pearls[0], flag = 1;
            for (int i = 1, j = 2; i < n && j < n; i += 2, j += 2)
            {
                if (pearls[i] != pearls[j] || pearls[i] == last)
                {
                    flag = 0;
                    break;
                }
                last = pearls[i];
            }
            if (!flag) cout << "NO\n";
            else
            {
                sort(pearls, pearls + n);
                int nn = unique(pearls, pearls + n) - pearls;
                for (int i = nn, j = nn - 2; i < n; i++, j--) pearls[i] = pearls[j];
                for (int i = 0; i < n; i++)
                    cout << pearls[i] << (i + 1 == n ? '\n' : ' ');
            }
        }
    }

    return 0;
}
