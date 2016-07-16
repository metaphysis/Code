// Paper Folding
// UVa ID: 177
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
    pattern += '0';

    memset(matrix, ' ', sizeof(matrix));
    int x = 512, y = 512;
    int minx = 512, maxx = 512, miny = 512, maxy = 512;
    for (int i = 0; i < pattern.length() - 1; i++)
    {
        if (pattern[i] == 'L')
        {
            matrix[x][y] = '_';
            y -= 1;
        }
        else if (pattern[i] == 'R')
        {
            matrix[x][y] = '_';
            y += 1;
        }
        else if (pattern[i] == 'U')
        {
            matrix[x][y] = '|';
            x -= 1;
            if (pattern[i + 1] == 'L')
                y -= 1;
            if (pattern[i + 1] == 'R')
                y += 1;
        }
        else if (pattern[i] == 'D')
        {
            x += 1;
            matrix[x][y] = '|';
            if (pattern[i + 1] == 'L')
                y -= 1;
            if (pattern[i + 1] == 'R')
                y += 1;
        }

        minx = min(x, minx);
        maxx = max(x, maxx);
        miny = min(y, miny);
        maxy = max(y, maxy);
    }

    for (int i = minx; i <= maxx; i++)
    {
        int lasty = maxy;
        while (matrix[i][lasty] == ' ')
            lasty--;

        if (lasty >= 0)
        {
            for (int j = miny; j <= lasty; j++)
                cout << matrix[i][j];
            cout << "\n";
        }
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
