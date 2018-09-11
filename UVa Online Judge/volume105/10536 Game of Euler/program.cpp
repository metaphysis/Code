// Game of Euler
// UVa ID: 10536
// Verdict: Accepted
// Submission Date: 2018-09-12
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int cache[1 << 16], offset[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int dfs(int x)
{
    if (~cache[x]) return cache[x];
    for (int i = 0; i < 16; i++)
    {
        if (x & (1 << i))
        {
            if (!dfs(x ^ (1 << i))) return cache[x] = 1;
            int r = i / 4, c = i % 4;
            int available[4] = {r == 0, c == 0, r == 3, c == 3};
            for (int j = 0; j < 4; j++)
            {
                if (!available[j]) continue;
                int bit = (1 << i);
                for (int k = 1; k <= 2; k++)
                {
                    int rr = r + offset[j][0] * k, cc = c + offset[j][1] * k;
                    if (rr < 0 || rr > 3 || cc < 0 || cc > 3) break;
                    if (!(x & (1 << (rr * 4 + cc)))) break;
                    bit |= ((1 << (rr * 4 + cc)));
                    if (!dfs(x ^ bit)) return cache[x] = 1;
                }
            }
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
