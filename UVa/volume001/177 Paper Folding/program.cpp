// Paper Folding
// UVa IDs: 177
// Verdict: Accepted
// Submission Date: 2016-03-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cstring>
#include <map>

using namespace std;

map <char, char> mapped;
char matrix[1024][1024];

string unfolding(int n)
{
    if (n > 1)
    {
        string pattern = unfolding(n - 1);
        int length = pattern.length();
        for (int i = length - 1; i >= 0; i--)
            pattern += mapped[pattern[i]];
        return pattern;
    }
    else
        return "RU";
}

void display(int n)
{
    string pattern = unfolding(n);
    memset(matrix, 0, sizeof(matrix));
    
    int x = 512, y = 512;
    for (int i = 0; i < pattern.length(); i++)
    {
        if (pattern[i] == 'L')
        {
            matrix[x][y] = '_';
        }
        else if (pattern[i] == 'R')
        {
            matrix[x][y] = '_';
        }
        else if (pattern[i] == 'U')
        {
            matrix[x][y] = '|';
        }
        else
        {
            matrix[x][y] = '|';
        }
    }

    // left margin
    int left = 1023;
    for (int i = 0; i < 1024; i++)
        for (int j = 0; j < 1024; j++)
        {
            if (matrix[i][j] != 0)
            {
                if (j < left)
                    left = j;
                break;
            }
        }
    
    for (int i = 0; i < 1024; i++)
    {
        int end = -1;
        for (int j = 1023; j >= 0; j--)
            if (matrix[i][j] != 0)
            {
                end = j;
                break;
            }
        if (end == -1)
            continue;
            
        for (int j = left; j <= end; j++)
            if (matrxi
    }
    
    cout << "^\n";
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    mapped.insert(make_pair('R', 'U'));
    mapped.insert(make_pair('U', 'L'));
    mapped.insert(make_pair('L', 'D'));
    mapped.insert(make_pair('D', 'R'));
    
    int n;
    while (cin >> n, n)
        display(n);
    
	return 0;
}
