// Seven Seas
// UVa ID: 10923
// Verdict: Accepted
// Submission Date: 2018-07-11
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int offset[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

bool dfs(int depth, bitset<72> enemies, bitset<72> rocks, int si, int sj)
{
    if (depth > 9) return false;
    if (enemies.count() == 0) return true;
    for (int k = 0; k < 8; k++)
    {
        int nexti = si + offset[k][0], nextj = sj + offset[k][1];
        if (nexti < 0 || nexti >= 9 || nextj < 0 || nextj >= 8) continue;
        if (enemies.test(nexti * 8 + nextj) || rocks.test(nexti * 8 + nextj)) continue;
        bitset<72> nexte, nextr(rocks);
        bool destroyed = false;
        for (int p = 0; p < 72; p++)
        {
            if (!enemies.test(p)) continue;
            int pi = p / 8, pj = p % 8;
            if (pi < nexti) pi += 1;
            else if (pi > nexti) pi -= 1;
            if (pj < nextj) pj += 1;
            else if (pj > nextj) pj -= 1;
            if (pi == nexti && pj == nextj) { destroyed = true; break; }
            if (nextr.test(pi * 8 + pj)) continue;
            if (nexte.test(pi * 8 + pj))
            {
                nexte.set(pi * 8 + pj, 0);
                nextr.set(pi * 8 + pj);
            }
            else nexte.set(pi * 8 + pj);
        }
        if (destroyed) continue;
        if (dfs(depth + 1, nexte, nextr, nexti, nextj)) return true;
    }
    
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, si, sj;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        bitset<72> enemies, rocks;
        char c;
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 8; j++)
            {
                cin >> c;
                if (c == 'E') enemies.set(i * 8 + j);
                else if (c == '#') rocks.set(i * 8 + j);
                else if (c == 'S') si = i, sj = j;
            }
        if (dfs(0, enemies, rocks, si, sj)) cout << "I'm the king of the Seven Seas!\n";
        else cout << "Oh no! I'm a dead man!\n";
    }

    return 0;
}
