// Table
// UVa ID: 500
// Verdict: Accepted
// Submission Date: 2017-04-17
// UVa Run Time: 0.100s
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
#include <vector>

using namespace std;

const char separator = (char)(179), right_line_separator = (char)(180),
    top_right_corner = (char)(191), bottom_left_corner = (char)(192),
    bottom_line_separator = (char)(193), top_line_separator = (char)(194),
    left_line_separator = (char)(195), link = (char)(196),
    middle_line_separator = (char)(197), bottom_right_corner = (char)(217),
    top_left_corner = (char)(218);

void drawLine(int cells, vector<int> &columnWidth, char left, char middle, char right)
{
    cout << left;
    for (int i = 0; i < cells; i++)
    {
        if (i > 0)
            cout << middle;
        for (int j = 0; j < columnWidth[i] + 2; j++)
            cout << link;
    }
    cout << right << '\n';
}

void process(vector< string> table)
{
    vector<int> columnWidth(256, 0);

    int columns = 0;
    for (int i = 0; i < table.size(); i++)
        if (table[i].front() == separator)
        {
            istringstream iss(table[i].substr(1, table[i].length() - 1));
            string block;

            int c = 0;
            while (getline(iss, block, separator))
            {
                int ii = 0, jj = block.length() - 1;
                while (ii < block.length() && isblank(block[ii]))
                    ii++;
                while (jj >= 0 && isblank(block[jj]))
                    jj--;
                if (ii <= jj)
                    columnWidth[c] = max(columnWidth[c], jj - ii + 1);
                c++;
            }
            columns = c;
        }

    for (int i = 0; i < table.size(); i++)
    {
        if (table[i].front() == top_left_corner)
            drawLine(columns, columnWidth, top_left_corner, top_line_separator, top_right_corner);
        if (table[i].front() == bottom_left_corner)
            drawLine(columns, columnWidth, bottom_left_corner, bottom_line_separator, bottom_right_corner);
        if (table[i].front() == left_line_separator)
            drawLine(columns, columnWidth, left_line_separator, middle_line_separator, right_line_separator);

        if (table[i].front() == separator)
        {
            istringstream iss(table[i].substr(1, table[i].length() - 1));

            string block;
            int c = 0;
            while (getline(iss, block, separator))
            {
                int ii = 0, jj = block.length() - 1;
                while (ii < block.length() && isblank(block[ii]))
                    ii++;
                while (jj >= 0 && isblank(block[jj]))
                    jj--;
                if (ii <= jj)
                    block = block.substr(ii, jj - ii + 1);
                else
                    block.clear();
                cout << separator << ' ' << block;
                cout << string(columnWidth[c] + 1 - block.length(), ' ');
                c++;
            }
            cout << separator << '\n';
        }
    }
}

int main(int argc, char *argv[])
{
    string line;
    getline(cin, line);

    int cases = stoi(line);

    getline(cin, line);
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1)
            cout << '\n';

        vector<string> table;
        while (getline(cin, line), line.length() > 0)
            table.push_back(line);

        process(table);
    }

    return 0;
}
