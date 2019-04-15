// Huatuo's Medicine
// UVa ID: 12992
// Verdict: Accepted
// Submission Date: 2019-04-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n;
        cout << "Case #" << cs << ": " << (2 * n - 1) << '\n';
    }

    return 0;
}
