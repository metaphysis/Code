// Financial Management
// UVa ID: 11945
// Verdict: Accepted
// Submission Date: 2017-12-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        long long total = 0, balance;
        string money;
        for (int i = 1; i <= 12; i++)
        {
            balance = 0;
            cin >> money;
            for (int j = 0; j < money.length(); j++)
            {
                if (isdigit(money[j])) balance = balance * 10 + money[j] - '0';
            }
            total += balance;
        }
        cout << c << " $";
        long long a = total / 12, b = total % 12;
        if (b >= 6) a++;
        b = a % 100, a /= 100;

        money.clear();
        int k = 0;
        while (a > 0)
        {
            k++;
            money.insert(money.begin(), (char)('0' + (a % 10)));
            if (k % 3 == 0) money.insert(money.begin(), ',');
            a /= 10;
        }
        if (money.front() == ',') money.erase(money.begin());
        cout << money << '.' << setw(2) << setfill('0') << b << '\n';
    }

    return 0;
}
