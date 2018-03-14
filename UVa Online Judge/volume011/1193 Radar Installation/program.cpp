// Radar Installation
// UVa ID: 1193
// Verdict: Accepted
// Submission Date: 2018-01-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct island
{
    int x, y;
    bool operator<(const island &i) const
    {
       return x < i.x;
    }
}islands[1010];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, d, cases = 0;
    while (cin >> n >> d, n > 0)
    {
        bool flag = true;
        for (int i = 0; i < n; i++)
        {
            cin >> islands[i].x >> islands[i].y;
            if (islands[i].y > d) flag = false;
        }

        sort(islands, islands + n);

        cout << "Case " << ++cases << ": ";
        if (!flag) cout << "-1\n";
        else
        {
            int radars = 0;
            double cleft = islands[0].x - 2 * d, cright = islands[0].x - 2 * d;
            double covered, nleft, nright;
            for (int i = 0; i < n; i++)
            {
                covered = sqrt(d * d - islands[i].y * islands[i].y);
                nleft = islands[i].x - covered, nright = islands[i].x + covered;
                cleft = max(cleft, nleft);
                cright = min(cright, nright);
                if (cleft > cright)
                {
                    radars++;
                    cleft = nleft, cright = nright;
                }
            }
            cout << radars << '\n';
        }
    }

    return 0;
}
