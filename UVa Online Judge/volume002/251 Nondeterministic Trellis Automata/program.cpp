// Nondeterministic Trellis Automata
// UVa ID: 251
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
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

int table[15][15], states, counter, cases = 0, accepted = 0;
map<int, set <long long int> > patterns;
bool flag = false;

void backtrack(int, int, int[], int[]);

void dfs(int row, int processor[])
{
    if (flag)
        return;

    if (row == 1)
    {
        if (((1 << processor[0]) & accepted) > 0)
            flag = true;
    }
    else
    {
        int next_processor[15];
        for (int j = 0; j < row - 1; j++)
            next_processor[j] = table[processor[j]][processor[j + 1]];

        int next_next_processor[15];
        backtrack(0, row - 1, next_processor, next_next_processor);
    }
}

void backtrack(int index, int row, int processor[], int next_processor[])
{
    if (flag)
        return;

    if (index == row)
    {
        long long int key = 0;
        for (int i = 0; i < row; i++)
        {
            key |= next_processor[i];
            key <<= 4;
        }
        
        if (patterns[row].find(key) == patterns[row].end())
        {
            patterns[row].insert(key);
            dfs(row, next_processor);
        }
    }
    else
    {
        for (int i = 0; i < states; i++)
            if (((1 << i) & processor[index]) > 0)
            {
                next_processor[index] = i;
                backtrack(index + 1, row, processor, next_processor);
                if (flag)
                    return;
            }
    }
}

int main(int argc, char *argv[])
{
    string line;
    while (getline(cin, line))
    {
        istringstream iss(line);
        iss >> states >> counter;

        if (states == 0)
            break;

        accepted = 0;
        for (int i = states - 1; counter > 0; counter--, i--)
            accepted |= (1 << i);

        memset(table, 0, sizeof(table));
        for (int i = 0; i < states; i++)
            for (int j = 0; j < states; j++)
            {
                getline(cin, line);
                for (int k = 0; k < line.length(); k++)
                    if (isalpha(line[k]))
                        table[i][j] |= (1 << (line[k] - 'a'));
            }

        if (cases++)
            cout << endl;
        cout << "NTA " << cases << endl;

        while (getline(cin, line), line.front() != '#')
        {
            int processor[15] = { 0 }, next_processor[15] = { 0 }, row = 0;
            for (int i = 0; i < line.length(); i++)
                if (isalpha(line[i]))
                    processor[row++] = (1 << (line[i] - 'a'));

            flag = false;
            patterns.clear();
            backtrack(0, row, processor, next_processor);

            cout << (flag ? "accept " : "reject ") << line << endl;
        }
    }

    return 0;
}
