// Collecting Beepers
// UVa ID: 10496
// Verdict: Accepted
// Submission Date: 2018-01-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, width, height, startx, starty, beeperx[11], beepery[11];

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> width >> height;
        cin >> startx >> starty;
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> beeperx[i] >> beepery[i];
        }
        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);
        int minimum = 0x3fffffff;
        do
        {
            int length = 0;
            int lastx = startx, lasty = starty;
            for (auto k : idx)
            {
                length += abs(beeperx[k] - lastx) + abs(beepery[k] - lasty);
                if (length > minimum) break;
                lastx = beeperx[k], lasty = beepery[k];
            }
            length += abs(startx - lastx) + abs(starty - lasty);
            minimum = min(minimum, length);
        } while (next_permutation(idx.begin(), idx.end()));
        cout << "The shortest path has length " << minimum << '\n';
    }

    return 0;
}
