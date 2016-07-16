// Crosswords
// UVa ID: 285
// Verdict: Accepted
// Submission Date: 2016-06-07
// UVa Run Time: 0.020s
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
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

char grid[150][150], solution[150][150];
int right_most, bottom_most;

void process(string line)
{
    string word, x, y, d;
    istringstream iss(line);
    iss >> word >> x >> y >> d;

    int offsetx, offsety;
    if (d == "l")
        offsetx = -1, offsety = 0;
    else if (d == "r")
        offsetx = 1, offsety = 0;
    else if (d == "u")
        offsetx = 0, offsety = -1;
    else if (d == "d")
        offsetx = 0, offsety = 1;

    int i = stoi(y), j = stoi(x), lasti = i, lastj = j;
    for (int k = 0; k < word.length(); k++)
    {
        grid[i][j] = word[k];
        lasti = i, lastj = j, i += offsety, j += offsetx;
    }

    right_most = max(right_most, max(stoi(x), lastj));
    bottom_most = max(bottom_most, max(stoi(y), lasti));
}

int main(int argc, char *argv[])
{
    string line;
    while (getline(cin, line))
    {
        right_most = 0, bottom_most = 0;
        memset(grid, ' ', sizeof(grid));
        process(line);

        while (getline(cin, line), line[0] != '#')
            process(line);

        int width = (getline(cin, line), stoi(line));
        int height = (getline(cin, line), stoi(line));

        memset(solution, ' ', sizeof(solution));
        getline(cin, line);

        string answer;
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '$')
                break;

            if (!isblank(line[i]))
                answer += line[i];
        }

        bool correct = true;

        if (width != right_most || height != bottom_most)
            correct = false;
        else
        {
            string text;
            for (int i = 1; i <= height; i++)
                for (int j = 1; j <= width; j++)
                    if (!isblank(grid[i][j]))
                        text += grid[i][j];

            correct = (answer == text);
        }

        if (correct)
            cout << "The solution is correct." << endl;
        else
            cout << "The solution is incorrect." << endl;
    }

    return 0;
}
