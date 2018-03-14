// Numbering Roads!
// UVa ID: 11723
// Verdict: Accepted
// Submission Date: 2018-02-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int R, N, cases = 0;
    while (cin >> R >> N, R > 0)
    {
        cout << "Case " << ++cases << ": ";
        if (R <= N) cout << "0\n";
        else if (R > N * 27) cout << "impossible\n";
        else cout << (R - N) / N + ((R - N) % N != 0) << '\n';
    }

    return 0;
}
