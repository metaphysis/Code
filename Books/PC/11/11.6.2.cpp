#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

int n;
int denom[110];
int coins[10010], parent[10010], idx[10010], cnt[110];

void findPath(int money)
{
    if (money > 0)
    {
        cnt[idx[money]]++;
        findPath(parent[money]);
    }
}

void findMiniumCoins(int money)
{
    fill(coins, coins + 10010, INF);
    fill(cnt, cnt + 110, 0);

    coins[0] = 0;
    for (int m = 1; m <= money; m++)
    {
        int minCoins = INF, minIdx = INF;
        for (int d = 0; d < n; d++)
            if (m >= denom[d] && coins[m - denom[d]] != INF &&
                minCoins > (coins[m - denom[d]] + 1))
                minCoins = coins[m - denom[d]] + 1, minIdx = d;

        if (minIdx != INF)
        {
            coins[m] = minCoins;
            parent[m] = m - denom[minIdx];
            idx[m] = minIdx;
        }
    }

    if (coins[money] == INF)
        cout << "No solution." << endl;
    else
    {
        cout << coins[money];

        findPath(money);

        int plusPrinted = 0;
        for (int i = 0; i < n; i++)
            if (cnt[i] > 0)
            {
                cout << (plusPrinted++ ? "+" : " ");
                cout << denom[i] << "*" << cnt[i];
            }
        cout << endl;
    }
}

int main(int argc, char *argv[])
{
    double money;
    while (cin >> n, n)
    {
        for (int i = 0; i < n; i++)
            cin >> denom[i];

        sort(denom, denom + n);
        n = unique(denom, denom + n) - denom;

        cin >> money;
        findMiniumCoins((int)(money * 100.0 + 0.5));
    }

    return 0;
}
