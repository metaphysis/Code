// Exchange Rates
// UVa ID: 11285
// Verdict: Accepted
// Submission Date: 2018-09-23
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

double truncate(double a)
{
    string number = to_string(a);
    return stod(number.substr(0, number.find('.') + 3));
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    while (cin >> n, n > 0)
    {
        double canada = 1000, usa = 0, new_canada, new_usa, rate;
        for (int i = 1; i <= n; i++)
        {
            cin >> rate;
            new_canada = max(canada, usa * 0.97 * rate);
            new_usa = max(usa, canada * 0.97 / rate);
            canada = truncate(new_canada);
            usa = truncate(new_usa);
        }
        cout << fixed << setprecision(2) << canada << '\n';
    }

    return 0;
}
