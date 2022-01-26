// A Benevolent Josephus
// UVa ID: 1176
// Verdict: Accepted
// Submission Date: 2022-01-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int survivor[32800];
    survivor[1] = 0;
    for (int i = 2; i <= 32767; i++) survivor[i] = (survivor[i - 1] + 2) % i;
    int n;
    while (cin >> n)
    {
        int cnt = 0;
        while (true)
        {
            int last = survivor[n];
            if (last == n - 1)
            {
                cnt += 2 * n;
                break;
            }
            cnt += n - 1 - last;
            n = last + 1;
        }
        cout << cnt << '\n';
    }
    return 0;
}
