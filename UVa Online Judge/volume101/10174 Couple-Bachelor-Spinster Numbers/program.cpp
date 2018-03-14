// Couple-Bachelor-Spinster Numbers
// UVa ID: 10174
// Verdict: Accepted
// Submission Date: 2018-03-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long n1, n2, a, b;
    string line;
    while (getline(cin, line))
    {
        istringstream iss(line);
        iss >> n1;
        if (iss >> n2)
        {
            int bachelor = 0;
            for (long long i = n1; i <= n2; i++)
                bachelor += (!(i & 1) && (i % 4 != 0));
            cout << bachelor << '\n';
        }
        else
        {
            bool negative = n1 < 0;
            n1 = abs(n1);
            if (n1 % 2 == 1)
            {
                a = (1 + n1) / 2;
                b = n1 - a;
                if (negative)
                    cout << min(a, b) << ' ' << max(a, b) << '\n';
                else
                    cout << max(a, b) << ' ' << min(a, b) << '\n';
            }
            else
            {
                long long half = n1 / 2;
                if (n1 % 4 != 0) cout << "Bachelor Number.\n";
                else
                {
                    a = (half + 2) / 2;
                    b = max(2LL, half) - a;
                    if (negative)
                        cout << min(a, b) << ' ' << max(a, b) << '\n';
                    else
                        cout << max(a, b) << ' ' << min(a, b) << '\n';
                }
            }
        }
    }

    return 0;
}
