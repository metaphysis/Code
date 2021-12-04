// Solve Everything
// UVa ID: 13034
// Verdict: Accepted
// Submission Date: 2021-12-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        int yes = 1;
        for (int i = 1, n; i <= 13; i++)
        {
            cin >> n;
            if (!n) yes = 0;
        }
        cout << "Set #" << cs << ": " << (yes ? "Yes" : "No") << '\n';
    }

    return 0;
}
