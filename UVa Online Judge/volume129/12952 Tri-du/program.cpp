// Tri-du
// UVa ID: 12952
// Verdict: Accepted
// Submission Date: 2018-04-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int A, B;
    while (cin >> A >> B)
    {
        if (A == B || A > B) cout << A << '\n';
        else cout << B << '\n';
    }

    return 0;
}
