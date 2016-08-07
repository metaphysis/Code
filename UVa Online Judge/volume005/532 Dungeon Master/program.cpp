// Dungeon Master
// UVa ID: 532
// Verdict: Accepted
// Submission Date: 2016-08-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

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
#include <vector>

using namespace std;

struct state
{
    int i, j, k, minutes;
};

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    char grid[32][32][32], visited[32][32][32];
    
    int L, R, C;
    while (cin >> L >> R >> C, L && R && C)
    {
        int starti, startj, startk, endi, endj, endk;

        for (int i = 0; i < L; i++)
            for (int j = 0; j < R; j++)
                for (int k = 0; k < C; k++)
                {
                    cin >> grid[i][j][k];

                    if (grid[i][j][k] == 'S')
                        starti = i, startj = j, startk = k;
                    if (grid[i][j][k] == 'E')
                        endi = i, endj = j, endk = k;
                }
                        
        memset(visited, 0, sizeof(visited));
        
        queue<state> unvisited;
        unvisited.push((state){starti, startj, startk, 0});
        
        bool escaped = false;
        while (!unvisited.empty())
        {
            state current = unvisited.front();
            unvisited.pop();
            
            if (current.i < 0 || current.i >= L || current.j < 0 || current.j >= R ||
                current.k < 0 || current.k >= C || grid[current.i][current.j][current.k] == '#' ||
                visited[current.i][current.j][current.k])
                continue;
                
            visited[current.i][current.j][current.k] = 1;

            if (current.i == endi && current.j == endj && current.k == endk)
            {
                cout << "Escaped in " << current.minutes << " minute(s).\n";
                escaped = true;
                break;
            }
            
            unvisited.push((state){current.i - 1, current.j, current.k, current.minutes + 1});
            unvisited.push((state){current.i + 1, current.j, current.k, current.minutes + 1});
            unvisited.push((state){current.i, current.j - 1, current.k, current.minutes + 1});
            unvisited.push((state){current.i, current.j + 1, current.k, current.minutes + 1});
            unvisited.push((state){current.i, current.j, current.k - 1, current.minutes + 1});
            unvisited.push((state){current.i, current.j, current.k + 1, current.minutes + 1});
        }
        
        if (!escaped)
            cout << "Trapped!\n";
    }

	return 0;
}
