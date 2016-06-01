// Mirror Maze
// UVa IDs: 258
// Verdict: Time Limit Excess
// Submission Date: 2016-05-25
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

char grid[60][60];
int row, column;
int reflect[3600][4], indexer[60][60], flapped[3600], visited[3600];
vector < pair<int, int> > mirrors(3600);

// up = 0, right = 1, down = 2, left = 3
int offset[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

// mirror is '/' = 0, mirror is '\' = 1
// ligth: up = 0, right = 1, down = 2, left = 3
int transform[2][4][2] =
{
    {{3, 1}, {2, 0}, {1, 3}, {0, 2}}, {{1, 3}, {0, 2}, {3, 1}, {2, 0}}
};

// get next mirror and light by current mirror and light configuration
inline void getNextMirror(int mirror, int light, int& next_mirror, int& next_light)
{
    next_mirror = reflect[mirror][transform[flapped[mirror]][light][0]];
    next_light = transform[flapped[mirror]][light][1];
}

// current mirror and light come in
bool dfs(int mirror, int light)
{
    if (mirror == -1)
        return true;

    bool mirrorVisited = visited[mirror];
    visited[mirror] = true;

    int next_mirror, next_light;
    getNextMirror(mirror, light, next_mirror, next_light);

    if (next_mirror != 0 && dfs(next_mirror, next_light))
        return true;

    if (!mirrorVisited)
    {
        flapped[mirror] = !flapped[mirror];

        getNextMirror(mirror, light, next_mirror, next_light);
        
        // if (dfs(next_mirror, next_light)) is enough
        if (next_mirror != 0 && dfs(next_mirror, next_light))
            return true;

        flapped[mirror] = !flapped[mirror];
    }

    visited[mirror] = mirrorVisited;

    return false;
}

int main(int argc, char *argv[])
{
    bool printBlankLine = false;
    while (cin >> column >> row, column > 0 && row > 0)
    {
        memset(indexer, 0, sizeof(indexer));
        memset(flapped, 0, sizeof(flapped));
        memset(visited, 0, sizeof(visited));
        memset(reflect, 0, sizeof(reflect));

        int mirrorNumber = 0;
        for (int i = 0; i < row; i++)
            for (int j = 0; j < column; j++)
            {
                cin >> grid[i][j];
                if (grid[i][j] == '.' && (i == 0 || i == (row - 1) || j == 0 || j == (column - 1)))
                    indexer[i][j] = -1;
                else if (grid[i][j] == '/' || grid[i][j] == '\\')
                {
                    mirrorNumber++;
                    mirrors[mirrorNumber] = make_pair(i, j);
                    flapped[mirrorNumber] = (grid[i][j] == '\\');
                    indexer[i][j] = mirrorNumber;
                }
            }

        // find neighboring mirrors for current mirror
        int firstMirror = -1, firstLight = -1;
        for (int m = 1; m <= mirrorNumber; m++)
            for (int d = 0; d < 4; d++)
            {
                int i = mirrors[m].first, j = mirrors[m].second;

                while (true)
                {
                    i += offset[d][0], j += offset[d][1];

                    // encounter the boundary
                    if (grid[i][j] == '*')
                        break;

                    // neighborer is enter or exit point
                    if (indexer[i][j] == -1)
                    {
                        reflect[m][d] = -1;
                        firstMirror = m;
                        firstLight = d;
                        break;
                    }

                    // find a neighboring mirror
                    if (indexer[i][j] > 0)
                    {
                        reflect[m][d] = indexer[i][j];
                        break;
                    }
                }
            }

        // start search
        if (firstMirror != -1 && firstLight != -1)
            dfs(firstMirror, firstLight);

        // output result
        if (printBlankLine)
            cout << endl;
        else
            printBlankLine = true;

        for (int i = 1; i <= mirrorNumber; i++)
            grid[mirrors[i].first][mirrors[i].second] = (flapped[i] ? '\\' : '/');

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
                cout << grid[i][j];
            cout << endl;
        }
    }

    return 0;
}
