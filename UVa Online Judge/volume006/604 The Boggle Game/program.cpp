// The Boggle Game
// UVa ID: 604
// Verdict: Accepted
// Submission Date: 2016-08-30
// UVa Run Time: 0.010s
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

int visited[4][4], vowels[4][4], sequence[4][2], field[4][4];

void dfs(int depth, int i, int j, int k, set<int> &words)
{
    if (depth == 3)
    {
        if (k == 2)
        {
            int word = 0;
            for (int i = 0; i < 4; i++)
                word = word * 27 + field[sequence[i][0]][sequence[i][1]];
            words.insert(word);
        }
    }
    else
    {
        for (int x = -1; x <= 1; x++)
            for (int y = -1; y <= 1; y++)
            {
                int nexti = i + x, nextj = j + y;
                if (nexti >= 0 && nexti < 4 && nextj >= 0 && nextj < 4 && !visited[nexti][nextj])
                {
                    int nextk = k + vowels[nexti][nextj];
                    if (nextk <= 2)
                    {
                        visited[nexti][nextj] = 1;
                        sequence[depth + 1][0] = nexti, sequence[depth + 1][1] = nextj;
                        dfs(depth + 1, nexti, nextj, nextk, words);
                        visited[nexti][nextj] = 0;
                    }
                }
            }
    }
}

void collect(set<int> &words, int matrix[4][4])
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            field[i][j] = matrix[i][j];
            
            if (matrix[i][j] == ('A' - 'A') || matrix[i][j] == ('E' - 'A') || matrix[i][j] == ('I' - 'A') ||
                matrix[i][j] == ('O' - 'A') || matrix[i][j] == ('U' - 'A') || matrix[i][j] == ('Y' - 'A'))
                vowels[i][j] = 1;
            else
                vowels[i][j] = 0;
        }

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {    
            memset(visited, 0, sizeof(visited));
            visited[i][j] = 1;
            sequence[0][0] = i, sequence[0][1] = j;
            dfs(0, i, j, vowels[i][j], words);
        }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int matrix1[4][4], matrix2[4][4];
    
    int cases = 0;
    char terminator, letter;
    while (cin >> terminator, terminator != '#')
    {
        if (cases++ > 0)
            cout << '\n';

        cin.putback(terminator);
        
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                cin >> letter;
                matrix1[i][j] = letter - 'A';
            }
            for (int j = 0; j < 4; j++)
            {
                cin >> letter;
                matrix2[i][j] = letter - 'A';
            }
        }
        
        set<int> words1, words2;
        collect(words1, matrix1), collect(words2, matrix2);
        
        set<string> boggles;
        for (auto word : words1)
            if (words2.find(word) != words2.end())
            {
                string temp;
                for (int i = 0; i < 4; i++)
                {
                    temp += (char)(word % 27 + 'A');
                    word /= 27;
                }
                boggles.insert(temp);
            }
        
        if (boggles.size() == 0)
            cout << "There are no common words for this pair of boggle boards.\n";
        else
        {
            for (auto word : boggles)
                cout << word << '\n';
        }
    }
    
	return 0;
}
