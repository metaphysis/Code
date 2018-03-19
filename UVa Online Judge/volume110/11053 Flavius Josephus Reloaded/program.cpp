// Flavius Josephus Reloaded
// UVa ID: 11053
// Verdict: Accepted
// Submission Date: 2018-03-19
// UVa Run Time: 0.910s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long N, a, b, x;
    while (cin >> N)
    {
        if (N == 0) break;
        cin >> a >> b;
        x = 0;
        int steps = 0;
        map<int, int> indexer;
        while (true)
        {
            x = ((a * x % N) * x % N + b) % N;
            if (indexer.find(x) != indexer.end())
                break;
            indexer[x] = steps++;
        }
        cout << (N - (steps - indexer[x])) << '\n';
    }

    return 0;
}
