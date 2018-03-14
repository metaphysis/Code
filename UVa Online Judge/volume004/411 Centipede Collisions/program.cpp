// Centipede Collisions
// UVa ID: 411
// Verdict: Accepted
// Submission Date: 2017-02-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// L, U, R, D
map<char, int> directions = {{'L', 0}, {'U', 1}, {'R', 2}, {'D', 3}};
int offset[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

struct centipede
{
    int x, y, length, offsetx, offsety, segments[40];
};

centipede centipedes[20];
char grid[40][40];

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n;
    while (cin >> n)
    {
        memset(grid, '.', sizeof(grid));
        
        char direction;
        int length, x, y;

        for (int i = 0; i < n; i++)
        {
            cin >> direction >> length >> x >> y;
            centipedes[i].x = x;
            centipedes[i].y = y;
            centipedes[i].length = length;
            centipedes[i].offsetx = offset[directions[direction]][0];
            centipedes[i].offsety = offset[directions[direction]][1];
            
            for (int j = 0; j < length; j++)
            {
                grid[29 - y][x] = i + '0';
                x -= offset[directions[direction]][0];
                y -= offset[directions[direction]][1];
                centipedes[i].segments[j] = 1;
            }
        }
        
        while (true)
        {
            bool updated = false;
            for (int i = 0; i < n; i++)
            {
                int xx = centipedes[i].x, yy = centipedes[i].y;
                for (int j = 0; j < centipedes[i].length; j++)
                {
                    if (centipedes[i].segments[j] > 0)
                    {
                        if (xx >= 0 && xx <= 29 && yy >= 0 && yy <= 29)
                        {
                            if (grid[29 - yy][xx] == 'X')
                            {
                                centipedes[i].segments[j] = 0;
                                updated = true;
                            }
                        }
                    }
                    xx -= centipedes[i].offsetx;
                    yy -= centipedes[i].offsety;
                }
                
                xx = centipedes[i].x, yy = centipedes[i].y;
                for (int j = 0; j < centipedes[i].length; j++)
                {
                    if (xx >= 0 && xx <= 29 && yy >= 0 && yy <= 29)
                    {
                        if (grid[29 - yy][xx] == (i + '0'))
                            grid[29 - yy][xx] = '.';
                    }
                    xx -= centipedes[i].offsetx;
                    yy -= centipedes[i].offsety;
                }
                
                centipedes[i].x += centipedes[i].offsetx;
                centipedes[i].y += centipedes[i].offsety;
                
                xx = centipedes[i].x, yy = centipedes[i].y;
                for (int j = 0; j < centipedes[i].length; j++)
                {
                    if (centipedes[i].segments[j] > 0)
                    {
                        if (xx >= 0 && xx <= 29 && yy >= 0 && yy <= 29)
                        {
                            if (grid[29 - yy][xx] != '.')
                            {
                                grid[29 - yy][xx] = 'X';
                                centipedes[i].segments[j] = 0;
                            }
                            else
                            {
                                grid[29 - yy][xx] = i + '0';
                            }
                        }
                        else
                        {
                            centipedes[i].segments[j] = 0;
                        }
                        
                        updated = true;
                    }
                    
                    xx -= centipedes[i].offsetx;
                    yy -= centipedes[i].offsety;
                }
            }
            
            if (!updated) break;
        }
        
        cout << "   0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2\n";
        cout << "   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9\n";
        for (int i = 0; i < 30; i++)
        {
            int label = 29 - i;
            cout << setw(2) << setfill('0') << label;
            
            for (int j = 0; j < 30; j++) cout << ' ' << grid[i][j];
            cout << '\n';
        }
        cout << '\n';
    }
    
	return 0;
}
