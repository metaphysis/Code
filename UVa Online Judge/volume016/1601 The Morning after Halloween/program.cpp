// The Morning after Halloween
// UVa ID: 1601
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int mask[3] = {0xff, 0xff00, 0xff0000};
int xy[3][2];

inline void unpack(int s, int n)
{
    for (int i = 0; i < n; i++)
    {
        int bit = (s & mask[i]) >> (8 * i);
        xy[i][0] = (bit >> 4);
        xy[i][1] = (bit & 0xf);
    }
}

inline int pack(int s, int i, int x, int y)
{
    return (s & (~mask[i])) | (((x << 4) | y) << (8 * i));
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    char grid[16][16];
    int w, h, n;
    int offset[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    
    while (cin >> w >> h >> n)
    {
        if (w == 0) break;
        int S = 0, T = 0;
        cin.ignore(256, '\n');
        for (int i = 0; i < h; i++)
        {
            getline(cin, line);
            for (int j = 0; j < w; j++)
            {
                grid[i][j] = line[j];
                if (isupper(grid[i][j]))
                {
                    T |= (((i << 4) | j) << (8 * (grid[i][j] - 'A')));
                    grid[i][j] = ' ';
                }
                if (islower(grid[i][j]))
                {
                    S |= (((i << 4) | j) << (8 * (grid[i][j] - 'a')));
                    grid[i][j] = ' ';
                }
            }
        }

        unordered_set<int> visited;
        queue<int> q, moves;
        q.push(S);
        visited.insert(S);
        moves.push(0);
        
        while (!q.empty())
        {
            int s = q.front(); q.pop();
            int m = moves.front(); moves.pop();
            if (s == T)
            {
                cout << m << '\n';
                break;
            }
            unpack(s, n);
            for (int i = 0; i < n; i++)
            {
                int x = xy[i][0], y = xy[i][1];
                for (int j = 0; j < 4; j++)
                {
                    int xx = x + offset[j][0], yy = y + offset[j][1];
                    if (grid[xx][yy] == '#') continue;
                    bool good = true;
                    for (int k = 0; k < n; k++)
                    {
                        if (k == i) continue;
                        if (xx == xy[k][0] && yy == xy[k][1])
                        {
                            good = false;
                            break;
                        }
                    }
                    if (!good) continue;
                    int key = pack(s, i, xx, yy);
                    if (visited.find(key) != visited.end()) continue;
                    visited.insert(key);
                    q.push(key);
                    moves.push(m + 1);
                }
            }
        }
        
    }

    return 0;
}
