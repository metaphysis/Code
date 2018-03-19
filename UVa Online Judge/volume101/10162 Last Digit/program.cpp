// Last Digit
// UVa ID: 10162
// Verdict: Accepted
// Submission Date: 2018-03-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2018, 邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int table[20] = {0, 1, 5, 2, 8, 3, 9, 2, 8, 7, 7, 8, 4, 7, 3, 8, 4, 1, 5, 4};
    string n;
    while (cin >> n)
    {
        if (n == "0") break;
        int tail = 0, length = n.length();
        for (int i = length - 2; i < length; i++)
            if (i >= 0)
                tail = tail * 10 + n[i] - '0';
        cout << (table[tail % 20] + tail / 20 * 4) % 10 << '\n';
    }

    return 0;
}
