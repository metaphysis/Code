// Gift?!
// UVa ID: 10120
// Verdict: Accepted
// Submission Date: 2023-01-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;
int d[110];
int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n, m;
    while (cin >> n >> m, n) {
        if (n >= 50) cout << "Let me try!\n";
        else {
            queue<int> q;
            q.push(1);
            d[1] = 1;
            bool flag = false;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                if (u == m) { flag = true; break; }
                int v = u + d[u] + 2;
                if (v <= n) {
                    q.push(v);
                    d[v] = d[u] + 2;
                }
                v = u - d[u] - 2;
                if (v > 0) {
                    q.push(v);
                    d[v] = d[u] + 2;
                }
            }
            cout << (flag ? "Let me try!" : "Don't make fun of me!") << '\n';
        }
    }
    return 0;
}
