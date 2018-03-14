// Amazing
// UVa ID: 556
// Verdict: Accepted
// Submission Date: 2016-08-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int b, w;
    char grid[100][100];
    int counter[100][100];
    int offset[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int rightside[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    
    while (cin >> b >> w, b)
    {
        memset(counter, 0, sizeof(counter));
        
        for (int i = 1; i <= b; i++)
            for (int j = 1; j <= w; j++)
                cin >> grid[b - i + 1][j];
        
        int x = 1, y = 1, nextx, nexty, rightx, righty, d = 0;    
        do
        {
            nextx = x + offset[d][0], nexty = y + offset[d][1];
            if (nextx < 1 || nextx > b || nexty < 1 || nexty > w || grid[nextx][nexty] == '1')
            {
                d++;
                d %= 4;
            }
            else
            {
                //cout << nextx << ' ' << nexty << '\n';
                
                counter[nextx][nexty]++;
                x = nextx, y = nexty;

                rightx = nextx + rightside[d][0], righty = nexty + rightside[d][1];
                if (rightx >= 1 && rightx <= b && righty >= 1 && righty <= w && grid[rightx][righty] == '0')
                {
                    d += 3;
                    d %= 4;
                }
            }
        } while (x != 1 || y != 1);
        
        int times[5] = {0, 0, 0, 0, 0};
        for (int i = 1; i <= b; i++)
            for (int j = 1; j <= w; j++)
                if (grid[i][j] == '0')
                    times[counter[i][j]]++;
        for (int i = 0; i <= 4; i++)
            cout << setw(3) << times[i];
        cout << '\n';
    }
    
	return 0;
}
