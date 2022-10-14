// Combination Lock
// UVa ID: 13049
// Verdict: Accepted
// Submission Date: 2022-10-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int T; cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        cout << "Case " << cs << ": ";
        int n;
        string a, b;
        cin >> n >> a >> b;
        int r = 0;
        for (int i = 0; i < n; i++)
            if (a[i] > b[i])
                r += min(10 + b[i] - a[i], a[i] - b[i]);
            else
                r += min(10 + a[i] - b[i], b[i] - a[i]);
        cout << r << '\n';
    }

    return 0;
}
