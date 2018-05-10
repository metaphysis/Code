// Diving for Gold
// UVa ID: 990
// Verdict: Accepted
// Submission Date: 2017-02-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);

    int t, w, n, d[40], v[40];
    int coins[40][1010], choosed[40][1010];
    int cases = 0;

    while (cin >> t >> w)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> d[i] >> v[i];
            d[i] *= 3 * w;
        }

        memset(coins, 0, sizeof(coins));
        memset(choosed, 0, sizeof(choosed));

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= t; j++)
            {
                if (j >= d[i] && (coins[i - 1][j - d[i]] + v[i]) > coins[i - 1][j])
                {
                    coins[i][j] = coins[i - 1][j - d[i]] + v[i];
                    choosed[i][j] = 1;
                }
                else
                    coins[i][j] = coins[i - 1][j];
            }
        }

        int indexer = n, capacity = t;
        vector<int> boxes;

        while (indexer > 0)
        {
            if (choosed[indexer][capacity])
            {
                boxes.push_back(indexer);
                capacity -= d[indexer];
            }
            indexer--;
        }

        if (cases++ > 0)
            cout << '\n';
        cout << coins[n][t] << '\n';
        cout << boxes.size() << '\n';
        for (int i = boxes.size() - 1; i >= 0; i--)
            cout << (d[boxes[i]] / (3 * w)) << ' ' << v[boxes[i]] << '\n';
    }

    return 0;
}
