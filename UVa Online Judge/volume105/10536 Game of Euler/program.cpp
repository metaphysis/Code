// Game of Euler
// UVa ID: 10536
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int cache[1 << 16], offset[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int dfs(int x)
{
    if (~cache[x]) return cache[x];
    for (int i = 0; i < 16; i++)
        for (int j = 0; j < 4; j++)
        {
            int r = i / 4, c = i % 4, bit = 0;
            for (int k = 0; k <= 2; k++)
            {
                int rr = r + offset[j][0] * k, cc = c + offset[j][1] * k;
                if (rr < 0 || rr > 3 || cc < 0 || cc > 3) break;
                if (!(x & (1 << (rr * 4 + cc)))) break;
                bit |= ((1 << (rr * 4 + cc)));
                if (!dfs(x ^ bit)) return cache[x] = 1;
            }
        }
    return cache[x] = 0;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    memset(cache, -1, sizeof(cache));
    cache[0] = 1;
    
    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        int mask = 0, cnt = 0;
        char character;
        while (cnt < 16)
        {
            cin >> character;
            if (character == 'X' || character == '.')
            {
                if (character == '.')
                    mask |= (1 << cnt);
                cnt++;
            }
        }
        cout << (dfs(mask) ? "WINNING" : "LOSING") << '\n';
    }

    return 0;
}
