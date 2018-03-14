// Genius MJ
// UVa ID: 11894
// Verdict: Accepted
// Submission Date: 2017-12-16
// UVa Run Time: 0.120s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point { int x, y; } plug[100010];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int offset[4][4] = {
        {1, 0, 0, 1},
        {0, -1, 1, 0},
        {-1, 0, 0, -1},
        {0, 1, -1, 0}
    };

    int cases, n;
    cin >> cases;

    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
    
        point pr = point{10000, 10000};

        for (int i = 0; i < n; i++)
        {
            cin >> plug[i].x >> plug[i].y;
            if (plug[i].y < pr.y || (plug[i].y == pr.y && plug[i].x < pr.x))
                pr.x = plug[i].x, pr.y = plug[i].y;
        }
    
        int xi, yi;
        unordered_map<int, unordered_set<int>> socket;
        point p[4] = {point{10000, 10000}, point{-10000, 10000}, point{-10000, -10000}, point{10000, -10000}}; 
        for (int i = 0; i < n; i++)
        {
            cin >> xi >> yi;
            socket[xi].insert(yi);
            if (yi < p[0].y || (yi == p[0].y && xi < p[0].x)) p[0].x = xi, p[0].y = yi;
            if (xi > p[1].x || (xi == p[1].x && yi < p[1].y)) p[1].x = xi, p[1].y = yi;
            if (yi > p[2].y || (yi == p[2].y && xi > p[2].x)) p[2].x = xi, p[2].y = yi;
            if (xi < p[3].x || (xi == p[3].x && yi > p[3].y)) p[3].x = xi, p[3].y = yi;
        }

        int flag = 0;
        for (int i = 0; i < 4; i++)
        {
            int prx = pr.x * offset[i][0] + pr.y * offset[i][1];
            int pry = pr.x * offset[i][2] + pr.y * offset[i][3];
            int biasx = p[i].x - prx, biasy = p[i].y - pry;
            
            bool matched = true;
            for (int j = 0; j < n; j++)
            {
                prx = plug[j].x * offset[i][0] + plug[j].y * offset[i][1] + biasx;
                pry = plug[j].x * offset[i][2] + plug[j].y * offset[i][3] + biasy;
                
                if (socket.find(prx) == socket.end())
                {
                    matched = false;
                    break;
                }
                
                if (socket[prx].find(pry) == socket[prx].end())
                {
                    matched = false;
                    break;
                }
            }
            
            if (matched)
            {
                flag = 1;
                break;
            }
        }
        
        cout << (flag ? "MATCHED" : "NOT MATCHED") << '\n';
    }

    return 0;
}
