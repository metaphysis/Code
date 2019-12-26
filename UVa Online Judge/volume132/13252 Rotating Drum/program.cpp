// Rotating Drum
// UVa ID: 13252
// Verdict: Accepted
// Submission Date: 2019-12-26
// UVa Run Time: 0.020s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int k, n, m, next[100010], visited[100010];
    while (cin >> k >> n)
    {
        if (k == 1)
        {
            for (int i = 1; i <= n; i++) cout << 'A';
            cout << '\n';
            continue;
        }
        m = pow(k, n);
        int group = m / k;
        for (int i = 0; i < group; i++)
            for (int j = 0; j < k; j++)
                next[j * group + i] = i * k + j;
        memset(visited, 0, sizeof visited);
        for (int i = 0; i < m; i++)
        {
            if (visited[i]) continue;
            for (int j = i; !visited[j]; j = next[j])
            {
                visited[j] = 1;
                cout << char('A' + j / group);
            }
        }
        cout << '\n';
    }

    return 0;
}
