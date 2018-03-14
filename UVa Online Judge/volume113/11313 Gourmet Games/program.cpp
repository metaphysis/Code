// Gourmet Games
// UVa ID: 11313
// Verdict: Accepted
// Submission Date: 2018-02-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, m;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> m;
        int r = 0, shows = 0, possible = 1;
        while (true)
        {
            if (n == 1 && r == 0) break;
            if (n + r < m)
            {
                possible = 0;
                break;
            }
            int nr = n + r;
            n = nr / m, r = nr % m;
            shows += n;
        }
        if (possible) cout << shows << '\n';
        else cout << "cannot do this\n";
    }

    return 0;
}
