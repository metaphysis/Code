// Pushing Boxes
// UVa ID: 589
// Verdict: TLE
// Submission Date: 2017-06-05
// UVa Run Time: 3.000s
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

struct state
{
    int boxr, boxc, startr, startc, pushes;
    string moves;
};

int r, c;
char maze[20][20], direction[8] = {'w', 'n', 'e', 's', 'W', 'N', 'E', 'S'};
int pushed[20][20][4], visited[20][20];
int startr, startc, endr, endc, boxr, boxc;
int offset1[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
int offset2[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

bool getWalks(int from_x, int from_y, int to_x, int to_y, int box_x, int box_y, string &shortest)
{
    queue<int> x, y;
    queue<string> walks;

    memset(visited, 0, sizeof(visited));
    x.push(from_x), y.push(from_y), walks.push("");
    visited[from_x][from_y] = 1;
    
    while (!x.empty())
    {
        int current_x = x.front(); x.pop();
        int current_y = y.front(); y.pop();
        string current_walks = walks.front(); walks.pop();
        
        if (current_x == to_x && current_y == to_y)
        {
            shortest = current_walks;
            return true;
        }

        for (int i = 0; i < 4; i++)
        {
            int next_x = current_x + offset1[i][0];
            int next_y = current_y + offset1[i][1];
            
            if (next_x < 0 || next_x >= r || next_y < 0 || next_y >= c) continue;
            if (next_x == box_x && next_y == box_y) continue;
            if (maze[next_x][next_y] == '#') continue;
            if (visited[next_x][next_y]) continue;
            
            visited[next_x][next_y] = 1;
            x.push(next_x), y.push(next_y), walks.push(current_walks + direction[i]);
        }
    }
    
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    
    while (cin >> r >> c)
    {
        if (r == 0 && c == 0) break;
        
        bool possible = true;

        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
            {
                cin >> maze[i][j];
                if (maze[i][j] == 'S') startr = i, startc = j;
                if (maze[i][j] == 'B') boxr = i, boxc = j;
                if (maze[i][j] == 'T') endr = i, endc = j;
            }
        
        if (r == 0 || c == 0) possible = false;

        string bestMoves;
        if (possible)
        {
            int bestPushes = 0;
            possible = false;
            memset(pushed, 0, sizeof(pushed));

            state start = state{boxr, boxc, startr, startc, 0, ""};
            queue<state> unvisited;
            unvisited.push(start);

            while (!unvisited.empty())
            {
                state current = unvisited.front();
                unvisited.pop();
                
                if (possible && current.pushes > bestPushes) break;
                
                if (current.boxr == endr && current.boxc == endc)
                {
                    if (!possible)
                    {
                        bestPushes = current.pushes, bestMoves = current.moves;
                        possible = true;
                    }
                    else
                    {
                        if (current.moves.size() < bestMoves.size())
                            bestMoves = current.moves;
                    }
                }

                // left, up, right, down
                int frontr, frontc, backr, backc;

                for (int i = 0; i < 4; i++)
                {
                    frontr = current.boxr + offset1[i][0];
                    frontc = current.boxc + offset1[i][1];
                    backr = current.boxr + offset2[i][0];
                    backc = current.boxc + offset2[i][1];
                    
                    if (frontr < 0 || frontr >= r || frontc < 0 || frontc >= c) continue;
                    if (backr < 0 || backr >= r || backc < 0 || backc >= c) continue;
                    if (maze[frontr][frontc] == '#') continue;
                    if (maze[backr][backc] == '#') continue;
                    if (pushed[current.boxr][current.boxc][i] && current.pushes > pushed[current.boxr][current.boxc][i]) continue;

                    string walks;
                    if (!getWalks(current.startr, current.startc, backr, backc, current.boxr, current.boxc, walks)) continue;
                    
                    pushed[current.boxr][current.boxc][i] = current.pushes;
                    state next = state{frontr, frontc, current.boxr, current.boxc, current.pushes + 1, current.moves + walks + direction[i + 4]};
                    unvisited.push(next);
                }
            }
        }

        cout << "Maze #" << ++cases << '\n';
        cout << (possible ? bestMoves : "Impossible.");
        cout << "\n\n";
    }
    
    return 0;
}
