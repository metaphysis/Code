// Switch The Lights
// UVa ID: 11974
// Verdict: Accepted
// Submission Date: 2018-07-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, N, M, mask[110], idx;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> N >> M;

        for (int i = 0; i < M; i++)
        {
            mask[i] = 0;
            for (int j = 0; j < N; j++)
            {
                cin >> idx;
                mask[i] |= (idx << j);
            }
        }

        int moves[1 << 16] = {}, lamps, next;
        queue<int> q;
        q.push((1 << N) - 1);
        moves[(1 << N) - 1] = 1;

        while (!q.empty() && moves[0] == 0)
        {
            lamps = q.front(); q.pop();
            for (int i = 0; i < M; i++)
            {
                next = lamps ^ mask[i];
                if (moves[next] == 0)
                {
                    moves[next] = moves[lamps] + 1;
                    q.push(next);
                }
            }
        }

        cout << "Case " << cs << ": ";
        if (moves[0] == 0) cout << "IMPOSSIBLE\n";
        else cout << (moves[0] - 1) << '\n';
    }

    return 0;
}
