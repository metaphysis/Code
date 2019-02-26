// Armstrong Number
// UVa ID: 12895
// Verdict: Accepted
// Submission Date: 2019-02-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, idx;
    int n, nn, digit[16];

    cin >> cases;
    while (cases--)
    {
        cin >> n;
        nn = n, idx = 0;
        while (n)
        {
            digit[idx++] = n % 10;
            n /= 10;
        }
        long long s = 0;
        for (int i = 0; i < idx; i++)
            s += (long long)pow(digit[i], idx);
        if (s == (long long)nn) cout << "Armstrong";
        else cout << "Not Armstrong";
        cout << '\n';
    }

    return 0;
}
