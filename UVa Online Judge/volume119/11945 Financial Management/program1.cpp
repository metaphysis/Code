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
        double total = 0, balance;
        for (int i = 1; i <= 12; i++)
        {
           cin >> balance;
           total += balance;
        }
        stringstream ss;
        ss << fixed << setprecision(2) << (total / 12);
        string money;
        ss >> money;
        string integer = money.substr(0, money.find('.'));
        for (int i = integer.length() - 3; i > 0; i -= 3)
            integer.insert(integer.begin() + i, ','); 
        cout << c << " $" << integer << money.substr(money.find('.')) << '\n';
    }

    return 0;
}
