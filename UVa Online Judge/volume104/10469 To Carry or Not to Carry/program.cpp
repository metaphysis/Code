// To Carry or Not to Carry
// UVa ID: 10469
// Verdict: Accepted
// Submission Date: 2018-02-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    unsigned a, b;
    while (cin >> a >> b)
    {
        cout << (a ^ b) << '\n';
    }

    return 0;
}
