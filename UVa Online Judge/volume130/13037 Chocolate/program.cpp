// Chocolate
// UVa ID: 13037
// Verdict: Accepted
// Submission Date: 2022-01-05
// UVa Run Time: 0.940s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

set<int> C[3];

void getCount(int aa, int bb, int cc)
{
    int cnt = 0;
    for (auto c : C[aa])
    {
        if (C[bb].count(c)) continue;
        if (C[cc].count(c)) continue;
        cnt++;
    }
    cout << cnt;
    cnt = 0;
    for (auto c : C[bb])
    {
        if (C[aa].count(c)) continue;
        if (C[cc].count(c)) cnt++;
    }
    cout << ' ' << cnt << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        int L, R, S;
        for (int i = 0; i < 3; i++) C[i].clear();
        cin >> L >> R >> S;
        for (int i = 0, c; i < L; i++)
        {
            cin >> c;
            C[0].insert(c);
        }
        for (int i = 0, c; i < R; i++)
        {
            cin >> c;
            C[1].insert(c);
        }
        for (int i = 0, c; i < S; i++)
        {
            cin >> c;
            C[2].insert(c);
        }
        cout << "Case #" << cs << ":\n";
        getCount(0, 1, 2);
        getCount(1, 0, 2);
        getCount(2, 0, 1);
    }
    return 0;
}
