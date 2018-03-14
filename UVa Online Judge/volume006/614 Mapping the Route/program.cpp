// Mapping the Route
// UVa ID: 614
// Verdict: Accepted
// Submission Date: 2016-08-31
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int WEST = 0, NORTH = 1, EAST = 2, SOUTH = 3;

int maze[20][20], visited[20][20];
pair<int, int> path[20][20], offset[4] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
int rows, columns, starti, startj, endi, endj;

bool go(int i, int j, int d)
{
    if (d == WEST && (j == 1 || maze[i][j - 1] == 1 || maze[i][j - 1] == 3))
        return false;
    if (d == NORTH && (i == 1 || maze[i - 1][j] == 2 || maze[i - 1][j] == 3))
        return false;
    if (d == EAST && (j == columns || maze[i][j] == 1 || maze[i][j] == 3))
        return false;   
    if (d == SOUTH && (i == rows || maze[i][j] == 2 || maze[i][j] == 3))
        return false;
    return true;
}

bool dfs(int i, int j)
{
    visited[i][j] = -1;

    if (i == endi && j == endj)
        return true;
        
    for (int k = 0; k < 4; k++)
    {
        int nexti = i + offset[k].first, nextj = j + offset[k].second;
        if (visited[nexti][nextj] == 0 && go(i, j, k))
        {
            visited[nexti][nextj] = -1;
            if (dfs(nexti, nextj))
            {
                path[nexti][nextj] = make_pair(i, j);
                return true;
            }
        }
    }
    
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> rows >> columns >> starti >> startj >> endi >> endj)
    {
        if (rows == 0)
            break;
        
        for (int i = 1; i <= rows; i++)
            for (int j = 1; j <= columns; j++)
                cin >> maze[i][j];

        cout << "Maze " << ++cases << "\n\n";

        memset(visited, 0, sizeof(visited));

        if (dfs(starti, startj))
        {
            vector<pair<int, int>> paths;
            pair<int, int> last(endi, endj);
            while (last.first != starti || last.second != startj)
            {
                paths.push_back(last);
                last = path[last.first][last.second];
            }
            paths.push_back(make_pair(starti, startj));
            reverse(paths.begin(), paths.end());
            
            for (int i = 0; i < paths.size(); i++)
                visited[paths[i].first][paths[i].second] = i + 1;
        }
        
        for (int i = 1; i <= columns; i++)
            cout << "+---";
        cout << "+\n";
        
        for (int i = 1; i <= rows; i++)
        {
            if (i > 1)
            {
                for (int j = 1; j <= columns; j++)
                {
                    cout << '+';
                    if (maze[i - 1][j] == 2 || maze[i - 1][j] == 3)
                        cout << "---";
                    else
                        cout << "   ";
                }
                cout << "+\n";
            }

            for (int j = 1; j <= columns; j++)
            {
                if (j == 1)
                    cout << '|';
                    
                if (visited[i][j] == -1)
                    cout << "???";
                else if (visited[i][j] == 0)
                    cout << "   ";
                else
                    cout << setw(3) << right << visited[i][j];
                    
                if (maze[i][j] == 1 || maze[i][j] == 3 || j == columns)
                    cout << '|';
                else
                    cout << ' ';
            }
            cout << '\n';
        }
        
        for (int i = 1; i <= columns; i++)
            cout << "+---";
        cout << "+\n";
        
        cout << "\n\n";
    }
    
	return 0;
}
