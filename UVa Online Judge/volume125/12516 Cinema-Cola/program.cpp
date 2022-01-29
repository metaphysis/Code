// Cinema-Cola
// UVa ID: 12516
// Verdict: Accepted
// Submission Date: 2022-01-29
// UVa Run Time: 0.010s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct seat
{
    int r, c;
    bool operator<(const seat &s) const
    {
        if (r != s.r) return r < s.r;
        return c < s.c;
    }
} friends[3200];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int R, C, P, Z;
    int g[32][110][2];
    while (cin >> R >> C)
    {
        if (R == 0) break;
        memset(g, 0, sizeof g);
        cin >> P;
        string id;
        char sign;
        for (int i = 0; i < P; i++)
        {
            cin >> id >> sign;
            int r = id[0] - 'A' + 1;
            int c = stoi(id.substr(1));
            if (sign == '-')
            {
                g[r][c][0] = 1;
                g[r][c - 1][1] = 1;
            }
            else
            {
                g[r][c][1] = 1;
                g[r][c + 1][0] = 1;
            }
            
        }
        cin >> Z;
        for (int i = 0; i < Z; i++)
        {
            cin >> id;
            friends[i].r = id[0] - 'A' + 1;
            friends[i].c = stoi(id.substr(1));
        }
        sort(friends, friends + Z);
        int flag = 1;
        for (int i = 0; i < Z; i++)
        {
            if (!g[friends[i].r][friends[i].c][0])
            {
                g[friends[i].r][friends[i].c][0] = 1;
                continue;
            }
            if (!g[friends[i].r][friends[i].c][1])
            {
                g[friends[i].r][friends[i].c][1] = 1;
                g[friends[i].r][friends[i].c + 1][0] = 1;
                continue;
            }
            flag = 0;
            break;
        }
        cout << (flag ? "YES" : "NO") << '\n';
    }
    return 0;
}
