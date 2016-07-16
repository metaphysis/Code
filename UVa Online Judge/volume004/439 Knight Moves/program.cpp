// Knight Moves
// UVa ID: 439
// Verdict: Accepted
// Submission Date: 2016-07-13
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct state
{
    int row, column;
};

int offset[8][2] = {
    {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {2, 1}, {2, -1}, {1, 2}, {1, -2}
};

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    string from, to;
    while (cin >> from >> to)
    {
        int start_row = from.back() - '1', start_column = from.front() - 'a';
        int end_row = to.back() - '1', end_column = to.front() - 'a';
        
        int visited[8][8] = { }, moves[8][8] = { };
        
        queue<state> unvisited;
        unvisited.push((state){start_row, start_column});
        visited[start_row][start_column] = 1;
        moves[start_row][start_column] = 0;
        
        while (!unvisited.empty())
        {
            state current = unvisited.front();
            unvisited.pop();
            
            for (int i = 0; i < 8; i++)
            {
                int next_row = current.row + offset[i][0], next_column = current.column + offset[i][1];
                if (next_row >= 0 && next_row < 8 && next_column >= 0 && next_column < 8 && visited[next_row][next_column] == false)
                {
                    moves[next_row][next_column] = moves[current.row][current.column] + 1;
                    unvisited.push((state){next_row, next_column});
                    visited[next_row][next_column] = 1;
                }
            }
        }
        
        cout << "To get from " << from << " to " << to << " takes " << moves[end_row][end_column] << " knight moves." << endl;

    }
    
	return 0;
}
