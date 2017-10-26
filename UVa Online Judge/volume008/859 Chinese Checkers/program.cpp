// Chinese Checkers
// UVa ID: 859
// Verdict: Accepted
// Submission Date: 2017-10-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const int MAXL = 110, MAXC = 110;

struct state {
    int r, c, flag, jumps;
    
    bool operator<(const state &s) const
    {
        if (r != s.r) return r > s.r;
        else return c < s.c;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    int L, C;
    char grid[MAXL][MAXC];
    int visited[MAXL][MAXC], steps[MAXL][MAXC];
    int offset[3][2] = {{0, -1}, {1, 0}, {0, 1}};
    int jump[5][2] = {{0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}};

    while (cin >> L >> C)
    {
        for (int i = 1; i <= L; i++)
            for (int j = 1; j <= C; j++)
                grid[i][j] = '0', visited[i][j] = 0, steps[i][j] = 0x3fffffff;
                
        int x, y;
        for (int i = 1; i <= 4 * C; i++)
        {
            cin >> x >> y;
            grid[x][y] = '1';
        }
        
        cin >> x >> y;
        state s = state{x, y, 0, 0};
        queue<state> q; q.push(s);
        visited[x][y] = 1, grid[x][y] = '0';

        while (!q.empty())
        {
            s = q.front(); q.pop();           
            steps[s.r][s.c] = min(steps[s.r][s.c], s.jumps);
            
            if (s.flag == 0)
            {
                for (int k = 0; k < 3; k++)
                {
                    int ii = s.r + offset[k][0], jj = s.c + offset[k][1];
                    if (ii >= 1 && ii <= L && jj >= 1 && jj <= C)
                    {
                        if (!visited[ii][jj] && grid[ii][jj] == '0')
                        {
                            visited[ii][jj] = 1;
                            q.push(state{ii, jj, 1, s.jumps + 1});
                        }
                    }
                }
            }
            if (s.flag == 0 || s.flag == 2)
            {
                for (int k = 0; k < 5; k++)
                {
                    int ii = s.r + jump[k][0], jj = s.c + jump[k][1];
                    int iii = ii + jump[k][0], jjj = jj + jump[k][1];
                    if (ii >= 1 && ii <= L && jj >= 1 && jj <= C)
                    {
                        if (iii >= 1 && iii <= L && jjj >= 1 && jjj <= C)
                        {
                            if (grid[ii][jj] == '1' && grid[iii][jjj] == '0')
                            {
                                if (!visited[iii][jjj])
                                {
                                    visited[iii][jjj] = 1;
                                    q.push(state{iii, jjj, 2, s.jumps + 1});
                                }
                            }
                        }
                    }
                }
            }
        }

        if (cases++ > 0) cout << '\n';
        vector<state> all;
        for (int i = 1; i <= L; i++)
            for (int j = 1; j <= C; j++)
                if (visited[i][j] && steps[i][j])
                    all.push_back(state{i, j, 0, steps[i][j]});
        sort(all.begin(), all.end());
        for (auto a : all) cout << a.r << ' ' << a.c << ' ' << a.jumps << '\n';
    }
    
    
    return 0;
}
