// Spanning Subtrees
// UVa ID: 11597
// Verdict: Accepted
// Submission Date: 2018-04-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    int n;
    
    while (cin >> n, n > 0)
    {
        cout << "Case " << ++cases << ": " << n / 2 << '\n';
    }

    return 0;
}
