// Overlapping Air Traffic Control Zones
// UVa ID: 904
// Verdict: Accepted
// Submission Date: 2018-12-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    int x1[32], y1[64], z1[64], x2[64], y2[64], z2[64];

    while (cin >> n)
    {
        vector<int> xs, ys, zs;
        for (int i = 0; i < n; i++)
        {
            cin >> x1[i] >> y1[i] >> z1[i];
            cin >> x2[i] >> y2[i] >> z2[i];
            xs.push_back(x1[i]); xs.push_back(x2[i]);
            ys.push_back(y1[i]); ys.push_back(y2[i]);
            zs.push_back(z1[i]); zs.push_back(z2[i]);
        }

        sort(xs.begin(), xs.end());
        sort(ys.begin(), ys.end());
        sort(zs.begin(), zs.end());

        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        zs.erase(unique(zs.begin(), zs.end()), zs.end());

        for (int i = 0; i < n; i++)
        {
            x1[i] = lower_bound(xs.begin(), xs.end(), x1[i]) - xs.begin();
            x2[i] = lower_bound(xs.begin(), xs.end(), x2[i]) - xs.begin();
            y1[i] = lower_bound(ys.begin(), ys.end(), y1[i]) - ys.begin();
            y2[i] = lower_bound(ys.begin(), ys.end(), y2[i]) - ys.begin();
            z1[i] = lower_bound(zs.begin(), zs.end(), z1[i]) - zs.begin();
            z2[i] = lower_bound(zs.begin(), zs.end(), z2[i]) - zs.begin();
        }

        int g[32][32][32] = {};
        for (int c = 0; c < n; c++)
            for (int i = x1[c]; i < x2[c]; i++)
                for (int j = y1[c]; j < y2[c]; j++)
                    for (int k = z1[c]; k < z2[c]; k++)
                        g[i][j][k]++;

        int volume = 0;
        for (int i = 0; i < 31; i++)
            for (int j = 0; j < 31; j++)
                for (int k = 0; k < 31; k++)
                    if (g[i][j][k] >= 2)
                        volume += (xs[i + 1] - xs[i]) * (ys[j + 1] - ys[j]) * (zs[k + 1] - zs[k]);
        cout << volume << '\n';
    }

    return 0;
}
