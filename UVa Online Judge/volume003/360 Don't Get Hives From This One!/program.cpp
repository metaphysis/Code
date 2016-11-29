// Don't Get Hives From This One!
// UVa ID: 360
// Verdict: Accepted
// Submission Date: 2016-11-24
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

int link[10] = {0, 4, 5, 6, 1, 2, 3};
int start, start_opening, dest, dest_opening;
int door[1000][10], adjacent[1000][10];
int to_cell[1000], to_number[1000], enabled[1000];
bool finished;
vector<int> sequences;

void dfs(int room, int wall)
{
    if (finished) return;

    sequences.push_back(room);

    int next_wall = wall;
    for (int k = 1; k <= 6; k++)
    {
        next_wall--;
        if (next_wall <= 0) next_wall += 6;
        if ((room == to_number[start] && next_wall == start_opening) ||
            (room == to_number[dest]) && next_wall == dest_opening)
        {
            finished = true;
            return;
        }
        if (door[room][next_wall]) break;
    }

    if (!adjacent[room][next_wall] || !enabled[adjacent[room][next_wall]])
    {
        finished = true;
        return;
    }
    
    dfs(adjacent[room][next_wall], link[next_wall]);
}

void map_cell_to_number(int r, int c)
{
    memset(to_cell, 0, sizeof(to_cell));
    memset(to_number, 0, sizeof(to_number));

    int offset = c / 2 + c % 2, base = 0;
    for (int i = 1; i <= r; i++)
    {
        for (int j = 1; j <= c; j++)
        {
            if (j % 2 == 1)
            {
                to_cell[(i - 1) * 30 + j] = base + (j + 1) / 2;
                to_number[base + (j + 1) / 2] = (i - 1) * 30 + j;
            }
            else
            {
                to_cell[(i - 1) * 30 + j] = base + j / 2 + offset;
                to_number[base + j / 2 + offset] = (i - 1) * 30 + j;
            }
        }

        base += c;
    }

    memset(enabled, 0, sizeof(enabled));
    int cells = 0;
    for (int i = 1; i <= r; i++)
        cells += (i % 2 == 1) ? ((c + 1) / 2) : (c / 2);
    for (int i = 1; i <= cells; i++)
        enabled[to_number[i]] = 1;
}

void initialize()
{
    int offset[2][6] = {{-30, 1, 31, 30, 29, -1}, {-30, -29, 1, 30, -1, -31}};

    memset(adjacent, 0, sizeof(adjacent));
    for (int i = 1; i <= 15; i++)
        for (int j = 1; j <= 30; j++)
        {
            int number = (i - 1) * 30 + j;
            for (int k = 1; k <= 6; k++)
                adjacent[number][k] = number + offset[j % 2][k - 1];
            if (i == 1)
            {
                adjacent[number][1] = 0;
                if (j % 2 == 1) adjacent[number][2] = adjacent[number][6] = 0;
            }
            if (i == 15)
            {
                adjacent[number][4] = 0;
                if (j % 2 == 0) adjacent[number][3] = adjacent[number][5] = 0;
            }
            if (j == 1) adjacent[number][5] = adjacent[number][6] = 0;
            if (j == 30) adjacent[number][2] = adjacent[number][3] = 0;
        }
}

int main(int argc, char *argv[])
{
    initialize();

    int r, c;
    string line;

    while (cin >> r >> c, r > 0)
    {
        map_cell_to_number(r, c);
        memset(door, 0, sizeof(door));
        cin >> start >> start_opening >> dest >> dest_opening;

        int room, wall;
        while (cin >> room, room > 0)
        {
            getline(cin, line);
            istringstream iss(line);
            while (iss >> wall) door[to_number[room]][wall] = 1;
        }
        
        sequences.clear();
        finished = false;
        dfs(to_number[start], start_opening);

        for (int i = 0; i < sequences.size(); i++)
        {
            cout << to_cell[sequences[i]];
            if ((i + 1) == sequences.size() || (i + 1) % 20 == 0)
                cout << '\n';
            else
                cout << ' ';
        }

        if (sequences.back() == to_number[dest])
            cout << "SOLUTION FOUND\n";
        else
            cout << "NO SOLUTION\n";
    }

    return 0;
}
