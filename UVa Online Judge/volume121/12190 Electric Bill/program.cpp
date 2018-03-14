// Electric Bill
// UVa ID: 12190
// Verdict: Accepted
// Submission Date: 2017-11-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int fee(int watt)
{
    int cost = 0;
    if (watt > 1000000) { cost += (watt - 1000000) * 7; watt = 1000000; }
    if (watt >= 10001) { cost += (watt - 10000) * 5; watt = 10000; }
    if (watt >= 101) { cost += (watt - 100) * 3; watt = 100; }
    cost += watt * 2;
    return cost;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int A, B;

    while (cin >> A >> B, A > 0)
    {
        int left = 1, right = 150000000, middle, cost, total;
        while (true)
        {
            middle = (left + right) / 2;
            cost = fee(middle);
            if (cost == A) break;
            if (cost > A) right = middle;
            else left = middle + 1;
        }

        total = middle, left = 1, right = middle;
        while (true)
        {
            middle = (left + right) / 2;
            cost = fee(total - middle) - fee(middle);
            if (cost == B) break;
            if (cost < B) right = middle;
            else left = middle + 1;
        }
        cout << fee(middle) << '\n';
    }

    return 0;
}
