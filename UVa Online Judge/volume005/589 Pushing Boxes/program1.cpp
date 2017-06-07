// Pushing Boxes
// UVa ID: 589
// Verdict: Accepted
// Submission Date: 2017-06-07
// UVa Run Time: 0.460s
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
    int boxx, boxy, personx, persony, pushes;
    string moves;
    
    bool operator<(const state &s) const
    {
        if (pushes != s.pushes) return pushes > s.pushes;
        else return moves.size() > s.moves.size();
    }
};

struct person
{
    int personx, persony;
    string walks;
};

int r, c;
char maze[24][24], direction[8] = {'n', 's', 'w', 'e', 'N', 'S', 'W', 'E'};
int pushed[24][24][4][400], visited[24][24];
int startx, starty, endx, endy, boxx, boxy;
int offset1[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int offset2[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
string shortest_walks, empty;

bool bfs(int fromx, int fromy, int tox, int toy, int boxr, int boxc)
{
    queue<person> unvisited;
    unvisited.push(person{fromx, fromy, empty});
    
    memset(visited, 0, sizeof(visited));
    visited[fromx][fromy] = 1;
    
    person current, next;
    while (!unvisited.empty())
    {
        current = unvisited.front(); unvisited.pop();

        if (current.personx == tox && current.persony == toy)
        {
            shortest_walks = current.walks;
            return true;
        }

        for (int i = 0; i < 4; i++)
        {
            next = current;
            next.personx += offset1[i][0];
            next.persony += offset1[i][1];
            
            if (next.personx < 0 || next.personx >= r || next.persony < 0 || next.persony >= c) continue;
            if (next.personx == boxr && next.persony == boxc) continue;
            if (maze[next.personx][next.persony] == '#') continue;
            if (visited[next.personx][next.persony]) continue;
            
            visited[next.personx][next.persony] = 1;
            next.walks += direction[i];
            unvisited.push(next);
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
                if (maze[i][j] == 'S') startx = i, starty = j;
                else if (maze[i][j] == 'B') boxx = i, boxy = j;
                else if (maze[i][j] == 'T') endx = i, endy = j;
            }
        
        if (r == 0 || c == 0) possible = false;

        string bestMoves;
        
        if (possible)
        {
            possible = false;
            memset(pushed, 0, sizeof(pushed));

            priority_queue<state> unvisited;
            unvisited.push(state{boxx, boxy, startx, starty, 0, empty});

            int nextx, nexty, previousx, previousy;
            while (!unvisited.empty())
            {
                state current = unvisited.top();
                unvisited.pop();
                
                if (current.boxx == endx && current.boxy == endy)
                {
                    bestMoves = current.moves;
                    possible = true;
                    break;
                }

                for (int i = 0; i < 4; i++)
                {
                    nextx = current.boxx + offset1[i][0], nexty = current.boxy + offset1[i][1];
                    previousx = current.boxx + offset2[i][0], previousy = current.boxy + offset2[i][1];
                    
                    if (nextx < 0 || nextx >= r || nexty < 0 || nexty >= c) continue;
                    if (previousx < 0 || previousx >= r || previousy < 0 || previousy >= c) continue;
                    if (maze[nextx][nexty] == '#' || maze[previousx][previousy] == '#') continue;
                    if (pushed[current.boxx][current.boxy][i][current.pushes]) continue;
                    if (!bfs(current.personx, current.persony, previousx, previousy, current.boxx, current.boxy)) continue;
                    
                    pushed[current.boxx][current.boxy][i][current.pushes] = 1;
                    unvisited.push(state{nextx, nexty, current.boxx, current.boxy, current.pushes + 1, current.moves + shortest_walks + direction[i + 4]});
                }
            }
        }

        cout << "Maze #" << ++cases << '\n';
        cout << (possible ? bestMoves : "Impossible.");
        cout << "\n\n";
    }
    
    return 0;
}
