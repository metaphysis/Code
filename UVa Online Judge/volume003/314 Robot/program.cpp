// Robot
// UVa IDs: 314
// Verdict: Accepted
// Submission Date: 2016-07-02
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <queue>

using namespace std;

const int NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3;
int obstacles[60][60], seconds[60][60][4], visited[60][60][4];
int offset[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
int M, N, B1, B2, E1, E2;
string orientation;

struct state
{
    int row, column, elapsed, direction;
};

void bfs(int row, int column, int elapsed, int direction)
{
    for (int i = 0; i <= M; i++)
        for (int j = 0; j <= N; j++)
            for (int k = 0; k < 4; k++)
            {
                seconds[i][j][k] = -1;
                visited[i][j][k] = 0;
            }

    queue<state> unvisited;
    unvisited.push((state){row, column, elapsed, direction});

    while (!unvisited.empty())
    {
        state current = unvisited.front();
        unvisited.pop();

        row = current.row, column = current.column;
        elapsed = current.elapsed, direction = current.direction;

        if (visited[row][column][direction])
            continue;

        visited[row][column][direction] = 1;

        if (seconds[row][column][direction] == -1 ||
            elapsed < seconds[row][column][direction])
            seconds[row][column][direction] = elapsed;

        int step = 1, nextRow = row, nextColumn = column;
        while (step <= 3)
        {
            if ((direction == NORTH && nextRow >= 2) || (direction == SOUTH && nextRow <= (M - 2)) ||
                (direction == EAST && nextColumn <= (N - 2)) || (direction == WEST && nextColumn >= 2))
            {
                nextRow += offset[direction][0], nextColumn += offset[direction][1];
                
                if ((direction == NORTH && (obstacles[nextRow - 1][nextColumn - 1] || obstacles[nextRow - 1][nextColumn])) ||
                    (direction == SOUTH && (obstacles[nextRow][nextColumn - 1] || obstacles[nextRow][nextColumn])) ||
                    (direction == EAST && (obstacles[nextRow - 1][nextColumn] || obstacles[nextRow][nextColumn])) ||
                    (direction == WEST && (obstacles[nextRow - 1][nextColumn - 1] || obstacles[nextRow][nextColumn - 1])))
                    break;

                unvisited.push((state){nextRow, nextColumn, elapsed + 1, direction});
            }
            
            step++;
        }

        unvisited.push((state){row, column, elapsed + 1, (direction - 1 + 4) % 4});
        unvisited.push((state){row, column, elapsed + 1, (direction + 1) % 4});
    }
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    while (cin >> M >> N, M && N)
    {
        for (int row = 0; row < M; row++)
            for (int column = 0; column < N; column++)
                cin >> obstacles[row][column];

        cin >> B1 >> B2 >> E1 >> E2 >> orientation;

        int direction = NORTH;
        if (orientation == "east") direction = EAST;
        else if (orientation == "south") direction = SOUTH;
        else if (orientation == "west") direction = WEST;

        bfs(B1, B2, 0, direction);

        int minSeconds = -1;
        for (int i = 0; i < 4; i++)
        {
            if (seconds[E1][E2][i] == -1)
                continue;
            if (minSeconds == -1 || seconds[E1][E2][i] < minSeconds)
                minSeconds = seconds[E1][E2][i];
        }

        cout << minSeconds << endl;
    }

    return 0;
}
