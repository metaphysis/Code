// Square
// UVa ID: 10364
// Verdict: Accepted
// Submission Date: 2018-07-22
// UVa Run Time: 0.080s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n, stick[22], edge, marked[(1 << 20) + 10] = {};

bool dfs(int used, int depth, int sum)
{
    if (marked[used]) return false;
    if (sum == edge) return dfs(used, depth + 1, 0);
    if (depth == 4) return true;
    marked[used] = 1;
    for (int i = 0; i < n; i++)
    {
        if (used & (1 << i)) continue;
        if (sum + stick[i] > edge) continue;
        if (i && stick[i] == stick[i - 1] && !(used & (1 << (i - 1)))) continue;
        if (dfs(used | (1 << i), depth, sum + stick[i])) return true;
    }
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n;
        int sum = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> stick[i];
            sum += stick[i];
        }
        if (sum % 4 != 0)
        {
            cout << "no\n";
            continue;
        }
        edge = sum / 4;
        sort(stick, stick + n, greater<int>());
        if (stick[0] > edge)
        {
            cout << "no\n";
            continue;
        }
        memset(marked, 0, (1 << n) * sizeof(int));
        cout << (dfs(0, 0, 0) ? "yes" : "no") << '\n';
    }

    return 0;
}
