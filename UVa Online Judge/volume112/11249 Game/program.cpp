// Game
// UVa ID: 11249
// Verdict: Accepted
// Submission Date: 2018-06-23
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100001;

int losing[MAXN];

void initialize(int k)
{
    memset(losing, 0, sizeof(losing));
    for (int i = 1, pre = 0; i < MAXN; i++)
    {
        if (losing[i]) continue;
        int lose = losing[pre] - pre + i + k + 1;
        pre = i;
        losing[i] = lose;
        if (lose >= MAXN) continue;
        losing[lose] = i;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, k, q, a, b;
    
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> k >> q;
        initialize(k);
        for (int i = 1; i <= q; i++)
        {
            cin >> a >> b;
            if (a > b) swap(a, b);
            if (losing[a] == b) cout << "LOSING\n";
            else cout << "WINNING\n";
        }
        cout << '\n';
    }

    return 0;
}
