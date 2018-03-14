// Contract Revision
// UVa ID: 11830
// Verdict: Accepted
// Submission Date: 2018-03-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    char D;
    string N;
    while (cin >> D, D != '0')
    {
        bool printed = false;
        cin >> N;
        for (auto d : N)
        {
            if (d == D) continue;
            if (!printed && d == '0') continue;
            printed = true;
            cout << d;
        }
        if (!printed) cout << '0';
        cout << '\n';
    }

    return 0;
}
