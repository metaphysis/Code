// High School Assembly
// UVa ID: 13082
// Verdict: Accepted
// Submission Date: 2022-01-30
// UVa Run Time: 0.010s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T, n;
    cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        cout << "Case " << cs << ": ";
        cin >> n;
        int now = 0;
        for (int i = 0, h; i < n; i++)
        {
            cin >> h;
            if ((now + 1) == h) now++;
        }
        cout << n - now << '\n';
    }
    return 0;
}
