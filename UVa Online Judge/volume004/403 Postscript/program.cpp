// Postscript
// UVa ID: 403
// Verdict: Accepted
// Submission Date: 2016-08-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;
char grid[60][60];

map<char, string> letter = {
    {'A', ".***..*...*.*****.*...*.*...*."},
    {'B', "****..*...*.****..*...*.****.."},
    {'C', ".****.*...*.*.....*......****."},
    {'D', "****..*...*.*...*.*...*.****.."},
    {'E', "*****.*.....***...*.....*****."},
    {'F', "*****.*.....***...*.....*....."},
    {'G', ".****.*.....*..**.*...*..***.."},
    {'H', "*...*.*...*.*****.*...*.*...*."},
    {'I', "*****...*.....*.....*...*****."},
    {'J', "..***....*.....*..*..*...**..."},
    {'K', "*...*.*..*..***...*..*..*...*."},
    {'L', "*.....*.....*.....*.....*****."},
    {'M', "*...*.**.**.*.*.*.*...*.*...*."},
    {'N', "*...*.**..*.*.*.*.*..**.*...*."},
    {'O', ".***..*...*.*...*.*...*..***.."},
    {'P', "****..*...*.****..*.....*....."},
    {'Q', ".***..*...*.*...*.*..**..****."},
    {'R', "****..*...*.****..*..*..*...*."},
    {'S', ".****.*......***......*.****.."},
    {'T', "*****.*.*.*...*.....*....***.."},
    {'U', "*...*.*...*.*...*.*...*..***.."},
    {'V', "*...*.*...*..*.*...*.*....*..."},
    {'W', "*...*.*...*.*.*.*.**.**.*...*."},
    {'X', "*...*..*.*....*....*.*..*...*."},
    {'Y', "*...*..*.*....*.....*.....*..."},
    {'Z', "*****....*....*....*....*****."},
    {' ', ".............................."}
};

void flushing()
{
    for (int i = 0; i < 60; i++)
    {
        for (int j = 0; j < 60; j++)
            cout << grid[i][j];
        cout << '\n';
    }
    cout << '\n';
        
    for (int i = 0; i < 60; i++)
        cout << '-';
    cout << "\n\n";
}

void render_to_right(int r, int c, string font, string text)
{
    if (font == "C1")
    {
        for (int i = 0; i < text.length(); i++)
        {
            if (text[i] != ' ' && r >= 0 && r < 60 && c >= 0 && c < 60)
                grid[r][c] = text[i];
            c++;
        }
    }
    else
    {
        for (int i = 0; i < text.length(); i++)
        {
            for (int j = 0; j < 5; j++)
                for (int k = 0; k < 6; k++)
                {
                    int rr = r + j, cc = c + k;
                    if (letter[text[i]][j * 6 + k] != '.' && rr >= 0 && rr < 60 && cc >= 0 && cc < 60)
                        grid[rr][cc] = letter[text[i]][j * 6 + k];
                }
            c += 6;
        }
    }
}

void render_to_left(int r, int c, string font, string text)
{
    if (font == "C1")
    {
        for (int i = text.length() - 1; i >= 0; i--)
        {
            if (text[i] != ' ' && r >= 0 && r < 60 && c >= 0 && c < 60)
                grid[r][c] = text[i];
            c--;
        }
    }
    else
    {
        c -= 5;
        for (int i = text.length() - 1; i >= 0; i--)
        {
            for (int j = 0; j < 5; j++)
                for (int k = 0; k < 6; k++)
                {
                    int rr = r + j, cc = c + k;
                    if (letter[text[i]][j * 6 + k] != '.' && rr >= 0 && rr < 60 && cc >= 0 && cc < 60)
                        grid[rr][cc] = letter[text[i]][j * 6 + k];
                }
            c -= 6;
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        memset(grid, '.', sizeof(grid));

        do
        {
            while (isblank(line.front()))
                line.erase(line.begin());
            while (isblank(line.back()))
                line.erase(line.end() - 1);
            
            if (line == ".EOP")
            {
                flushing();
                break;
            }
            
            string command, font, row, column, text;
            while (!isblank(line.front()))
            {
                command += line.front();
                line.erase(line.begin());
            }
            
            while (isblank(line.front()))
                line.erase(line.begin());
                
            while (!isblank(line.front()))
            {
                font += line.front();
                line.erase(line.begin());
            }
            
            while (isblank(line.front()))
                line.erase(line.begin());
            while (!isblank(line.front()))
            {
                row += line.front();
                line.erase(line.begin());
            }
            
            if (command == ".P")
            {
                while (isblank(line.front()))
                    line.erase(line.begin());
                while (!isblank(line.front()))
                {
                    column += line.front();
                    line.erase(line.begin());
                }
            }
            while (isblank(line.front())) line.erase(line.begin());
            text = line.substr(1, line.length() - 2);
            
            int r = stoi(row) - 1, c;
            if (command == ".P" || command == ".L")
            {
                if (command == ".L")
                    c = 0;
                else
                    c = stoi(column) - 1;

                render_to_right(r, c, font, text);
            }
            else if (command == ".C")
            {
                if (font == "C5" && text.length() % 2 == 1)
                {
                    render_to_right(r, 27, font, text.substr(text.length() / 2));
                    render_to_left(r, 26, font, text.substr(0, text.length() / 2));
                }
                else
                {
                    render_to_right(r, 30, font, text.substr(text.length() / 2));
                    render_to_left(r, 29, font, text.substr(0, text.length() / 2));
                }
            }
            else if (command == ".R")
                render_to_left(r, 59, font, text);
        } while (getline(cin, line));
    }

	return 0;
}
