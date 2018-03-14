// In The Airport
// UVa ID: 11968
// Verdict: Accepted
// Submission Date: 2018-02-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1010;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long cases, N, M, K, price;
    long long cakes[MAXV], drinks[MAXV];

    cin >> cases;
    for (long long c = 1; c <= cases; c++)
    {
        cin >> N >> M >> K;
        long long total = 0;
        for (int i = 0; i < M; i++)
        {
            cin >> cakes[i];
            total += cakes[i];
        }
        for (long long i = 0; i < K; i++)
        {
            cin >> drinks[i];
            total += drinks[i];
        }
        for (long long i = (M + K); i < N; i++)
        {
            cin >> price;
            total += price;
        }
        long long diff;
        long long closestCake = cakes[0], cakeDiff = abs(total - cakes[0] * N);
        for (int i = 1; i < M; i++)
        {
            diff = abs(total - cakes[i] * N);
            if (diff < cakeDiff)
            {
                closestCake = cakes[i];
                cakeDiff = diff;
            }
            else if (diff == closestCake)
            {
                if (cakes[i] < closestCake)
                    closestCake = cakes[i];
            }
        }
        long long closestDrink = drinks[0], drinkDiff = abs(total - drinks[0] * N);
        for (int i = 1; i < K; i++)
        {
            diff = abs(total - drinks[i] * N);
            if (diff < drinkDiff)
            {
                closestDrink = drinks[i];
                drinkDiff = diff;
            }
            else if (diff == closestDrink)
            {
                if (drinks[i] < closestDrink)
                    closestDrink = drinks[i];
            }
        }
        cout << "Case #" << c << ": " << closestCake << ' ' << closestDrink << '\n';
    }

    return 0;
}
