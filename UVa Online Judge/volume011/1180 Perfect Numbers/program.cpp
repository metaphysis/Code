// Perfect Numbers
// UVa ID: 1180
// Verdict: Accepted
// Submission Date: 2022-10-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases;
    cin >> cases;
    while (cases--)
    {
        int p;
        cin >> p;
        if (p == 2 || p == 3 || p == 5 || p == 7 || p == 13 || p == 17) cout << "Yes";
        else cout << "No";
        cout << '\n';
        char comma;
        if (cases) cin >> comma;
    }
    return 0;
}
