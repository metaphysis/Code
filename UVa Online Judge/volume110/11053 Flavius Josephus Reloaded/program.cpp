// Flavius Josephus Reloaded
// UVa ID: 11053
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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
        map<int, int> calculated;

        x = 0;
        int suicide = 0;
        while (true)
        {
            x = ((a * x % N) * x % N + b) % N;
            calculated[x]++;
            if (calculated[x] == 3) break;
            if (calculated[x] == 2) suicide++;
        }
        cout << (N - suicide) << '\n';
    }

    return 0;
}
