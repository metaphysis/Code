#include <iostream>
#include <limits>
#include <algorithm>

using namespace std;

int denominations[110], n;
int coins[10010], parentMoney[10010], index[10010];
int counter[110];
const int MAX_INT = numeric_limits < int >::max();

void findPath(int money)
{
    if (money > 0)
    {
        counter[index[money]]++;
        findPath(parentMoney[money]);
    }
}

void findMiniumCoins(int money)
{
    fill(coins, coins + 10010, MAX_INT);
    fill(counter, counter + 110, 0);

    coins[0] = 0;
    for (int m = 1; m <= money; m++)
    {
        int minCoins = MAX_INT, minIndex = MAX_INT;
        for (int d = 0; d < n; d++)
            if (m >= denominations[d] &&
                coins[m - denominations[d]] != MAX_INT &&
                minCoins > (coins[m - denominations[d]] + 1))
            {
                minCoins = coins[m - denominations[d]] + 1;
                minIndex = d;
            }

        if (minIndex != MAX_INT)
        {
            coins[m] = minCoins;
            parentMoney[m] = m - denominations[minIndex];
            index[m] = minIndex;
        }
    }

    if (coins[money] == MAX_INT)
        cout << "No solution." << endl;
    else
    {
        cout << coins[money];

        findPath(money);

        int plusPrinted = 0;
        for (int i = 0; i < n; i++)
            if (counter[i] > 0)
            {
                cout << (plusPrinted++ ? "+" : " ");
                cout << denominations[i] << "*" << counter[i];
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
            cin >> denominations[i];

        sort(denominations, denominations + n);
        n = unique(denominations, denominations + n) - denominations;

        cin >> money;
        findMiniumCoins((int)(money * 100.0 + 0.5));
    }

    return 0;
}
