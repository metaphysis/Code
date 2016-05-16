// Race Tracks
// UVa IDs: 298
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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

int grid[31][31], minimum[31][31], X, Y, startx, starty, endx, endy;
set < string > visited;

string getKey(int x, int y, int vx, int vy)
{
    return to_string(x) + "#" + to_string(y) + "#" + to_string(vx) + "#" + to_string(vy);
}

void bfs(int startx, int starty)
{
    visited.clear();
        
    for (int i = 0; i < X; i++)
        for (int j = 0; j < Y; j++)
            minimum[i][j] = -1;

    queue < hop > unvisited;
    unvisited.push((hop){startx, starty, 0, 0, 0});
    
    while (unvisited.size())
    {
        hop current = unvisited.front();
        unvisited.pop();
        
        string key = getKey(current.x, current.y, current.vx, current.vy);
        if (visited.count(key) > 0)
            continue;
        else
            visited.insert(key);
            
        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++)
            {   
                int vxx = current.vx + i;
                int vyy = current.vy + j;
                
                int xx = current.x + vxx;
                int yy = current.y + vyy;
                
                if (xx >= 0 && xx < X && yy >= 0 && yy < Y && grid[xx][yy] == 0)
                {
                    if (minimum[xx][yy] < 0 || (current.step + 1) < minimum[xx][yy])
                        minimum[xx][yy] = current.step + 1;
                    unvisited.push((hop){xx, yy, vxx, vyy, current.step + 1});
                }
            }
    }
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
        
        if (startx == endx && starty == endy)
        {
            cout << "Optimal solution takes 0 hops." << endl;
            continue;
        }
        
        bfs(startx, starty);
        
        if (minimum[endx][endy] == -1)
            cout << "No solution." << endl;
        else
        {
            cout << "Optimal solution takes ";
            cout << minimum[endx][endy];
            cout << " hops." << endl;
        }
    }
    
	return 0;
}
