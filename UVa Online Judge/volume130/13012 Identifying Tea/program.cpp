// Identifying Tea
// UVa ID: 13012
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

    int T, C, A;
    while (cin >> T)
    {
        C = 0;
        for (int i = 0; i < 5; i++)
        {
            cin >> A;
            C += A == T;
        }
        cout << C << '\n';
    }

    return 0;
}
