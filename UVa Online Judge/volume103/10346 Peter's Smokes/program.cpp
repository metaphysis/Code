// Peter's Smokes
// UVa ID: 10346
// Verdict: Accepted
// Submission Date: 2018-02-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, k;
    while (cin >> n >> k)
    {
        int cigarettes = 0, last = 0;
        while (n > 0)
        {
            cigarettes += n;
            int next = (n + last) / k;
            last = (n + last) % k;
            n = next;
        }
        cout << cigarettes << '\n';
    }

    return 0;
}
