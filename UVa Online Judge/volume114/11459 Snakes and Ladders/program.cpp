// Snakes and Ladders
// UVa ID: 11459
// Verdict: Accepted
// Submission Date: 2017-12-25
// UVa Run Time: 0.100s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int player[1000010], change[110];
    int cases, a, b, d, step;
    int begin, end;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> a >> b >> d;

        for (int i = 1; i <= a; i++)
            player[i] = 1;

        memset(change, 0, sizeof(change));
        for (int i = 1; i <= b; i++)
        {
            cin >> begin >> end;
            change[begin] = end - begin;
        }

        int ended = 0;
        for (int i = 1, n = 1; i <= d; i++, n = (n + 1 > a ? 1 : n + 1))
        {
            cin >> step;
            if (ended) continue;
            player[n] += step;
            if (player[n] > 100) player[n] = 100;
            player[n] += change[player[n]];
            if (player[n] == 100) ended = 1;
        }
        
        for (int i = 1; i <= a; i++)
            cout << "Position of player " << i << " is " << player[i] << ".\n";
    }
    
    return 0;
}
