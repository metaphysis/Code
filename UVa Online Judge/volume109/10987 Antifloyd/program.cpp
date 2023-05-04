// Antifloyd
// UVa ID: 10987
// Verdict: Accepted
// Submission Date: 2023-05-04
// UVa Run Time: 0.050s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
int linked[110][110];
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T; cin >> T;
    int n, d[110][110];
    for (int cs = 1; cs <= T; cs++) {
        cout << "Case #" << cs << ":\n";
        cin >> n;
        memset(d, 0x3f, sizeof d);
        for (int i = 1; i <= n; i++) d[i][i] = 0;
        for (int i = 1; i <= n - 1; i++)
            for (int j = 1, w; j <= i; j++) {
                cin >> w;
                d[i + 1][j] = d[j][i + 1] = w;
            }
        int flag = 1;
        for (int k = 1; flag && k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    if (d[i][k] + d[k][j] < d[i][j])
                        flag = 0;
        if (!flag) {
            cout << "Need better measurements.\n\n";
            continue;
        }
        memset(linked, 1, sizeof linked);
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    if (i != j && i != k && j != k && d[i][k] + d[k][j] == d[i][j])
                        linked[i][j] = linked[j][i] = 0;
        int cables = 0;
        for (int i = 1; i <= n; i++)
            for (int j = i + 1; j <= n; j++)
                cables += linked[i][j] ? 1 : 0;
        cout << cables << '\n';
        for (int i = 1; i <= n; i++)
            for (int j = i + 1; j <= n; j++)
                if (linked[i][j])
                    cout << i << ' ' << j << ' ' << d[i][j] << '\n';
        cout << '\n';
    }
    return 0;
}
