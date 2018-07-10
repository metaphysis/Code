// Switch Bulbs
// UVa ID: 12135
// Verdict: Accepted
// Submission Date: 2018-07-10
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, N, M, K, Q, mask[50], idx;
    string bits;

    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> N >> M;

        for (int i = 0; i < M; i++)
        {
            mask[i] = 0;
            cin >> K;
            for (int j = 0; j < K; j++)
            {
                cin >> idx;
                mask[i] |= (1 << idx);
            }
        }

        int visited[1 << 16] = {}, lamps, next;
        queue<int> q;
        q.push(0);
        visited[0] = 1;

        while (!q.empty())
        {
            lamps = q.front(); q.pop();
            for (int i = 0; i < M; i++)
            {
                next = lamps ^ mask[i];
                if (visited[next] == 0)
                {
                    visited[next] = visited[lamps] + 1;
                    q.push(next);
                }
            }
        }

        cout << "Case " << cs << ":\n";
        cin >> Q;
        for (int i = 1; i <= Q; i++)
        {
            cin >> bits;
            lamps = stoi(bits, 0, 2);
            if (visited[lamps] == 0)
                cout << -1 << '\n';
            else
                cout << (visited[lamps] - 1) << '\n';
        }
        cout << '\n';
    }

    return 0;
}
