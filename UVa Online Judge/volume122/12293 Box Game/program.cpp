// Box Game
// UVa ID: 12293
// Verdict: Accepted
// Submission Date: 2018-06-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    vector<int> N = {1};
    while ((N.back() * 2 + 1) <= 1000000000) N.push_back(N.back() * 2 + 1);

    int n;
    while (cin >> n, n > 0)
    {
        if (binary_search(N.begin(), N.end(), n)) cout << "Bob\n";
        else cout << "Alice\n";
    }

    return 0;
}
