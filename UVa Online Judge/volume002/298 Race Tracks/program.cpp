// Race Tracks
// UVa IDs: 298
// Verdict: Accepted
// Submission Date: 2016-05-16
// UVa Run Time: 0.820s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <set>
#include <queue>

using namespace std;

struct hop
{
    int x, y, vx, vy, step;
};

int grid[31][31], X, Y, startx, starty, endx, endy;
set < string > visited;

string getKey(int x, int y, int vx, int vy)
{
    return to_string(x) + "*" + to_string(y) + "*" + to_string(vx) + "*" + to_string(vy);
}

void bfs()
{
    visited.clear();
    
    queue < hop > unvisited;
    unvisited.push((hop){startx, starty, 0, 0, 0});
    
    while (unvisited.size())
    {
        hop current = unvisited.front();
        unvisited.pop();
        
        if (current.x == endx && current.y == endy)
        {
            cout << "Optimal solution takes " << current.step << " hops." << endl;
            return;
        }
        
        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++)
            {   
                int vxx = current.vx + i;
                int vyy = current.vy + j;
                
                if (abs(vxx) > 3 || abs(vyy) > 3)
                    continue;
                    
                int xx = current.x + vxx;
                int yy = current.y + vyy;
                
                if (xx >= 0 && xx < X && yy >= 0 && yy < Y)
                {
                    if (grid[xx][yy] == 1)
                        continue;
                        
                    string key = getKey(xx, yy, vxx, vyy);
                    if (visited.count(key) > 0)
                        continue;
                    else
                        visited.insert(key);
                        
                    unvisited.push((hop){xx, yy, vxx, vyy, current.step + 1});
                }
            }
    }
    
    cout << "No solution." << endl;
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    int N;
    cin >> N;
    
    while (N--)
    {
        cin >> X >> Y;
        
        for (int i = 0; i < X; i++)
            for (int j = 0; j < Y; j++)
                grid[i][j] = 0;
        
        cin >> startx >> starty >> endx >> endy;
                
        int P;
        cin >> P;
        for (int i = 1; i <= P; i++)
        {
            int x1, x2, y1, y2;
            cin >> x1 >> x2 >> y1 >> y2;
            
            for (int m = x1; m <= x2; m++)
                for (int n = y1; n <= y2; n++)
                    grid[m][n] = 1;
        }
        
        bfs();
    }
    
	return 0;
}
