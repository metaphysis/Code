// Look-and-Say Sequences
// UVa ID: 11660
// Verdict: Accepted
// Submission Date: 2018-03-15
// UVa Run Time: 0.270s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string xi, next;
    int i, j, prune;

    // Simulation.
    while (cin >> xi >> i >> j)
    {
        prune = j + 20;

        if (i == 0) break;
        next = xi;
        while (--i)
        {
            next.clear();
            int last = 0, cnt = 0;
            for (auto d : xi)
            {
                if (last && d != last)
                {
                    next += to_string(cnt);
                    next += (char)last;
                    cnt = 0;

                    // Prune.
                    if (next.length() > prune && next.back() != next[next.length() - 2]) break;
                }
                last = d;
                cnt++;
            }
            if (cnt && (next.length() < prune || next.back() == next[next.length() - 2]))
            {
                next += to_string(cnt);
                next += (char)last;
            }
            xi = next;
        }
        cout << next[j - 1] << '\n';
    }

    return 0;
}
