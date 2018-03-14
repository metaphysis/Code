// Coast Tracker
// UVa ID: 824
// Verdict: Accepted
// Submission Date: 2016-12-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int offset[8][2] = {{0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}};
    int next[8]= {6, 6, 0, 0, 2, 2, 4, 4};
    int x, y, d, xi, yi, si;
    int surface[3][3];

    while (cin >> x, x > 0)
    {
        cin >> y >> d;
        for (int i = 0; i < 8; i++)
        {
            cin >> xi >> yi >> si;
            surface[xi - x + 1][yi - y + 1] = si;
        }
        
        for (int i = 0; i < 8; i++)
        {
            int nextd = (next[d] + i) % 8;
            int nextx = 1 + offset[nextd][0];
            int nexty = 1 + offset[nextd][1];
            
            if (surface[nextx][nexty])
            {
                cout << nextd << '\n';
                break;
            }
        }
    }
    
	return 0;
}
