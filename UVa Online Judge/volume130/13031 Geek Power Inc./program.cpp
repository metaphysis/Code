// Geek Power Inc.
// UVa ID: 13031
// Verdict: Accepted
// Submission Date: 2022-01-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct power { int ki, pi; } source[64];
bool cmp(power a, power b) { return a.pi > b.pi; }
int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T, n;
    cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> source[i].ki >> source[i].pi;
        sort(source, source + n, cmp);
        cout << "Case " << cs << ": ";
        long long r = 0, cnt = 0;
        for (int i = 0; i < n; i++)
        {
            cnt += source[i].ki;
            r = max(r, cnt * source[i].pi);
        }
        cout << r << '\n';
    }
    return 0;
}
