// Very Big Perfect Squares
// UVa ID: 12027
// Verdict: Accepted
// Submission Date: 2018-03-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string n;
    while (cin >> n, n != "0")
    {
        int length = n.length();
        if (length <= 2) cout << (int)sqrt(stoi(n)) << '\n';
        else
        {
            if (length % 2 == 0)
            {
                cout << (int)sqrt(stoi(n.substr(0, 2)));
                length = (length - 2) / 2;
                for (int i = 1; i <= length; i++)
                    cout << '0';
                cout << '\n';
            }
            else
            {
                cout << (int)sqrt(stoi(n.substr(0, 1)));
                length = (length - 1) / 2;
                for (int i = 1; i <= length; i++)
                    cout << '0';
                cout << '\n';
            }
        }
    }

    return 0;
}
