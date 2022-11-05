// Frieze Patterns
// UVa ID: 11511
// Verdict: Accepted
// Submission Date: 2022-11-05
// UVa Run Time: 0.050s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int v1[1010], v2[2][1010], v3[1000010];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, row, cln;
    while (cin >> n, n)
    {
        cin >> row >> cln;
        row--, cln--;
        for (int i = 0; i < n; i++) { cin >> v1[i]; v2[0][i] = v1[i]; }
        int cr = 0, nr = (cr + 1) % 2, cnt = 0;
        v3[cnt++] = v1[row];
        while (true)
        {
            bool same = true;
            v2[nr][0] = v2[nr][n - 1] = 1;
            for (int i = 1; i < n - 1; i++)
            {
                v2[nr][i] = (v2[nr][i - 1] * v2[cr][i + 1] + 1) / v2[cr][i];
                if (v2[nr][i] != v1[i]) same = false;
            }
            v3[cnt++] = v2[nr][row];
            if (cnt > cln)
            {
                cout << v3[cln] << '\n';
                break;
            }
            if (same)
            {
                cout << v3[cln % (cnt - 1)] << '\n';
                break;
            }
            cr = nr, nr = (cr + 1) % 2;
        }
    }

    return 0;
}
