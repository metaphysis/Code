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
    vector < vector < string >> lines;
};

void process(vector < string > table)
{
    istringstream iss;

    vector < row > rows;
    for (int i = 0; i < table.size(); i++)
    {
        if (table[i].front() == separator)
        {
            row single_row;
            while (table[i].front() == separator)
            {
                string input = table[i].substr(1, table[i].length() - 2);
                for (int i = 0; i < input.length(); i++)
                    if (input[i] == separator)
                        input[i] = '|';

                iss.clear();
                iss.str(input);

                vector < string > cells;
                string block;
                while (getline(iss, block, '|'))
                {
                    int i = 0, j = block.length() - 1;
                    while (i < block.length() && isblank(block[i]))
                        i++;
                    while (j >= 0 && isblank(block[j]))
                        j--;
                    if (i <= j)
                        cells.push_back(block.substr(i, j - i + 1));
                    else
                        cells.push_back("");
                }
                single_row.lines.push_back(cells);

                i++;
            }
            rows.push_back(single_row);
        }
    }

    int cells_per_line = (int)rows[0].lines[0].size();
    vector < int >max_length_of_cell(cells_per_line, 0);
    for (auto single_row : rows)
        for (auto single_line : single_row.lines)
        {
            int i = 0;
            for (auto single_word : single_line)
            {
                max_length_of_cell[i] = max(max_length_of_cell[i], (int)single_word.length());
                i++;
            }
        }

    cout << top_left_corner;
    for (int i = 0; i < cells_per_line; i++)
    {
        if (i > 0)
            cout << top_line_separator;
        int link_count = max_length_of_cell[i] + 2;
        for (int j = 0; j < link_count; j++)
            cout << link;
    }
    cout << top_right_corner << '\n';

    for (int i = 0; i < rows.size(); i++)
    {
        if (i > 0)
        {
            cout << left_line_separator;
            for (int j = 0; j < cells_per_line; j++)
            {
                if (j > 0)
                    cout << middle_line_separator;
                int link_count = max_length_of_cell[j] + 2;
                for (int k = 0; k < link_count; k++)
                    cout << link;
            }
            cout << right_line_separator << '\n';
        }

        for (int j = 0; j < rows[i].lines.size(); j++)
        {
            for (int k = 0; k < rows[i].lines[j].size(); k++)
            {
                cout << separator << ' ' << rows[i].lines[j][k];
                cout << string(max_length_of_cell[k] + 1 - rows[i].lines[j][k].length(), ' ');
            }
            cout << separator << '\n';
        }
    }

    cout << bottom_left_corner;
    for (int i = 0; i < cells_per_line; i++)
    {
        if (i > 0)
            cout << bottom_line_separator;
        int link_count = max_length_of_cell[i] + 2;
        for (int j = 0; j < link_count; j++)
            cout << link;
    }
    cout << bottom_right_corner << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);

    int M;

    cin >> M;
    cin.ignore(1024, '\n');

    string line;
    getline(cin, line);

    for (int c = 1; c <= M; c++)
    {
        if (c > 1)
            cout << '\n';

        vector < string > table;
        while (getline(cin, line), line.length() > 0)
            table.push_back(line);

        process(table);
    }

    return 0;
}
