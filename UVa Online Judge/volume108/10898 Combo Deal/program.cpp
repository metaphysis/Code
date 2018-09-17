// Combo Deal
// UVa ID: 10898
// Verdict: Accepted
// Submission Date: 2018-09-11
// UVa Run Time: 0.050s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct item
{
    int quantities, prices;
} menus[16];

int items, combos, total, cache[1 << 24];

inline int subtract(int a, int b)
{
    int mask = 0xf, diff = 0, result = 0;
    for (int i = 0; i < items; i++)
    {
        diff = ((a & mask) >> (i * 4)) - ((b & mask) >> (i * 4));
        if (diff < 0) return -1;
        result |= (diff << (i * 4));
        mask <<= 4;
    }
    return result;
}

int dp(int bit)
{
    if (bit == 0) return cache[bit] = 0;
    if (~cache[bit]) return cache[bit];
    int prices = 0x3f3f3f3f, nextbit;
    for (int i = 0; i < total; i++)
    {
        if ((nextbit = subtract(bit, menus[i].quantities)) >= 0)
            prices = min(prices, dp(nextbit) + menus[i].prices);
    }
    return cache[bit] = prices;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> items)
    {
        total = 0;
        memset(menus, 0, sizeof(menus));
        for (int i = 0; i < items; i++)
        {
            menus[i].quantities |= (1 << (i * 4));
            cin >> menus[i].prices;
        }
        total += items;

        cin >> combos;
        for (int i = 0; i < combos; i++)
        {
            for (int j = 0, k; j < items; j++)
            {
                cin >> k;
                menus[items + i].quantities |= (k << (j * 4));
            }
            cin >> menus[items + i].prices;
        }
        total += combos;

        int orders;
        cin >> orders;
        memset(cache, -1, (1 << (items * 4)) * sizeof(int));
        for (int i = 0; i < orders; i++)
        {
            int bit = 0, wanted;
            for (int j = 0; j < items; j++)
            {
                cin >> wanted;
                bit |= (wanted << (j * 4));
            }
            cout << dp(bit) << '\n';
        }
    }
    
    return 0;
}
