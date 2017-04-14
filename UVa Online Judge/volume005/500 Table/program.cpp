// Table
// UVa ID: 500
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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

const char separator = (char)(179), right_line_separator = (char)(180),
    top_right_corner = (char)(191), bottom_left_corner = (char)(192),
    bottom_line_separator = (char)(193), top_line_separator = (char)(194),
    left_line_separator = (char)(195), link = (char)(196),
    middle_line_separator = (char)(197), bottom_right_corner = (char)(217),
    top_left_corner = (char)(218);

struct row
{
    vector<vector<string>> lines;
};

void drawLine(int cells, vector<int> &columnWidth, char left, char middle, char right)
{
    cout << left;
    for (int i = 0; i < cells; i++)
    {
        if (i > 0) cout << middle;
        for (int j = 0; j < columnWidth[i] + 2; j++) cout << link;
    }
    cout << right << '\n';    
}

void process(vector<string> table)
{
    istringstream iss;

    vector<int> columnWidth(200, 0);
    vector<row> rows;
    int columns = 0;

    for (int i = 0; i < table.size(); i++)
    {
        if (table[i].front() == separator)
        {
            row single_row;
            bool empty_row = true;
            while (table[i].front() == separator)
            {
                iss.clear(); iss.str(table[i].substr(1, table[i].length() - 2));
                vector<string> cells;
                string block;
                bool empty_line = true;
                columns = 0;

                while (getline(iss, block, separator))
                {
                    int ii = 0, jj = block.length() - 1;
                    while (ii < block.length() && isblank(block[ii]))
                        ii++;
                    while (jj >= 0 && isblank(block[jj]))
                        jj--;
                    if (ii <= jj)
                    {
                        cells.push_back(block.substr(ii, jj - ii + 1));
                        columnWidth[columns] = max(columnWidth[columns], jj - ii + 1);
                        empty_line = false;
                    }
                    else
                        cells.push_back("");
                    columns++;
                }
                
                if (!empty_line)
                {
                    empty_row = false;
                    single_row.lines.push_back(cells);
                }
                i++;
            }
            if (!empty_row) rows.push_back(single_row);
        }
    }

    drawLine(columns, columnWidth, top_left_corner, top_line_separator, top_right_corner);

    for (int i = 0; i < rows.size(); i++)
    {
        if (i > 0)
            drawLine(columns, columnWidth, left_line_separator, middle_line_separator, right_line_separator);

        for (int j = 0; j < rows[i].lines.size(); j++)
        {
            for (int k = 0; k < rows[i].lines[j].size(); k++)
            {
                cout << separator << ' ' << rows[i].lines[j][k];
                int spaces = columnWidth[k] + 1 - rows[i].lines[j][k].length();
                for (int c = 0; c < spaces; c++) cout << ' ';
            }
            cout << separator << '\n';
        }
    }

    drawLine(columns, columnWidth, bottom_left_corner, bottom_line_separator, bottom_right_corner);
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    getline(cin, line);
    
    int M = stoi(line);

    getline(cin, line);
    for (int c = 1; c <= M; c++)
    {
        if (c > 1) cout << '\n';

        vector<string> table;
        while (getline(cin, line), line.length() > 0)
            table.push_back(line);

        process(table);
    }

    return 0;
}
