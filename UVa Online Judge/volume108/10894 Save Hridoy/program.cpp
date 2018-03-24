// Save Hridoy
// UVa ID: 10894
// Verdict: Accepted
// Submission Date: 2018-03-24
// UVa Run Time: 0.050s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

char board[256][3072];
string text = "savehridoy";
string dots[5] = {
    "*****.***.*...*******...**************..******...*",
    "*....*...**...**....*...**...*..*..*..*.*...*.*.*.",
    "***********...****..**********..*..*...**...*..*..",
    "....**...*.*.*.*....*...**.*....*..*..*.*...*..*..",
    "******...*..*..******...**..**********..*****..*.."
};

void drawVerticalLine(int edge, int n)
{
    for (int i = 0; i < 5; i++)
    {
        for (int bi = 0; bi < n; bi++)
            for (int bj = 0; bj < n; bj++)
                board[i * n + bi][edge + bj] = '.';
    }
}

void horizontal(int n)
{
    int edge = 0;
    for (int i = 0; i < text.length(); i++)
    {
        for (int bi = 0; bi < 5; bi++)
        {
            for (int bj = 0; bj < 5; bj++)
            {
                char c = dots[bi][i * 5 + bj];
                for (int j = 0; j < n; j++)
                    for (int k = 0; k < n; k++)
                        board[bi * n + j][edge + bj * n + k] = c;
            }
        }
        
        edge += 5 * n;
        drawVerticalLine(edge, n);
        edge += n;
        if (i == 3)
        {
            drawVerticalLine(edge, n);
            edge += n;
            drawVerticalLine(edge, n);
            edge += n;
        }
    }
    for (int i = 0; i < 5 * n; i++)
    {
        for (int j = 0; j < 61 * n; j++)
            cout << board[i][j];
        cout << '\n';
    }
}

void drawHorizontalLine(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 5 * n; j++)
            cout << '.';
        cout << '\n';
    }
}

void vertical(int n)
{
    for (int i = 0; i < text.length(); i++)
    {
        for (int bi = 0; bi < 5; bi++)
        {
            for (int bj = 0; bj < 5; bj++)
            {
                char c = dots[bi][i * 5 + bj];
                for (int j = 0; j < n; j++)
                    for (int k = 0; k < n; k++)
                        board[bi * n + j][bj * n + k] = c;
            }
        }
        for (int j = 0; j < 5 * n; j++)
        {
            for (int k = 0; k < 5 * n; k++)
                cout << board[j][k];
            cout << '\n';
        }
        if (i < text.length() - 1)
            drawHorizontalLine(n);
        if (i == 3)
        {
            drawHorizontalLine(n);
            drawHorizontalLine(n);
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    while (cin >> n, n != 0)
    {
        if (n > 0) horizontal(n);
        else vertical(abs(n));
        cout << "\n\n";
    }
    return 0;
}
