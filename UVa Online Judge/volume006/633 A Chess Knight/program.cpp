// A Chess Knight
// UVa ID: 633
// Verdict: Accepted
// Submission Date: 2017-06-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct movement
{
    int x, y, steps, lastMoveType;
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int obstacle[64][64], visited[64][64][4], n;

    int offsetK[8][2] = {
        {-2, -1}, {-1, -2}, {1, -2}, {2, -1},
        {2, 1}, {1, 2}, {-1, 2}, {-2, 1}
    };
    
    int offsetB[4][2] = {
        {-2, -2}, {2, -2}, {2, 2}, {-2, 2}
    };
    
    while (cin >> n, n > 0)
    {
        n *= 2;

        memset(obstacle, 0, sizeof(obstacle));
        memset(visited, 0, sizeof(visited));

        int startx, starty, endx, endy;
        cin >> startx >> starty >> endx >> endy;
        
        int obstaclex, obstacley;
        while (cin >> obstaclex >> obstacley)
        {            
            if (obstaclex == 0 && obstacley == 0) break;
            obstacle[obstaclex][obstacley] = 1;
        }

        // special cases.
        if (startx == endx && starty == endy)
        {
            cout << "Result : 0\n";
            continue;
        }
        if (obstacle[endx][endy])
        {
            cout << "Solution doesn't exist\n";
            continue;
        }

        // BFS.
        queue<movement> unvisited;
        unvisited.push(movement{startx, starty, 0, 0});
        bool found = false;

        while (!unvisited.empty())
        {
            movement m = unvisited.front();
            unvisited.pop();

            if (m.x == endx && m.y == endy)
            {
                cout << "Result : " << m.steps << '\n';
                found = true;
                break;
            }

            // type K
            if (m.lastMoveType != 1 && !visited[m.x][m.y][1])
            {
                for (int i = 0; i < 8; i++)
                {
                    int nextx = m.x + offsetK[i][0], nexty = m.y + offsetK[i][1];
                    if (nextx < 1 || nextx > n || nexty < 1 || nexty > n) continue;
                    if (obstacle[nextx][nexty]) continue;
                    unvisited.push(movement{nextx, nexty, m.steps + 1, 1});
                }
                
                visited[m.x][m.y][1] = 1;
            }

            // type B
            if (m.lastMoveType != 2 && !visited[m.x][m.y][2])
            {
                for (int i = 0; i < 4; i++)
                {
                    int nextx = m.x + offsetB[i][0], nexty = m.y + offsetB[i][1];
                    if (nextx < 1 || nextx > n || nexty < 1 || nexty > n) continue;
                    if (obstacle[nextx][nexty]) continue;
                    unvisited.push(movement{nextx, nexty, m.steps + 1, 2});
                }
                visited[m.x][m.y][2] = 1;
            }
            
            // type T
            if (m.lastMoveType != 3 && !visited[m.x][m.y][3])
            {
                int nextx = n - m.x + 1, nexty = m.y;
                if (!obstacle[nextx][nexty])
                    unvisited.push(movement{nextx, nexty, m.steps + 1, 3});
                
                nextx = m.x, nexty = n - m.y + 1;
                if (!obstacle[nextx][nexty])
                    unvisited.push(movement{nextx, nexty, m.steps + 1, 3});
                
                visited[m.x][m.y][3] = 1;
            }
        }
        
        if (!found)  cout << "Solution doesn't exist\n";
    }
    
    return 0;
}
