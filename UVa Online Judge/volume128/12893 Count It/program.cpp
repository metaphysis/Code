// Count It
// UVa ID: 12893
// Verdict: Accepted
// Submission Date: 2022-01-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T;
    long long n;
    cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        cin >> n;
        int r = 0;
        while (n)
        {
            r += n & 1;
            n /= 2;
        }
        cout << r << '\n';
    }
    return 0;
}
