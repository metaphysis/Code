// Grey Codes
// UVa ID: 11173
// Verdict: Accepted
// Submission Date: 2018-01-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int N, n, k;
    cin >> N;
    for (int c = 1; c <= N; c++)
    {
        cin >> n >> k;
        cout << (k ^ (k >> 1)) << '\n';
    }

    return 0;
}
